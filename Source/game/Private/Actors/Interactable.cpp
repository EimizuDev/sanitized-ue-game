#include "Actors/Interactable.h"
#include "UI/GameHUD.h"
#include "UI/TabMenuWidget.h"
#include "UI/Inventory/ContainerWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Data/Inventory/ContainersDataTable.h"
#include "Logs.h"
#include "Components/InventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "Data/Inventory/InventoryContainer.h"
#include "Components/WidgetComponent.h"
private

AInteractable::AInteractable()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	bReplicateUsingRegisteredSubObjectList = true;
	SetReplicateMovement(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	SetRootComponent(Mesh);

	Mesh->SetIsReplicated(true);

	private

	private

	// Assigning the containers data table
	const static ConstructorHelpers::FObjectFinder<UDataTable> ContainersDataTableHelper{ TEXT("/Game/Data/DT_Containers") };
	if (ContainersDataTableHelper.Object != NULL)
	{
		ContainersDataTable = ContainersDataTableHelper.Object;
	}

	// Assigning the collectables data table
	const static ConstructorHelpers::FObjectFinder<UDataTable> CollectablesDataTableHelper{ TEXT("/Game/Data/DT_Collectables") };
	if (CollectablesDataTableHelper.Object != NULL)
	{
		CollectablesDataTable = CollectablesDataTableHelper.Object;
	}
}

void AInteractable::Interact(TObjectPtr<AGameHUD> InHUD)
{
	if (!InHUD->bIsTabMenuVisible)
	{
		if (IsValid(Container))
		{
			InHUD->TabMenuWidget->GroundContainerWidget->InitContainer(this, Container);
			InHUD->OpenGroundContainer();
		}
		else
		{
			UE_LOG(LogGame, Warning, TEXT("Container %s is not set up!"), *GetName());
		}
	}
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();

	if (bIsContainer && IsValid(ContainersDataTable) && !ContainerID.IsNone())
	{
		const FContainerData* ContainerData = ContainersDataTable->FindRow<FContainerData>(ContainerID, ContainerID.ToString());
		
		if (ensure(ContainerData != nullptr))
		{
			Container = NewObject<UInventoryContainer>(this);

			Container->CreateContainer(ContainerData->TileHolders, ContainerData->BorderBounds);
			Container->bIsReplicated = true;

			AddReplicatedSubObject(Container);
		}
		else
		{
			UE_LOG(LogGame, Error, TEXT("ContainerID %s doesn't exist in the DT_Containers! Interactable actor name is %s"), *ContainerID.ToString(), *GetName());
		}
	}
	else if (bIsCollectable && IsValid(CollectablesDataTable) && !CollectableID.IsNone())
	{
		const FCollectableData* CollectableData = CollectablesDataTable->FindRow<FCollectableData>(CollectableID, CollectableID.ToString());

		if (ensure(CollectableData != nullptr))
		{
			Collectable.ID = CollectableID;
			Collectable.NumericData = CollectableData->NumericData;
			Collectable.Amount = Amount;
			Collectable.ResourceData = CollectableData->ResourceData;
			private

			private

			private
		}
		else
		{
			UE_LOG(LogGame, Error, TEXT("CollectableID %s doesn't exist in the DT_Collectables! Interactable actor name is %s"), *CollectableID.ToString(), *GetName());
		}
	}
	else if (Collectable.IsValid())
	{
		private
	}
}

void AInteractable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInteractable, Collectable);
	DOREPLIFETIME(AInteractable, Container);
	DOREPLIFETIME(AInteractable, bDirtyFlag);
	DOREPLIFETIME(AInteractable, Mesh);
	DOREPLIFETIME(AInteractable, bIsCollectable);
}

#if WITH_EDITOR
void AInteractable::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(AInteractable, ContainerID))
	{
		if (IsValid(ContainersDataTable))
		{
			if (const FContainerData* ContainerData = ContainersDataTable->FindRow<FContainerData>(ContainerID, ContainerID.ToString()))
			{
				Mesh->SetStaticMesh(ContainerData->Mesh);
			}
		}
	}

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(AInteractable, CollectableID))
	{
		if (IsValid(CollectablesDataTable))
		{
			if (const FCollectableData* CollectableData = CollectablesDataTable->FindRow<FCollectableData>(CollectableID, CollectableID.ToString()))
			{
				Mesh->SetStaticMesh(CollectableData->ResourceData.Mesh);
			}
		}
	}
}
#endif

void AInteractable::OnRep_ContainerContentsChanged()
{
	if (OnContainerContentsChanged.IsBound())
	{
		OnContainerContentsChanged.Broadcast();
	}
}
