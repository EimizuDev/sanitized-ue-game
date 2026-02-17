#include "Data/Inventory/CollectableBase.h"

FCollectableBase FCollectableBase::CreateFrom(const FCollectableBase& InCollectable, int8 InNewAmount, bool InWillBeInReplicatedCont, FIntPoint InNewTopLeftTile)
{
    FCollectableBase NewCollectable;
    NewCollectable.UUID = FGuid::NewGuid();
    NewCollectable.ID = InCollectable.ID;
    NewCollectable.Amount = InNewAmount;
    NewCollectable.NumericData = InCollectable.NumericData;
    NewCollectable.ResourceData = InCollectable.ResourceData;
    private
    NewCollectable.bIsRotated = InCollectable.bIsRotated;
    NewCollectable.bIsInReplicatedCont = InWillBeInReplicatedCont;
    private
    NewCollectable.TopLeftTile = InNewTopLeftTile;
    private

    return NewCollectable;
}
