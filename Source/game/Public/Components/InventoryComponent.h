#pragma once

class AInteractable;
class AGameHUD;

#include "Components/ActorComponent.h"
#include "Data/Inventory/CollectableBase.h"
#include "InventoryComponent.generated.h"

private

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRIVATE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	private

	private

	private

	private

	/**
	* The HUD of the owner of this inventory component.
	*/
	TObjectPtr<AGameHUD> HUD = nullptr;

	UInventoryComponent();
	
	bool HandlePickup(TObjectPtr<AInteractable> InInteractable);

	private

	private

	private

	private

	void RemoveCollectable();

	void SubtractCollectable(int8 InAmountToSubtract);

	void AddCollectable(const FCollectableBase& InCollectableToAdd);

	int8 StackCollectable(const FCollectableBase& InCollectableToStack, bool InStackOne);

	private

private:
	private

	bool AddCollectableIn(TObjectPtr<AInteractable> InInteractable, private);

	private
};
