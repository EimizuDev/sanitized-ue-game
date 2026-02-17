#pragma once

class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UInventoryComponent;
class UCommonLegacyMovementSettings;
class AGameHUD;
struct FTileHolderData;
struct FInputActionValue;

#include "MoverSimulationTypes.h"
#include "GameFramework/Pawn.h"
#include "Data/Inventory/ContainersDataTable.h"
#include "PlayerCharacter.generated.h"

/**
* Represents a player-controlled character pawn.
*/
UCLASS()
class PRIVATE_API APlayerCharacter : public APawn, public IMoverInputProducerInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	/**
	* Component managing the player's inventory.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	/**
	* Reference to the player's HUD for UI interactions.
	*/
	UPROPERTY()
	TObjectPtr<AGameHUD> HUD;

	private

	private

	/**
	* Updates the amount of a collectable inside an interactable container on the server.
	* 
	* @param InInteractable - The container to modify.
	* @param InNewAmount - The new amount to set to the collectable.
	*/
	UFUNCTION(Server, Reliable)
	void Server_SetCollectableAmount(AInteractable* InInteractable, int8 InNewAmount);

	UFUNCTION(Server, Reliable)
	void Server_AddCollectable(AInteractable* InInteractable, int16 InTileHolderIndex, FCollectableBase InCollectableToAdd, FIntPoint InDimensions, private, private, FBorderBounds InBorderBounds);

	/**
	* Removes a collectable from a specified tile holder within an interactable container.
	* 
	* @param InInteractable - Target container.
	* @param InTileHolderIndex - Index of the tile holder.
	* @param InCollectableToRemoveUUID - UUID of the collectable to be removed.
	*/
	UFUNCTION(Server, Reliable)
	void Server_RemoveCollectable(AInteractable* InInteractable, int16 InTileHolderIndex, FGuid InCollectableToRemoveUUID);

	/**
	* Modifies the amount of a specific collectable in a container.
	* 
	* @param InInteractable - Target container.
	* @param InTileHolderIndex - Tile holder index.
	* @param InCollectableToModifyUUID - UUID of the collectable to modify.
	* @param InNewAmount - New amount value.
	*/
	UFUNCTION(Server, Reliable)
	void Server_ModifyCollectable(AInteractable* InInteractable, int16 InTileHolderIndex, FGuid InCollectableToModifyUUID, int8 InNewAmount);

	UFUNCTION(Server, Reliable)
	void Server_SpawnCollectable(FVector InSpawnLocation, FCollectableBase InCollectableToSpawn, private, private, FBorderBounds InBorderBounds = {});

	private

protected:
	virtual void ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/**
	* Player�s collision shape
	*/
	UPROPERTY(VisibleAnywhere, Category = Collision)
	TObjectPtr<UCapsuleComponent> CapsuleCollision = nullptr;

	/**
	* Player�s skeletal mesh
	*/
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh = nullptr;

	/**
	* Spring arm for the camera, handling collision
	*/
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraCollision = nullptr;

	/**
	* Follow camera
	*/
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera = nullptr;

	/**
	* Component handling character movement logic
	*/
	UPROPERTY(VisibleAnywhere, Category = Movement)
	TObjectPtr<UMoverComponent> MoverComponent = nullptr;

	/**
	* Default input mapping context for player controls
	*/
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultIMC = nullptr;

	/** Input actions */
	UPROPERTY(EditAnywhere, Category = Input) TObjectPtr<UInputAction> MoveIA = nullptr;
	UPROPERTY(EditAnywhere, Category = Input) TObjectPtr<UInputAction> LookIA = nullptr;
	UPROPERTY(EditAnywhere, Category = Input) TObjectPtr<UInputAction> IncreaseSpeedIA = nullptr;
	UPROPERTY(EditAnywhere, Category = Input) TObjectPtr<UInputAction> DecreaseSpeedIA = nullptr;
	UPROPERTY(EditAnywhere, Category = Input) TObjectPtr<UInputAction> TabMenuIA = nullptr;
	UPROPERTY(EditAnywhere, Category = Input) TObjectPtr<UInputAction> InteractIA = nullptr;
	private
	UPROPERTY(EditAnywhere, Category = Input) TObjectPtr<UInputAction> RotateHeldVisualIA = nullptr;
	UPROPERTY(EditAnywhere, Category = Input) TObjectPtr<UInputAction> DropCollectableIA = nullptr;

	/**
	* Camera rotation sensitivity
	*/
	UPROPERTY(EditAnywhere, Category = Camera)
	float Sensitivity = 0;

	/**
	* Player movement speed range
	*/
	UPROPERTY(EditAnywhere, Category = "Movement|Move Speed")
	float MaxMoveSpeed = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Move Speed")
	float MoveSpeedSensitivity = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Movement|Move Speed")
	float MinMoveSpeed = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "Interaction")
	TArray<TObjectPtr<AActor>> Interactables;

	UPROPERTY(VisibleInstanceOnly, Category = "Interaction")
	TObjectPtr<AInteractable> CurrentInteractable = nullptr;

	/**
	* Allowed class of interactables
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	TSubclassOf<AInteractable> InteractableClass = nullptr;

	/**
	* Used for sizing the interactable check box.
	*/
	const FVector InteractableDetectorsBoxExtent{ 40.f, 55.f, 102.f };

	/**
	* Used for positioning the interactable check box.
	*/
	const FVector2D InteractableDetectorsBoxOffset{ 45.f, 12.f };

	/**
	* Stores the last move direction intent.
	* Used for character orientation even after CachedMoveInputIntent is zero.
	*/
	FVector2D LastAffirmativeMoveInput{ 0 };

	/**
	* Stores current move input direction.
	* Zero-vector when idle.
	*/
	FVector2D CachedMoveInputIntent{ 0 };

	/**
	* Handles move input vector from player.
	*/
	void Move(const FInputActionValue& InValue);

	/**
	* Clears movement intent when no input is detected.
	*/
	void Moved();

	/**
	* Smoothly rotates camera based on input.
	*/
	void Look(const FInputActionValue& InValue);

	/**
	* Increase movement speed
	*/
	void IncreaseMoveSpeed();

	/**
	* Decrease movement speed
	*/
	void DecreaseMoveSpeed();

	/**
	* Sends a server-side command to increase movement speed.
	* 
	* @param InMoverComp - The mover component to adjust.
	* @param InMoveSpeedSensitivity - Amount to change.
	* @param InMaxMoveSpeed - Upper limit of speed.
	*/
	UFUNCTION(Server, Reliable)
	void Server_IncreaseMoveSpeed(UMoverComponent* InMoverComp, float InMoveSpeedSensitivity, float InMaxMoveSpeed);

	/**
	* Sends a server-side command to decrease movement speed.
	* 
	* @param InMoverComp - The mover component to adjust.
	* @param InMoveSpeedSensitivity - Amount to change.
	* @param InMaxMoveSpeed - Lower limit of speed.
	*/
	UFUNCTION(Server, Reliable)
	void Server_DecreaseMoveSpeed(UMoverComponent* InMoverComp, float InMoveSpeedSensitivity, float InMinMoveSpeed);

	/**
	* Performs overlap checks to find nearby interactables. Should be called every Tick().
	*/
	void DetectInteractables();

	/**
	* Picks the closest valid interactable from the detected list.
	*/
	void InteractableHandler();

	/**
	* Determines if the selected interactable is visible (not blocked by obstacles).
	* 
	* @param InClosestInteractable - Candidate actor to validate.
	*/
	void InteractableOcclusionCheck(TObjectPtr<AInteractable> InClosestInteractable);

	/**
	* Executes appropriate behavior (pickup or open) on the current interactable.
	*/
	void HandleInteraction();

	/**
	* Requests server to destroy the specified interactable actor.
	* 
	* @param InOutInteractable - Target actor to destroy.
	*/
	UFUNCTION(Server, Reliable)
	void Server_DestroyInteractable(AInteractable* InOutInteractable);

	/**
	* Toggles visibility of the tab menu UI.
	*/
	void TabMenuToggle();

	private

	private

	void DropCollectable();
};