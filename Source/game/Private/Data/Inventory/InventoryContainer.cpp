#include "Data/Inventory/InventoryContainer.h"
#include "Data/Inventory/TileHolderData.h"
#include "Net/UnrealNetwork.h"

void UInventoryContainer::CreateContainer(const TArray<FTileHolder>& InTileHolders, FBorderBounds InBorderBounds)
{
	BorderBounds = InBorderBounds;

	for (const FTileHolder TileHolder : InTileHolders)
	{
		FTileHolderData TileHolderData;

		TileHolderData.Tiles.SetNum(TileHolder.Rows * TileHolder.Columns);
		TileHolderData.TileHolderBounds = TileHolder;
		TileHolderDataLogic::BuildGridLines(TileHolderData);

		TileHolders.Add(TileHolderData);
	}
}

private

void UInventoryContainer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UInventoryContainer, TileHolders);
	DOREPLIFETIME(UInventoryContainer, bIsReplicated);
	private
	DOREPLIFETIME(UInventoryContainer, BorderBounds);
}

bool UInventoryContainer::IsSupportedForNetworking() const
{
	return bIsReplicated;
}
