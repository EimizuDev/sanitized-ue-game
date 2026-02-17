#include "Components/InventoryComponent.h"
#include "Data/Inventory/InventoryContainer.h"
#include "Actors/Interactable.h"
#include "Player/PlayerCharacter.h"
#include "UI/GameHUD.h"
#include "UI/Inventory/CollectableHoldingVisual.h"

UInventoryComponent::UInventoryComponent()
{
    bReplicateUsingRegisteredSubObjectList = true;
    PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::HandlePickup(TObjectPtr<AInteractable> InInteractable)
{
    const FCollectableBase& InteractablesCollectable = InInteractable->Collectable;

    if (!InteractablesCollectable.IsValid()) return false;

    private

    if (private == InteractablesCollectable.ID && private < private)
    {
        const int8 NewStack = private + InteractablesCollectable.Amount;
    
        if (NewStack <= private.NumericData.MaxStackSize)
        {
            private.Amount = NewStack;
            return true;
        }
        else
        {
            if (const TObjectPtr<APlayerCharacter> PlayerCharacter = Cast<APlayerCharacter>(GetOwner()))
            {
                const int8 Overflow = NewStack - private.NumericData.MaxStackSize;
                private.Amount = private.NumericData.MaxStackSize;
                PlayerCharacter->Server_SetCollectableAmount(InInteractable, Overflow);
                return false;
            }
        }
    }

    if (private)
    {
        private
    }
    else
    {
        private
    }

    return false;
}

private

private

private

void UInventoryComponent::RemoveCollectable()
{
    private
}

void UInventoryComponent::SubtractCollectable(int8 InAmountToSubtract)
{
    private.Amount -= InAmountToSubtract;

    if (private)
    {
        private->RefreshAmount();
    }
}

void UInventoryComponent::AddCollectable(const FCollectableBase& InCollectableToAdd)
{
    private = InCollectableToAdd;

    private
}

int8 UInventoryComponent::StackCollectable(const FCollectableBase& InCollectableToStack, bool InStackOne)
{
    private

    if (private.ID == InCollectableToStack.ID && private.Amount < private.NumericData.MaxStackSize)
    {
        const int8 NewStack = private.Amount + (InStackOne ? 1 : InCollectableToStack.Amount);

        if (NewStack <= InCollectableToStack.NumericData.MaxStackSize)
        {
            private.Amount = NewStack;

            return 0;
        }
        else
        {
            private.Amount = InCollectableToStack.NumericData.MaxStackSize;

            return NewStack - InCollectableToStack.NumericData.MaxStackSize;
        }
    }

    return -1;
}

private

bool UInventoryComponent::AddCollectableIn(TObjectPtr<AInteractable> InInteractable, private)
{
    const FCollectableBase& InteractablesCollectable = InInteractable->Collectable;

    if (const TObjectPtr<APlayerCharacter> PlayerCharacter = Cast<APlayerCharacter>(TObjectPtr<AActor>(GetOwner())))
    {
        private

        if (InteractablesCollectable.Amount <= InteractablesCollectable.NumericData.MaxStackSize)
        {
            private = FCollectableBase::CreateFrom(private);

            private

            return true;
        }
        else
        {
            private = FCollectableBase::CreateFrom(private);

            PlayerCharacter->Server_SetCollectableAmount(InInteractable, InInteractable->Collectable.Amount - InInteractable->Collectable.NumericData.MaxStackSize);
        }
    }

    return false;
}

private
