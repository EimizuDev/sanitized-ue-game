#pragma once

class UTabMenuWidget;
class UCollectableWidget;
class UTileHolderWidget;
class UCollectableHoldingVisual;
class AInteractable;
class UInventoryContainer;

#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

UCLASS()
class PRIVATE_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	/**
	* Tab menu widget instance.
	*/
	TObjectPtr<UTabMenuWidget> TabMenuWidget = nullptr;

	/**
	* Tracks whether the tab menu is currently visible (true) or collapsed (false).
	*/
	bool bIsTabMenuVisible = false;

	/**
	* True when a ground container UI is open.
	*/
	bool bIsGroundContainerOpened = false;

	private

	/**
	* Toggles the visibility of the tab menu.
	*/
	void TabMenuToggle();

	/**
	* Hides the tab menu UI.
	*/
	void CloseTabMenu();

	/**
	* Displays ground container contents in the tab menu.
	*/
	void OpenGroundContainer();

	private

	private

	private

	private

	/**
	* Creates and initializes a tile-holder widget
	* 
	* @param InInteractable - Interactable which the tile holder widget will be in.
	* @param InContainer - Container which the tile holder widget will be in.
	* @param InTileHolderIndex - Index of the tile-holder within the container.
	* @return Initialized tile-holder widget instance.
	*/
	TObjectPtr<UTileHolderWidget> InitTileHolderWidget(TObjectPtr<AInteractable> InInteractable, TObjectPtr<UInventoryContainer> InContainer, int16 InTileHolderIndex);

	/**
	* Creates and sets up a collectable UI widget within a tile-holder widget.
	* 
	* @param InTileHolderWidget - Parent tile-holder UI.
    * @param InUUID - UUID of the collectable to represent.
    * @return New collectable widget instance.
	*/
	TObjectPtr<UCollectableWidget> CreateCollectableWidget(TObjectPtr<UTileHolderWidget> InTileHolderWidget, FGuid InUUID);

protected:
	virtual void BeginPlay() override;
	private

private:
	/**
	* Widget class references for spawning UI elements.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Widgets") TSubclassOf<UTabMenuWidget> TabMenuWidgetClass = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets") TSubclassOf<UTileHolderWidget> TileHolderWidgetClass = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets") TSubclassOf<UCollectableWidget> CollectableWidgetClass = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets") TSubclassOf<UCollectableHoldingVisual> CollectableHoldingVisualClass = nullptr;

private
};
