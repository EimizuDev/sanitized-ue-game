#pragma once

#include "Data/Inventory/ContainersDataTable.h"
#include "Engine/DataTable.h"
#include "CollectablesDataTable.generated.h"

USTRUCT()
struct FNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 5))
	int8 MaxStackSize = 1;

	// The amount of tiles the collectable occupies.
	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 8))
	FIntPoint Dimensions = FIntPoint(1, 1);
};

USTRUCT()
struct FResourceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInstance> Icon = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInstance> IconRotated = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> Mesh = nullptr;
};

USTRUCT()
struct private
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool private = false;

	UPROPERTY(EditAnywhere)
	FVector2D BorderSize = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, meta = (EditCondition = private))
	TArray<FTileHolder> private;
};

USTRUCT()
struct FCollectableData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FNumericData NumericData;

	UPROPERTY(EditAnywhere)
	FResourceData ResourceData;

	UPROPERTY(EditAnywhere)
	private private;
};