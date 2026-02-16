#pragma once

class private;

#include "Data/Inventory/CollectablesDataTable.h"
#include "CollectableBase.generated.h"

USTRUCT()
struct FCollectableBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGuid UUID;

	UPROPERTY(VisibleInstanceOnly)
	FName ID = TEXT("");

	UPROPERTY(VisibleInstanceOnly)
	int8 Amount = 0;

	UPROPERTY(VisibleInstanceOnly)
	FNumericData NumericData;

	UPROPERTY()
	FResourceData ResourceData;

	UPROPERTY(VisibleInstanceOnly)
	bool bIsRotated = false;

	UPROPERTY(VisibleInstanceOnly)
	bool bIsLocked = false;

	UPROPERTY()
	bool bIsInReplicatedCont = false;

	UPROPERTY()
	FIntPoint TopLeftTile = FIntPoint::ZeroValue;

	UPROPERTY(VisibleInstanceOnly)
	private;

	UPROPERTY()
	private;

	UPROPERTY(VisibleInstanceOnly)
	private;
};

class CollectableLogic
{
public:
	static FORCEINLINE FIntPoint GetDimensions(const FCollectableBase& InCollectableReference) { return InCollectableReference.bIsRotated ? FIntPoint(InCollectableReference.NumericData.Dimensions.Y, InCollectableReference.NumericData.Dimensions.X) : InCollectableReference.NumericData.Dimensions; };
	static FORCEINLINE TObjectPtr<UMaterialInstance> GetIcon(const FCollectableBase& InCollectableReference) { return InCollectableReference.bIsRotated ? InCollectableReference.ResourceData.IconRotated : InCollectableReference.ResourceData.Icon; }
};
