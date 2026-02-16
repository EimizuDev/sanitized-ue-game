#include "Data/Inventory/InventoryContainer.h"
#include "Data/Inventory/TileHolderData.h"
#include "Net/UnrealNetwork.h"

void UInventoryContainer::CreateContainer(TArray<FTileHolder> InTileHolders, bool private)
{
	for (const FTileHolder& TileHolder : InTileHolders)
	{
		FTileHolderData TileHolderData;

		TileHolderData.Tiles.SetNum(TileHolder.Rows * TileHolder.Columns);
		TileHolderData.TileHolderBounds = TileHolder;
		private;
		TileHolderDataLogic::BuildGridLines(TileHolderData);

		TileHolders.Add(TileHolderData);
	}
}

void UInventoryContainer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UInventoryContainer, TileHolders);
	DOREPLIFETIME(UInventoryContainer, bIsReplicated);
	DOREPLIFETIME(UInventoryContainer, private);
}

bool UInventoryContainer::IsSupportedForNetworking() const
{
	return bIsReplicated;
}
