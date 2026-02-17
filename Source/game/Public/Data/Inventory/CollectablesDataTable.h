#pragma once

#include "Data/Inventory/ContainersDataTable.h"
#include "Engine/DataTable.h"
#include "CollectablesDataTable.generated.h"

/**
* Contains numeric properties related to a collectable.
*/
USTRUCT()
struct FNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 5))
	int8 MaxStackSize = 1;

	/**
	* Dimensions (in tiles) that the collectable occupies.
	*/
	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 8))
	FIntPoint Dimensions{ 1, 1 };

	private
};

/**
* Contains references to visual resources associated with the collectable.
*/
USTRUCT()
struct FResourceData
{
	GENERATED_BODY()

	/**
	* Default icon for the collectable.
	*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInstance> Icon = nullptr;

	/**
	* Icon used when the collectable is rotated.
	*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInstance> IconRotated = nullptr;

	/**
	* 3D mesh representing the collectable.
	*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> Mesh = nullptr;
};

private

/**
* Defines a collectable's data entry in the collectables data table.
*/
USTRUCT()
struct FCollectableData : public FTableRowBase
{
	GENERATED_BODY()

	/**
	* Data defining properties such as max stack size, item dimensions, and more.
	*/
	UPROPERTY(EditAnywhere)
	FNumericData NumericData;

	/**
	* Visual and mesh data for the collectable, such as icons and mesh reference.
	*/
	UPROPERTY(EditAnywhere)
	FResourceData ResourceData;

	private

	private
};