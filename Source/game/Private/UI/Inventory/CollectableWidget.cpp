#include "UI/Inventory/CollectableWidget.h"
#include "Data/Inventory/CollectableBase.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/Inventory/CollectableHoldingVisual.h"
#include "UI/GameHUD.h"
#include "UI/Inventory/TileHolderWidget.h"
#include "Data/Inventory/TileHolderData.h"
#include "Data/Inventory/InventoryContainer.h"
#include "Components/InventoryComponent.h"

void UCollectableWidget::Refresh()
{
	const FCollectableBase& Collectable = GetCollectable();

	const FIntPoint Dimensions = CollectableLogic::GetDimensions(Collectable);
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
	Brush.SetResourceObject(CollectableLogic::GetIcon(Collectable));
	Brush.ImageSize = Size;
	CollectableImage1->SetBrush(Brush);
	CollectableImage2->SetBrush(Brush);
	CollectableImage3->SetBrush(Brush);

	RefreshAmount();
}

void UCollectableWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	BackgroundBorder->SetBrushColor(FLinearColor(0.3, 0.3, 0.3, 0.5));

	private
}

void UCollectableWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	BackgroundBorder->SetBrushColor(FLinearColor(0, 0, 0, 0.5));

	private
}

FReply UCollectableWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	const FCollectableBase Collectable = GetCollectable();
	private

	if (private)
	{
		if (private)
		{
			if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton && Collectable.Amount > 1)
			{
				const FCollectableBase& NewCollectable = FCollectableBase::CreateFrom(Collectable, 1, false, { 0, 0 });

				TileHolderWidget->ModifyCollectable(Collectable.Amount - 1, Collectable.UUID);
				TileHolderWidget->InventoryComponent->AddCollectable(NewCollectable);

				if (!TileHolderWidget->Container->bIsReplicated) RefreshAmount();
			}
			else if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
			{
				FCollectableBase CollectableCopy = FCollectableBase::CreateFrom(Collectable, Collectable.Amount, false, { 0, 0 });

				private

				TileHolderWidget->InventoryComponent->AddCollectable(CollectableCopy);
				TileHolderWidget->RemoveCollectable(Collectable.UUID);
			}
		}
	}
	else
	{
		// This order matters
		if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && InMouseEvent.IsLeftShiftDown())
		{
			const int8 Overflow = TileHolderWidget->InventoryComponent->StackCollectable(Collectable, false);

			if (Overflow != -1)
			{
				if (Overflow != 0)
				{
					TileHolderWidget->ModifyCollectable(Overflow, Collectable.UUID);

					if (!TileHolderWidget->Container->bIsReplicated) RefreshAmount();
				}
				else
				{
					TileHolderWidget->RemoveCollectable(Collectable.UUID);
				}

				private;
			}

			private
		}
		else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton && InMouseEvent.IsLeftShiftDown())
		{
			if (TileHolderWidget->InventoryComponent->StackCollectable(Collectable, true) != -1)
			{
				if (Collectable.Amount > 1)
				{
					TileHolderWidget->ModifyCollectable(Collectable.Amount - 1, Collectable.UUID);

					if (!TileHolderWidget->Container->bIsReplicated) RefreshAmount();
				}
				else
				{
					TileHolderWidget->RemoveCollectable(Collectable.UUID);
				}

				private;
			}

			private
		}
		else if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			const int8 AmountToSubtract = TileHolderWidget->StackCollectable(Collectable, false);

			if (AmountToSubtract != -1)
			{
				if (AmountToSubtract != 0)
				{
					TileHolderWidget->InventoryComponent->SubtractCollectable(AmountToSubtract);
					private
				}
				else
				{
					TileHolderWidget->InventoryComponent->RemoveCollectable();
				}

				if (!TileHolderWidget->Container->bIsReplicated) RefreshAmount();
			}
			else private
		}
		else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			if (TileHolderWidget->StackCollectable(Collectable, true) != -1)
			{
				if (private)
				{
					TileHolderWidget->InventoryComponent->SubtractCollectable(1);
					private
				}
				else
				{
					TileHolderWidget->InventoryComponent->RemoveCollectable();
				}

				if (!TileHolderWidget->Container->bIsReplicated) RefreshAmount();
			}
			else private
		}
	}

	private

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent).Handled();
}

FCollectableBase& UCollectableWidget::GetCollectable() const
{
	for (FCollectableBase& Collectable : TileHolderWidget->Container->TileHolders[TileHolderWidget->TileHolderIndex].Collectables)
	{
		if (Collectable.UUID == UUID)
		{
			return Collectable;
		}
	}

	checkNoEntry();
	static FCollectableBase DummyCollectable;
	return DummyCollectable;
}

void UCollectableWidget::RefreshAmount()
{
	const TObjectPtr<UCanvasPanelSlot> ImageCanvasSlot1 = Cast<UCanvasPanelSlot>(CollectableImage1->Slot);
	const TObjectPtr<UCanvasPanelSlot> ImageCanvasSlot2 = Cast<UCanvasPanelSlot>(CollectableImage2->Slot);
	const TObjectPtr<UCanvasPanelSlot> ImageCanvasSlot3 = Cast<UCanvasPanelSlot>(CollectableImage3->Slot);

	if (ImageCanvasSlot1 && ImageCanvasSlot2 && ImageCanvasSlot3)
	{
		const FCollectableBase& Collectable = GetCollectable();

		if (Collectable.Amount <= 1)
		{
			ImageCanvasSlot1->SetAlignment(FVector2D(0.5f, 0.5f));

			CollectableImage2->SetVisibility(ESlateVisibility::Hidden);
			CollectableImage3->SetVisibility(ESlateVisibility::Hidden);
		}
		else if (Collectable.Amount == 2)
		{
			if (Collectable.bIsRotated)
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

			if (Collectable.bIsRotated)
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
