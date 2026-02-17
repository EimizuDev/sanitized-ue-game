#pragma once

#include "Engine/DataTable.h"
#include "ContainersDataTable.generated.h"

/**
* Represents a grid section (tile holder) within a container.
*/
USTRUCT()
struct FTileHolder
{
	GENERATED_BODY()

	/**
	* Number of rows in this tile holder. 
	*/
	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 8))
	int8 Rows = 1;

	/**
	* Number of columns in this tile holder.
	*/
	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 9))
	int8 Columns = 1;

	/**
	* Offset from the Left edge of the container grid.
	*/
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 9))
	int8 LeftOffset = 0;

	/**
	* Offset from the top edge of the container grid.
	*/
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 8))
	int8 TopOffset = 0;
};

/**
* Defines the border size and padding of a container's layout.
*/
USTRUCT()
struct FBorderBounds
{
	GENERATED_BODY()

	/**
	* Size (width and height) of the container's border.
	*/
	UPROPERTY(EditAnywhere)
	FVector2D BorderSize{ 0 };

	/**
	* padding applied to the inside of the container border.
	*/
	UPROPERTY(EditAnywhere)
	FMargin BorderPadding{ 0 };
};

/**
* Represents a single container configuration entry in a data table.
*/
USTRUCT()
struct FContainerData : public FTableRowBase
{
	GENERATED_BODY()

	/**
	* List of tile holders inside the container.
	*/
	UPROPERTY(EditAnywhere)
	TArray<FTileHolder> TileHolders;

	/**
	* Visual properties of the container�s borders.
	*/
	UPROPERTY(EditAnywhere)
	FBorderBounds BorderBounds;

	/**
	* 3D mesh used to visually represent the container in the world.
	*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> Mesh = nullptr;
};