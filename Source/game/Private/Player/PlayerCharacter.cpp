#include "Player/PlayerCharacter.h"
#include "Components/InventoryComponent.h"
#include "UI/GameHUD.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "MoverComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/Interactable.h"
#include "DefaultMovementSet/Settings/CommonLegacyMovementSettings.h"
#include "UI/Inventory/TileHolderWidget.h"
#include "Data/Inventory/InventoryContainer.h"
#include "UI/Inventory/CollectableHoldingVisual.h"
private
#include "Components/WidgetComponent.h"
#include "UI/TabMenuWidget.h"
#include "UI/Inventory/ContainerWidget.h"
#include "Data/Inventory/TileHolderData.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Creates all necessery sub objects
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(CapsuleCollision);

	private

	private

	CameraCollision = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Collision"));
	CameraCollision->SetupAttachment(CapsuleCollision);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraCollision);

	MoverComponent = CreateDefaultSubobject<UMoverComponent>(TEXT("Mover"));

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	SetReplicatingMovement(false); // Stops movement replication since that's handled by mover

	private
}

void APlayerCharacter::Server_SetCollectableAmount_Implementation(AInteractable* InInteractable, int8 InNewAmount)
{
	InInteractable->Collectable.Amount = InNewAmount;
}

void APlayerCharacter::Server_AddCollectable_Implementation(AInteractable* InInteractable, int16 InTileHolderIndex, FCollectableBase InCollectableToAdd, FIntPoint InDimensions, private, private, FBorderBounds InBorderBounds)
{
	private

	FIntPoint TopLeftTile = InCollectableToAdd.TopLeftTile;

	FTileHolderData& TileHolderData = InInteractable->Container->TileHolders[InTileHolderIndex];

	for (int16 x = TopLeftTile.X; x < TopLeftTile.X + InDimensions.X; x++)
	{
		for (int16 y = TopLeftTile.Y; y < TopLeftTile.Y + InDimensions.Y; y++)
		{
			TileHolderData.Tiles[UTileHolderWidget::TileToIndex(TileHolderData.TileHolderBounds.Columns, { x, y })] = InCollectableToAdd.UUID;
		}
	}

	TileHolderData.Collectables.Add(InCollectableToAdd);

	InInteractable->DirtyTheContainer();
}

void APlayerCharacter::Server_RemoveCollectable_Implementation(AInteractable* InInteractable, int16 InTileHolderIndex, FGuid InCollectableToRemoveUUID)
{
	FTileHolderData& TileHolderData = InInteractable->Container->TileHolders[InTileHolderIndex];

	for (int16 i = 0; i < TileHolderData.Tiles.Num(); i++)
	{
		if (TileHolderData.Tiles[i] == InCollectableToRemoveUUID)
		{
			TileHolderData.Tiles[i].Invalidate();
		}
	}

	for (int16 i = 0; i < TileHolderData.Collectables.Num(); i++)
	{
		if (TileHolderData.Collectables[i].UUID == InCollectableToRemoveUUID)
		{
			TileHolderData.Collectables.RemoveAt(i);
			TileHolderData.Collectables.Shrink();
			break;
		}
	}

	InInteractable->DirtyTheContainer();
}

void APlayerCharacter::Server_ModifyCollectable_Implementation(AInteractable* InInteractable, int16 InTileHolderIndex, FGuid InCollectableToModifyUUID, int8 InNewAmount)
{
	for (FCollectableBase& Collectable : InInteractable->Container->TileHolders[InTileHolderIndex].Collectables)
	{
		if (Collectable.UUID == InCollectableToModifyUUID)
		{
			Collectable.Amount = InNewAmount;
			break;
		}
	}

	InInteractable->DirtyTheContainer();
}

void APlayerCharacter::Server_SpawnCollectable_Implementation(FVector InSpawnLocation, FCollectableBase InCollectableToSpawn, private, private, FBorderBounds InBorderBounds)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const TObjectPtr<AInteractable> SpawnedCollectable = GetWorld()->SpawnActor<AInteractable>(InteractableClass, InSpawnLocation, FRotator::ZeroRotator, SpawnParams);

	if (IsValid(SpawnedCollectable))
	{
		SpawnedCollectable->bIsCollectable = true;
		SpawnedCollectable->Mesh->SetStaticMesh(InCollectableToSpawn.ResourceData.Mesh);

		private

		SpawnedCollectable->Collectable = InCollectableToSpawn;
	}
}

private

// Handles input actions
void APlayerCharacter::ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& OutInputCmd)
{
	FCharacterDefaultInputs& CharacterInputs = OutInputCmd.InputCollection.FindOrAddMutableDataByType<FCharacterDefaultInputs>();

	if (!IsValid(Controller))
	{
		if (GetLocalRole() == ENetRole::ROLE_Authority && GetRemoteRole() == ENetRole::ROLE_SimulatedProxy)
		{
			static const FCharacterDefaultInputs DoNothingInput;
			CharacterInputs = DoNothingInput;
		}

		return;
	}

	CharacterInputs.ControlRotation = FRotator::ZeroRotator;
	
	if (const TObjectPtr<APlayerController> PC = Cast<APlayerController>(Controller))
	{
		CharacterInputs.ControlRotation = PC->GetControlRotation();
	}

	FVector2D FinalDirectionalIntent{ 0 };
	if (IsValid(MoverComponent))
	{
		FRotator Rotator = CharacterInputs.ControlRotation;
		const FVector RotationProjectedOntoUpDirection = FVector::VectorPlaneProject(Rotator.Vector(), MoverComponent->GetUpDirection()).GetSafeNormal();
		Rotator = RotationProjectedOntoUpDirection.Rotation();

		FinalDirectionalIntent.X = Rotator.RotateVector(FVector(CachedMoveInputIntent, 0)).X;
		FinalDirectionalIntent.Y = Rotator.RotateVector(FVector(CachedMoveInputIntent, 0)).Y;
	}
	CharacterInputs.SetMoveInput(EMoveInputType::DirectionalIntent, FVector(FinalDirectionalIntent, 0));

	const bool bHasAffirmativeMoveInput = (CharacterInputs.GetMoveInput().Size() >= 1e-3);

	CharacterInputs.OrientationIntent = FVector::ZeroVector;

	if (bHasAffirmativeMoveInput)
	{
		// Set the intent to the actors movement direction
		CharacterInputs.OrientationIntent = CharacterInputs.GetMoveInput().GetSafeNormal();

		LastAffirmativeMoveInput = FVector2D(CharacterInputs.GetMoveInput().X, CharacterInputs.GetMoveInput().Y);
	}
	else
	{
		// There is no movement intent, so use the last-known affirmative move input
		CharacterInputs.OrientationIntent = FVector(LastAffirmativeMoveInput.X, LastAffirmativeMoveInput.Y, 0);
	}

	CharacterInputs.bUsingMovementBase = false;

	if (IsValid(MoverComponent))
	{
		if (UPrimitiveComponent* MovementBase = MoverComponent->GetMovementBase())
		{
			FName MovementBaseBoneName = MoverComponent->GetMovementBaseBoneName();

			FVector RelativeMoveInput = FVector::ZeroVector, RelativeOrientDir = FVector::ZeroVector;

			UBasedMovementUtils::TransformWorldDirectionToBased(MovementBase, MovementBaseBoneName, CharacterInputs.GetMoveInput(), RelativeMoveInput);
			UBasedMovementUtils::TransformWorldDirectionToBased(MovementBase, MovementBaseBoneName, CharacterInputs.OrientationIntent, RelativeOrientDir);

			CharacterInputs.SetMoveInput(CharacterInputs.GetMoveInputType(), RelativeMoveInput);
			CharacterInputs.OrientationIntent = RelativeOrientDir;

			CharacterInputs.bUsingMovementBase = true;
			CharacterInputs.MovementBase = MovementBase;
			CharacterInputs.MovementBaseBoneName = MovementBaseBoneName;
		}
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocallyControlled()) return;

	if (const TObjectPtr<APlayerController> PC = Cast<APlayerController>(Controller))
	{
		if (const TObjectPtr<AGameHUD> GameHUD = Cast<AGameHUD>(PC->GetHUD()))
		{
			InventoryComponent->HUD = GameHUD;
			HUD = GameHUD;
		}

		// Apply IMC to player
		if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultIMC, 0);
		}
	}

	private
	private
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsLocallyControlled()) return;

	DetectInteractables();
	if (Interactables.Num() != 0) InteractableHandler();
	if (Interactables.Num() == 0 && CurrentInteractable)
	{
		private

		CurrentInteractable = nullptr;
	}
	if (IsValid(HUD))
	{
		if (!IsValid(CurrentInteractable) && HUD->bIsGroundContainerOpened) HUD->CloseTabMenu();
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!IsLocallyControlled()) return;

	// Setup some bindings
	if (const TObjectPtr<UEnhancedInputComponent> Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveIA, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		Input->BindAction(MoveIA, ETriggerEvent::Completed, this, &APlayerCharacter::Moved);
		Input->BindAction(LookIA, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		Input->BindAction(IncreaseSpeedIA, ETriggerEvent::Triggered, this, &APlayerCharacter::IncreaseMoveSpeed);
		Input->BindAction(DecreaseSpeedIA, ETriggerEvent::Triggered, this, &APlayerCharacter::DecreaseMoveSpeed);
		Input->BindAction(TabMenuIA, ETriggerEvent::Started, this, &APlayerCharacter::TabMenuToggle);
		Input->BindAction(InteractIA, ETriggerEvent::Started, this, &APlayerCharacter::HandleInteraction);
		private
		Input->BindAction(RotateHeldVisualIA, ETriggerEvent::Started, this, &APlayerCharacter::RotateHeldVisual);
		Input->BindAction(DropCollectableIA, ETriggerEvent::Started, this, &APlayerCharacter::DropCollectable);
	}
}

void APlayerCharacter::Move(const FInputActionValue& InValue)
{
	const FVector2D MoveVector = InValue.Get<FVector2D>();
	CachedMoveInputIntent.X = FMath::Clamp(MoveVector.X, -1.0f, 1.0f);
	CachedMoveInputIntent.Y = FMath::Clamp(MoveVector.Y, -1.0f, 1.0f);
}

void APlayerCharacter::Moved()
{
	CachedMoveInputIntent = FVector2D::ZeroVector;
}

void APlayerCharacter::Look(const FInputActionValue& InValue)
{
	const FVector2D LookAxis = InValue.Get<FVector2D>();

	if (const TObjectPtr<APlayerController> PC = Cast<APlayerController>(Controller))
	{
		// Spin camera based on input
		PC->AddYawInput(LookAxis.X * Sensitivity);
		PC->AddPitchInput(-LookAxis.Y * (Sensitivity / 2));
	}
}

void APlayerCharacter::IncreaseMoveSpeed()
{
	if (IsValid(MoverComponent))
	{
		static bool bDidOnce = false;

		if (!bDidOnce)
		{
			float& CurrentSpeed = MoverComponent->FindSharedSettings_Mutable<UCommonLegacyMovementSettings>()->MaxSpeed;

			if (CurrentSpeed < MaxMoveSpeed)
			{
				CurrentSpeed = FMath::Clamp(CurrentSpeed + MoveSpeedSensitivity, CurrentSpeed, MaxMoveSpeed);
				Server_IncreaseMoveSpeed(MoverComponent, MoveSpeedSensitivity, MaxMoveSpeed);
			}

			bDidOnce = true;
		}
		else bDidOnce = false;
	}
}

void APlayerCharacter::DecreaseMoveSpeed()
{
	if (IsValid(MoverComponent))
	{
		static bool bDidOnce = false;

		if (!bDidOnce)
		{
			float& CurrentSpeed = MoverComponent->FindSharedSettings_Mutable<UCommonLegacyMovementSettings>()->MaxSpeed;

			if (CurrentSpeed > MinMoveSpeed)
			{
				CurrentSpeed = FMath::Clamp(CurrentSpeed - MoveSpeedSensitivity, MinMoveSpeed, CurrentSpeed);
				Server_DecreaseMoveSpeed(MoverComponent, MoveSpeedSensitivity, MinMoveSpeed);
			}

			bDidOnce = true;
		}
		else bDidOnce = false;
	}
}

void APlayerCharacter::Server_IncreaseMoveSpeed_Implementation(UMoverComponent* InMoverComp, float InMoveSpeedSensitivity, float InMaxMoveSpeed)
{
	float& CurrentSpeed = InMoverComp->FindSharedSettings_Mutable<UCommonLegacyMovementSettings>()->MaxSpeed;

	if (CurrentSpeed < InMaxMoveSpeed)
	{
		CurrentSpeed = FMath::Clamp(CurrentSpeed + InMoveSpeedSensitivity, CurrentSpeed, InMaxMoveSpeed);
	}
}

void APlayerCharacter::Server_DecreaseMoveSpeed_Implementation(UMoverComponent* InMoverComp, float InMoveSpeedSensitivity, float InMinMoveSpeed)
{
	float& CurrentSpeed = InMoverComp->FindSharedSettings_Mutable<UCommonLegacyMovementSettings>()->MaxSpeed;

	if (CurrentSpeed > InMinMoveSpeed)
	{
		CurrentSpeed = FMath::Clamp(CurrentSpeed - InMoveSpeedSensitivity, InMinMoveSpeed, CurrentSpeed);
	}
}

void APlayerCharacter::DetectInteractables()
{
	const FVector TraceStart = GetActorLocation() + GetActorForwardVector() * InteractableDetectorsBoxExtent.X + GetActorUpVector() * InteractableDetectorsBoxOffset.Y;
	const FVector TraceEnd = TraceStart + GetActorForwardVector() * InteractableDetectorsBoxExtent.X + GetActorRightVector() * InteractableDetectorsBoxExtent.Y + GetActorUpVector() * InteractableDetectorsBoxExtent.Z;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	TArray<FHitResult> HitResults;

	GetWorld()->SweepMultiByChannel(HitResults, TraceStart, TraceEnd, FQuat(GetActorRotation()), ECC_Visibility, FCollisionShape::MakeBox(InteractableDetectorsBoxExtent), CollisionParams);

	Interactables.RemoveAll([&HitResults](TObjectPtr<AActor> InCandidate)
		{
			return !HitResults.ContainsByPredicate([InCandidate](const FHitResult& InHitResult)
				{
					return InHitResult.GetActor() == InCandidate;
				}
			);
		}
	);

	for (const FHitResult& HitResult : HitResults)
	{
		if (const TObjectPtr<AActor> HitActor = HitResult.GetActor())
		{
			if (IsValid(HitActor) && !Interactables.Contains(HitActor) && HitActor->IsA(AInteractable::StaticClass()))
			{
				Interactables.Add(HitActor);
			}
		}
	}
}

void APlayerCharacter::InteractableHandler()
{
	if (const TObjectPtr<APlayerController> PC = Cast<APlayerController>(Controller))
	{
		// Camera rotation
		const FRotator CameraRotation = PC->GetControlRotation();
		const FVector CameraForwardVector = CameraRotation.Vector();

		TObjectPtr<AActor> ClosestInteractableActor = nullptr;
		float MinAngle = MAX_FLT;

		for (const TObjectPtr<AActor> Interactable : Interactables)
		{
			const FVector ToInteractable = (Interactable->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			const float Angle = FMath::Acos(FVector::DotProduct(ToInteractable, CameraForwardVector));

			if (FMath::IsNearlyEqual(Angle, MinAngle, 0.01f) || Angle < MinAngle)
			{
				MinAngle = Angle;
				ClosestInteractableActor = Interactable;
			}
		}

		if (IsValid(ClosestInteractableActor))
		{
			if (const TObjectPtr<AInteractable> ClosestInteractable = Cast<AInteractable>(ClosestInteractableActor))
			{
				InteractableOcclusionCheck(ClosestInteractable);
			}
		}
	}
}

void APlayerCharacter::InteractableOcclusionCheck(TObjectPtr<AInteractable> InClosestInteractable)
{
	const FVector TraceStart = GetActorLocation();
	const FVector TraceEnd = InClosestInteractable->GetActorLocation();

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams))
	{
		if (const TObjectPtr<AInteractable> CheckedClosestInteractable = Cast<AInteractable>(HitResult.GetActor()))
		{
			if (CheckedClosestInteractable != CurrentInteractable && CheckedClosestInteractable == InClosestInteractable)
			{
				private

				CurrentInteractable = CheckedClosestInteractable;

				private
			}
		}
	}
}

void APlayerCharacter::HandleInteraction()
{
	if (IsValid(HUD))
	{
		private

		if (private)
		{
			private
		}
		else if (IsValid(CurrentInteractable))
		{
			if (CurrentInteractable->bIsContainer)
			{
				CurrentInteractable->Interact(HUD);
			}
			else if (CurrentInteractable->bIsCollectable)
			{
				if (InventoryComponent->HandlePickup(CurrentInteractable))
				{
					Server_DestroyInteractable(CurrentInteractable);
				}
			}
		}
	}
}

void APlayerCharacter::Server_DestroyInteractable_Implementation(AInteractable* InOutInteractable)
{
	InOutInteractable->Destroy();
}

void APlayerCharacter::TabMenuToggle()
{
	if (IsValid(HUD)) HUD->TabMenuToggle();
}

private

private

void APlayerCharacter::DropCollectable()
{
	if (private)
	{
		if (const TObjectPtr<APlayerController> PC = Cast<APlayerController>(Controller))
		{
			const FCollectableBase& CollectableToDrop = private;
			FCollectableBase CollectableToDropCopy = CollectableToDrop;

			const FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 150.f);

			if (PC->IsInputKeyDown(EKeys::LeftControl) && CollectableToDrop.Amount > 1)
			{
				CollectableToDropCopy.Amount = 1;

				Server_SpawnCollectable(SpawnLocation, CollectableToDropCopy);

				InventoryComponent->SubtractCollectable(1);
			}
			else
			{
				private

				Server_SpawnCollectable(SpawnLocation, CollectableToDropCopy, private, private, private);

				InventoryComponent->RemoveCollectable();
				private
			}
		}
	}
}