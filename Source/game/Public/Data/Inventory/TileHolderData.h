#pragma once

#include "Data/Inventory/CollectableBase.h"
#include "TileHolderData.generated.h"

/**
* Represents a visual line in the tile holder grid, defined by start and end coordinates.
*/
USTRUCT()
struct FLine
{
	GENERATED_BODY()

	/**
	* Starting coordinate of the line.
	*/
	UPROPERTY()
	FVector2D Start{ 0 };

	/**
	* Ending coordinate of the line.
	*/
	UPROPERTY()
	FVector2D End{ 0 };
};

/**
* Holds runtime data for a tile holder, including the collectables it contains, its tile occupancy, and visual line data.
*/
USTRUCT()
struct FTileHolderData
{
	GENERATED_BODY()

public:
	/**
	* All unique collectables currently stored in this tile holder.
	*/
	UPROPERTY(VisibleInstanceOnly)
	TArray<FCollectableBase> Collectables;

	/**
	* Grid of tile occupancy for this tile holder.
	*
	* Each tile holds the UUID of the collectable that occupies it. Multiple tiles may share the same UUID if a single collectable spans several tiles.
	*
	* You can look up collectable details by matching a UUID in this array with an entry in the `Collectables` array.
	*/
	UPROPERTY(VisibleInstanceOnly)
	TArray<FGuid> Tiles; // This could be a pointer instead of FGuid...
	
	/**
	* The layout and dimensions (rows, columns, offsets) of this tile holder.
	*/
	UPROPERTY()
	FTileHolder TileHolderBounds;

	/**
	* Array of lines representing the visual grid layout used for rendering.
	*/
	UPROPERTY()
	TArray<FLine> Lines;
};

/**
* Contains constants and logic functions to prepare tile holders.
*/
class TileHolderDataLogic final
{
public:
	/**
	* The uniform size of a tile within a tile holder grid.
	*/
	inline constexpr static float TileSize = 50.f;

	/**
	* Generates and appends grid lines to the provided tile holder data's `Lines` array.
	* 
	* @param InOutTileHolderData - The tile holder data whose `Lines` array will be populated with generated grid lines. Also used to generate the lines.
	*/
	static void BuildGridLines(FTileHolderData& InOutTileHolderData);
};
