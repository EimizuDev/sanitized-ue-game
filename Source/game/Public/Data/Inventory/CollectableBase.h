#pragma once

class UInventoryContainer;

#include "Data/Inventory/CollectablesDataTable.h"
#include "CollectableBase.generated.h"

USTRUCT()
struct FCollectableBase
{
	GENERATED_BODY()

public:
	/**
	* The unique ID for this collectable.
	*/
	UPROPERTY()
	FGuid UUID;

	/**
	* Identifier for the collectable type, matching an entry in the collectables data table.
	*/
	UPROPERTY(VisibleInstanceOnly)
	FName ID = TEXT("");

	/**
	* The number of items in this collectable�s stack.
	*/
	UPROPERTY(VisibleInstanceOnly)
	int8 Amount = 0;

	/**
	* Data defining properties such as max stack size, item dimensions, and more.
	*/
	UPROPERTY(VisibleInstanceOnly)
	FNumericData NumericData;

	/**
	* Visual and mesh data for the collectable, such as icons and mesh reference.
	*/
	UPROPERTY(VisibleInstanceOnly)
	FResourceData ResourceData;

	private

	UPROPERTY(VisibleInstanceOnly)
	bool bIsInReplicatedCont = false;

	/**
	* Top-left tile coordinate in the tile holder representing this collectable's position.
	*/
	UPROPERTY(VisibleInstanceOnly)
	FIntPoint TopLeftTile{ 0 };

	private

	/**
	* True if the collectable is rotated.
	*/
	UPROPERTY(VisibleInstanceOnly)
	bool bIsRotated = false;

	private
	
	/**
	* Creates a new collectable from the passed in arguments.
	*
	* @param InCollectable - the collectable to make a copy out of.
	* @param InNewAmount - a new amount for the new collectable.
	* @param InWillBeInReplicatedCont - is the container that the copy will go to replicated?
	* @param InNewTopLeftTile - new top left tile.
	* @return the copy of the new collectable.
	*/
	static FCollectableBase CreateFrom(const FCollectableBase& InCollectable, int8 InNewAmount, bool InWillBeInReplicatedCont, FIntPoint InNewTopLeftTile);

	/**
	* Returns true if the collectable is valid (i.e., has a non-empty ID).
	*/
	FORCEINLINE bool IsValid() const { return !ID.IsNone(); }
};

class CollectableLogic final
{
public:
	/**
	* Get the dimensions of the passed in collectable.
	* 
	* @param InCollectable - the collectable to get the dimensions from.
	* @return the dimensions received from InCollectable.
	*/
	static FORCEINLINE FIntPoint GetDimensions(const FCollectableBase& InCollectable) { return InCollectable.bIsRotated ? FIntPoint(InCollectable.NumericData.Dimensions.Y, InCollectable.NumericData.Dimensions.X) : InCollectable.NumericData.Dimensions; };
	
	/**
	* Gets the icon from the passed in collectable
	* 
	* @param InCollectable - the collectable to get the icon from.
	* @return the icon from InCollectable.
	*/
	static FORCEINLINE TObjectPtr<UMaterialInstance> GetIcon(const FCollectableBase& InCollectable) { return InCollectable.bIsRotated ? InCollectable.ResourceData.IconRotated : InCollectable.ResourceData.Icon; }
};
