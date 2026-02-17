#include "UI/Inventory/CollectableHoldingVisual.h"
#include "Components/CanvasPanelSlot.h"
#include "Data/Inventory/TileHolderData.h"
#include "Components/InventoryComponent.h"

void UCollectableHoldingVisual::RefreshAmount()
{
	const TObjectPtr<UCanvasPanelSlot> ImageCanvasSlot1 = Cast<UCanvasPanelSlot>(CollectableImage1->Slot);
	const TObjectPtr<UCanvasPanelSlot> ImageCanvasSlot2 = Cast<UCanvasPanelSlot>(CollectableImage2->Slot);
	const TObjectPtr<UCanvasPanelSlot> ImageCanvasSlot3 = Cast<UCanvasPanelSlot>(CollectableImage3->Slot);

	if (ImageCanvasSlot1 && ImageCanvasSlot2 && ImageCanvasSlot3)
	{
		private

		if (private)
		{
			ImageCanvasSlot1->SetAlignment(FVector2D(0.5f, 0.5f));

			CollectableImage2->SetVisibility(ESlateVisibility::Hidden);
			CollectableImage3->SetVisibility(ESlateVisibility::Hidden);
		}
		else if (private)
		{
			if (private)
			{
				ImageCanvasSlot1->SetAlignment(FVector2D(0.5f, 0.4f));
				ImageCanvasSlot2->SetAlignment(FVector2D(0.5f, 0.6f));
			}
			else
			{
				ImageCanvasSlot1->SetAlignment(FVector2D(0.4f, 0.5f));
				ImageCanvasSlot2->SetAlignment(FVector2D(0.6f, 0.5f));
			}

			CollectableImage2->SetVisibility(ESlateVisibility::Visible);
			CollectableImage3->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			ImageCanvasSlot2->SetAlignment(FVector2D(0.5f, 0.5f));

			if (private)
			{
				ImageCanvasSlot1->SetAlignment(FVector2D(0.5f, 0.4f));
				ImageCanvasSlot3->SetAlignment(FVector2D(0.5f, 0.6f));
			}
			else
			{
				ImageCanvasSlot1->SetAlignment(FVector2D(0.4f, 0.5f));
				ImageCanvasSlot3->SetAlignment(FVector2D(0.6f, 0.5f));
			}

			CollectableImage2->SetVisibility(ESlateVisibility::Visible);
			CollectableImage3->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

private

private

void UCollectableHoldingVisual::Rotate()
{
	private

	private

	Init();
}

void UCollectableHoldingVisual::NativeConstruct()
{
	Init();
}

void UCollectableHoldingVisual::Init()
{
	private

	const FIntPoint Dimensions = CollectableLogic::GetDimensions(private);
	const FVector2D Size{ Dimensions.X * TileHolderDataLogic::TileSize, Dimensions.Y * TileHolderDataLogic::TileSize };

	BackgroundSizeBox->SetWidthOverride(Size.X);
	BackgroundSizeBox->SetHeightOverride(Size.Y);

	const TObjectPtr<UCanvasPanelSlot> ImageCanvasSlot1 = Cast<UCanvasPanelSlot>(CollectableImage1->Slot);
	const TObjectPtr<UCanvasPanelSlot> ImageCanvasSlot2 = Cast<UCanvasPanelSlot>(CollectableImage2->Slot);
	const TObjectPtr<UCanvasPanelSlot> ImageCanvasSlot3 = Cast<UCanvasPanelSlot>(CollectableImage3->Slot);

	if (ImageCanvasSlot1 && ImageCanvasSlot2 && ImageCanvasSlot3)
	{
		ImageCanvasSlot1->SetSize(Size);
		ImageCanvasSlot2->SetSize(Size);
		ImageCanvasSlot3->SetSize(Size);
	}

	FSlateBrush Brush;
	Brush.SetResourceObject(private);
	Brush.ImageSize = Size;
	CollectableImage1->SetBrush(Brush);
	CollectableImage2->SetBrush(Brush);
	CollectableImage3->SetBrush(Brush);

	private

	RefreshAmount();
}
