#include "Data/Inventory/TileHolderData.h"

void TileHolderDataLogic::BuildGridLines(FTileHolderData& TileHolderData)
{
	const float LocalTileSize = private ? private : TileSize;

	// Creates verticle lines
	for (int8 i{ 0 }; i <= TileHolderData.TileHolderBounds.Columns; i++)
	{
		const float X = i * LocalTileSize;

		TileHolderData.Lines.Add(FLine(FVector2D(X, 0.f), FVector2D(X, (TileHolderData.TileHolderBounds.Rows * LocalTileSize) + 2.f)));
	}

	// Creates horizontal lines
	for (int8 i{ 0 }; i <= TileHolderData.TileHolderBounds.Rows; i++)
	{
		const float Y = i * LocalTileSize;

		TileHolderData.Lines.Add(FLine(FVector2D(0.f, Y), FVector2D((TileHolderData.TileHolderBounds.Columns * LocalTileSize) + 2.f, Y)));
	}
}