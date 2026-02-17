#include "Data/Inventory/TileHolderData.h"

void TileHolderDataLogic::BuildGridLines(FTileHolderData& InOutTileHolderData)
{
	// Creates verticle lines
	for (int8 i = 0; i <= InOutTileHolderData.TileHolderBounds.Columns; i++)
	{
		const float X = i * TileSize;

		InOutTileHolderData.Lines.Add({ {X, 0.f}, {X, (InOutTileHolderData.TileHolderBounds.Rows * TileSize) + 1.5f} });
	}

	// Creates horizontal lines
	for (int8 i = 0; i <= InOutTileHolderData.TileHolderBounds.Rows; i++)
	{
		const float Y = i * TileSize;

		InOutTileHolderData.Lines.Add({ {0.f, Y}, {(InOutTileHolderData.TileHolderBounds.Columns * TileSize) + 1.5f, Y} });
	}
}