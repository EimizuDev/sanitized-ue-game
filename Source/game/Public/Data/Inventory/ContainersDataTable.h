#pragma once

#include "Engine/DataTable.h"
#include "ContainersDataTable.generated.h"

USTRUCT()
struct FTileHolder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 8))
	int8 Rows = 1;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 9))
	int8 Columns = 1;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 9))
	int8 Right = 0;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 8))
	int8 Down = 0;

	// * Recommended to increment/decrement by 5.0f.
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 50.f))
	float RightOffset = 0;

	// * Recommended to increment/decrement by 5.0f.
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 50.f))
	float DownOffset = 0;

	FTileHolder() = default;
	FTileHolder(int8 InRows, int8 InColumns) : Rows(InRows), Columns(InColumns) {}
};

USTRUCT()
struct FContainerData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FTileHolder> TileHolders;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> Mesh = nullptr;
};