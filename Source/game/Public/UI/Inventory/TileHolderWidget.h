#pragma once

class UInventoryComponent;
class UInventoryContainer;
class AInteractable;
struct FCollectableBase;

#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "TileHolderWidget.generated.h"

struct FMousePositionInTile
{
	bool Right = false;
	bool Down = false;
};

/**
* Widget representing a single tile-holder in the UI. Manages visualization of collectables and other.
*/
UCLASS()
class PRIVATE_API UTileHolderWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* Inventory component associated with the owner of this widget.
	*/
	TObjectPtr<UInventoryComponent> InventoryComponent = nullptr;

	TObjectPtr<AInteractable> Interactable = nullptr;

	/**
	* Reference to the inventory container data backing this tile-holder UI.
	*/
	TObjectPtr<UInventoryContainer> Container = nullptr;

	/**
	* Index of this tile-holder within the container's array of tile holders.
	*/
	int16 TileHolderIndex = 0;

	/**
	* Remove a collectable from the tile holder based on its UUID.
	* @param InCollectableToRemoveUUID � UUID of the collectable to remove.
	*/
	void RemoveCollectable(FGuid InCollectableToRemoveUUID);

	/**
	* Updates the UI to reflect container changes � e.g. added, removed, or modified collectables.
	*/
	void Refresh();

	/**
	* Modify the amount of a specific collectable by UUID.
	* 
	* @param InAmountToSet � The amount to apply.
	* @param InCollectableToModifyUUID � Unique identifier of the target collectable.
	*/
	void ModifyCollectable(int8 InAmountToSet, FGuid InCollectableToModifyUUID);

	int8 StackCollectable(const FCollectableBase& InCollectableOn, bool InStackOne);

	/**
	* Maps a tile grid coordinate to a linear index.
	* 
	* @param InColumns � Number of columns in holder layout.
	* @param InTile � (X, Y) tile coordinate.
	* @return Index corresponding to array position.
	*/
	FORCEINLINE static int8 TileToIndex(int8 InColumns, FIntPoint InTile) { return InTile.X + (InTile.Y * InColumns); }

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	/**
	* Border of the tile holder widget.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> TileHolderBorder;

	/**
	* Canvas panel of the tile holder, which holds all collectable widgets.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> TileHolderCanvasPanel;

	private

	/**
	* Checks if the current visual placement area is free from overlap and within grid bounds.
	* @return True if all visual tiles can be placed; false otherwise.
	*/
	bool IsRoomAvailable() const;

	/**
	* Place a collectable into this tile-holder at the current hover location.
	* @param InCollectable � Reference collectable to add.
	* @param InAmount � Quantity to add.
	*/
	void AddCollectable(const FCollectableBase& InCollectable, int8 InAmount);

	/**
	* Invoked when the container content changes due to replication; forces UI update.
	*/
	FORCEINLINE void OnContainerContentsChanged() { Refresh(); }
};
