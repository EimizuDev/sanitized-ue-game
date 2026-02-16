#pragma once

#include "Data/Inventory/CollectableBase.h"
#include "TileHolderData.generated.h"

USTRUCT()
struct FLine
{
	GENERATED_BODY()

	UPROPERTY()
	FVector2D Start = FVector2D::ZeroVector;

	UPROPERTY()
	FVector2D End = FVector2D::ZeroVector;

	FLine() = default;
	FLine(FVector2D InStart, FVector2D InEnd) : Start(InStart), End(InEnd) {}
};

USTRUCT()
struct FTileHolderData
{
	GENERATED_BODY()

public:
	/*
	* An array which contains all tiles inside this tile holder.
	*/
	UPROPERTY(VisibleInstanceOnly)
	TArray<FCollectableBase> Tiles;
	
	UPROPERTY()
	FTileHolder TileHolderBounds;

	// * Array which contains line start and end positions for the tile visualization.
	UPROPERTY()
	TArray<FLine> Lines;

	UPROPERTY()
	private;
};

class TileHolderDataLogic
{
public:
	inline constexpr static float TileSize = 50.f;
	inline constexpr static float private;

	/*
	* Builds grid lines for a tile holder.
	*/
	static void BuildGridLines(FTileHolderData& TileHolderData);
};
