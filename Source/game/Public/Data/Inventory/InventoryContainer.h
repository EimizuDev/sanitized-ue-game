#pragma once

struct FTileHolderData;

#include "Data/Inventory/ContainersDataTable.h"
#include "InventoryContainer.generated.h"

UCLASS()
class UInventoryContainer : public UObject
{
	GENERATED_BODY()

public:
	/**
	* True if this container is replicated.
	*/
	UPROPERTY(Replicated)
	bool bIsReplicated = false;

	/**
	* Array containing all tile holder data associated with this container.
	*/
	UPROPERTY(VisibleInstanceOnly, Replicated)
	TArray<FTileHolderData> TileHolders;

	private

	/**
	* Defines the size and padding of the container�s border.
	*/
	UPROPERTY(Replicated)
	FBorderBounds BorderBounds;

	/**
	* Initializes the container with the specified tile holders and border bounds.
	* 
	* @param InTileHolders - The tile holders to be added to this container.
	* @param InBorderBounds - The border size and padding to apply.
	*/
	void CreateContainer(const TArray<FTileHolder>& InTileHolders, FBorderBounds InBorderBounds);

	private

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override;
};