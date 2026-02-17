#include "UI/Inventory/TileHolderWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/InventoryComponent.h"
#include "UI/GameHUD.h"
#include "UI/Inventory/CollectableWidget.h"
#include "Data/Inventory/TileHolderData.h"
#include "UI/Inventory/CollectableHoldingVisual.h"
#include "Actors/Interactable.h"
#include "Player/PlayerCharacter.h"
#include "Data/Inventory/InventoryContainer.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UTileHolderWidget::RemoveCollectable(FGuid InCollectableToRemoveUUID)
{
	if (Container->bIsReplicated)
	{
		if (const TObjectPtr<APlayerCharacter> PlayerCharacter = Cast<APlayerCharacter>(InventoryComponent->GetOwner()))
		{
			PlayerCharacter->Server_RemoveCollectable(Interactable, TileHolderIndex, InCollectableToRemoveUUID);
		}
	}
	else
	{
		FTileHolderData& TileHolderData = Container->TileHolders[TileHolderIndex];

		for (FGuid& Tile : TileHolderData.Tiles)
		{
			if (Tile == InCollectableToRemoveUUID)
			{
				Tile.Invalidate();
			}
		}

		for (int16 i = 0; i < TileHolderData.Collectables.Num(); i++)
		{
			if (TileHolderData.Collectables[i].UUID == InCollectableToRemoveUUID)
			{
				TileHolderData.Collectables.RemoveAt(i);
				TileHolderData.Collectables.Shrink();
				break;
			}
		}

		Refresh();
	}
}

void UTileHolderWidget::Refresh()
{
	TileHolderCanvasPanel->ClearChildren();

	for (const FCollectableBase& Collectable : Container->TileHolders[TileHolderIndex].Collectables)
	{
		const TObjectPtr<UCollectableWidget> NewCollectableWidget = InventoryComponent->HUD->CreateCollectableWidget(this, Collectable.UUID);

		NewCollectableWidget->Refresh();

		if (const TObjectPtr<UCanvasPanelSlot> AddedCollectableCanvasSlot = Cast<UCanvasPanelSlot>(TileHolderCanvasPanel->AddChild(NewCollectableWidget)))
		{
			AddedCollectableCanvasSlot->SetAutoSize(true);
			AddedCollectableCanvasSlot->SetPosition({ Collectable.TopLeftTile.X * TileHolderDataLogic::TileSize, Collectable.TopLeftTile.Y * TileHolderDataLogic::TileSize });
		}
	}
}

void UTileHolderWidget::ModifyCollectable(int8 InAmountToSet, FGuid InCollectableToModifyUUID)
{
	if (Container->bIsReplicated)
	{
		if (const TObjectPtr<APlayerCharacter> PlayerCharacter = Cast<APlayerCharacter>(InventoryComponent->GetOwner()))
		{
			PlayerCharacter->Server_ModifyCollectable(Interactable, TileHolderIndex, InCollectableToModifyUUID, InAmountToSet);
		}
	}
	else
	{
		for (FCollectableBase& Collectable : Container->TileHolders[TileHolderIndex].Collectables)
		{
			if (Collectable.UUID == InCollectableToModifyUUID)
			{
				Collectable.Amount = InAmountToSet;
				break;
			}
		}
	}
}

int8 UTileHolderWidget::StackCollectable(const FCollectableBase& InCollectableOn, bool InStackOne)
{
	private

	if (InCollectableOn.ID == private && InCollectableOn.Amount < InCollectableOn.NumericData.MaxStackSize)
	{
		const int8 NewStack = InCollectableOn.Amount + (InStackOne ? 1 : private);

		const bool bFills = NewStack <= InCollectableOn.NumericData.MaxStackSize;

		ModifyCollectable(bFills ? NewStack : InCollectableOn.NumericData.MaxStackSize, InCollectableOn.UUID);

		return bFills ? 0 : private - (NewStack - InCollectableOn.NumericData.MaxStackSize);
	}

	return -1;
}

void UTileHolderWidget::NativeConstruct()
{
	FTileHolder TileHolder = Container->TileHolders[TileHolderIndex].TileHolderBounds;

	if (const TObjectPtr<UCanvasPanelSlot> BorderCanvasSlot = Cast<UCanvasPanelSlot>(TileHolderBorder->Slot))
	{
		BorderCanvasSlot->SetSize({ TileHolder.Columns * TileHolderDataLogic::TileSize, TileHolder.Rows * TileHolderDataLogic::TileSize });

		if (Container->bIsReplicated)
		{
			Interactable->OnContainerContentsChanged.AddUObject(this, &UTileHolderWidget::OnContainerContentsChanged);
		}

		Refresh();
	}
}

void UTileHolderWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(Interactable))
	{
		Interactable->OnContainerContentsChanged.RemoveAll(this);
	}
}

int32 UTileHolderWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	LayerId = FMath::RoundToInt(60 / FMath::Pow(UWidgetLayoutLibrary::GetViewportScale(this), 0.62f));

	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	if (!Container) return LayerId;

	for (const FLine Line : Container->TileHolders[TileHolderIndex].Lines)
	{
		const TArray<FVector2D> Positions{ Line.Start, Line.End };
		
		FSlateDrawElement::MakeLines(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			Positions,
			ESlateDrawEffect::None,
			FLinearColor(0.6f, 0.6f, 0.6f, 0.6f),
			false,
			1.0f
		);
	}

	return LayerId;
}

FReply UTileHolderWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (!IsValid(private)) return Reply;

	private

	private

	if (IsRoomAvailable())
	{
		// Drop a split collectable
		if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton && Collectable.Amount > 1)
		{
			AddCollectable(Collectable, 1);
			InventoryComponent->SubtractCollectable(1);
		}
		// Drop a collectable
		else if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			AddCollectable(Collectable, Collectable.Amount);
			InventoryComponent->RemoveCollectable();

			private
		}
	}

	return Reply;
}

FReply UTileHolderWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (private)
	{
		const FVector2D MousePosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
		const FMousePositionInTile Result{ FMath::Fmod(MousePosition.X, TileHolderDataLogic::TileSize) > (TileHolderDataLogic::TileSize / 2.f), FMath::Fmod(MousePosition.Y, TileHolderDataLogic::TileSize) > (TileHolderDataLogic::TileSize / 2.f) };

		const FIntPoint Dimension = private;

		const int8 X = Dimension.X - (Result.Right ? 1 : 0);
		const int8 Y = Dimension.Y - (Result.Down ? 1 : 0);

		private
	}

	return Super::NativeOnMouseMove(InGeometry, InMouseEvent);
}

bool UTileHolderWidget::IsRoomAvailable() const
{
	const FTileHolderData& TileHolderData = Container->TileHolders[TileHolderIndex];

	const FIntPoint Dimensions = private;

	for (int16 x = private.X; x < private.X + Dimensions.X; x++)
	{
		for (int16 y = private.Y; y < private.Y + Dimensions.Y; y++)
		{
			if (x >= 0 && x < TileHolderData.TileHolderBounds.Columns && y >= 0 && y < TileHolderData.TileHolderBounds.Rows)
			{
				if (TileHolderData.Tiles[TileToIndex(Container->TileHolders[TileHolderIndex].TileHolderBounds.Columns, {x, y})].IsValid()) return false;
			}
			else return false;
		}
	}

	return true;
}

void UTileHolderWidget::AddCollectable(const FCollectableBase& InCollectable, int8 InAmount)
{
	FCollectableBase CollectableToAddCopy = FCollectableBase::CreateFrom(InCollectable, InAmount, Container->bIsReplicated, private);

	if (Container->bIsReplicated)
	{
		if (const TObjectPtr<APlayerCharacter> PlayerCharacter = Cast<APlayerCharacter>(InventoryComponent->GetOwner()))
		{
			private

			PlayerCharacter->Server_AddCollectable(Interactable, TileHolderIndex, CollectableToAddCopy, CollectableLogic::GetDimensions(InCollectable), !InCollectable.bIsInReplicatedCont && private, private, private);
		}
	}
	else
	{
		private

		const FIntPoint Dimensions = CollectableLogic::GetDimensions(InCollectable);

		for (int16 x = private.X; x < private.X + Dimensions.X; x++)
		{
			for (int16 y = private.Y; y < private.Y + Dimensions.Y; y++)
			{
				Container->TileHolders[TileHolderIndex].Tiles[TileToIndex(Container->TileHolders[TileHolderIndex].TileHolderBounds.Columns, { x, y })] = CollectableToAddCopy.UUID;
			}
		}

		Container->TileHolders[TileHolderIndex].Collectables.Add(CollectableToAddCopy);

		Refresh();
	}
}
