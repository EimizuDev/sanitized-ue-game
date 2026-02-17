#include "UI/Inventory/ContainerWidget.h"
#include "UI/GameHUD.h"
#include "Data/Inventory/InventoryContainer.h"
#include "UI/Inventory/TileHolderWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Player/PlayerCharacter.h"
#include "Components/InventoryComponent.h"
#include "Data/Inventory/TileHolderData.h"

void UContainerWidget::InitContainer(TObjectPtr<AInteractable> InInteractable, TObjectPtr<UInventoryContainer> InContainerToInit)
{
	if (const TObjectPtr<AGameHUD> HUD = Cast<AGameHUD>(GetOwningPlayer()->GetHUD()))
	{
		if (const TObjectPtr<UCanvasPanelSlot> BorderCanvasSlot = Cast<UCanvasPanelSlot>(ContainerBorder->Slot))
		{
			BorderCanvasSlot->SetSize(InContainerToInit->BorderBounds.BorderSize);
		}

		ContainerBorder->SetPadding(InContainerToInit->BorderBounds.BorderPadding);

		for (int16 i = 0; i < InContainerToInit->TileHolders.Num(); i++)
		{
			PositionTileHolder(HUD->InitTileHolderWidget(InInteractable, InContainerToInit, i));
		}
	}
}

private

private

void UContainerWidget::PositionTileHolder(TObjectPtr<UTileHolderWidget> InTileHolderWidget)
{
	if (const TObjectPtr<UCanvasPanelSlot> AddedTileHolderCanvasSlot = TileHoldersCanvasPanel->AddChildToCanvas(InTileHolderWidget))
	{
		AddedTileHolderCanvasSlot->SetAutoSize(true);

		const FTileHolder TileHolder = InTileHolderWidget->Container->TileHolders[InTileHolderWidget->TileHolderIndex].TileHolderBounds;

		AddedTileHolderCanvasSlot->SetPosition({ TileHolderDataLogic::TileSize * TileHolder.LeftOffset, TileHolderDataLogic::TileSize * TileHolder.TopOffset });
	}
}
