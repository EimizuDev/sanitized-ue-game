#pragma once

class UInventoryContainer;
class UTileHolderWidget;
class AInteractable;

#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "ContainerWidget.generated.h"

/**
* UI widget representing a container.
* Displays tile holder widgets.
*/
UCLASS()
class PRIVATE_API UContainerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* Canvas panel where all tile holder widgets are added and laid out.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> TileHoldersCanvasPanel;

	/**
	* Sets up the container's visual border and spawns the necessary tile holder widgets inside it.
	* 
	* @param InInteractable - The interactable instance owning this container.
	* @param InContainerToInit - The inventory container data to initialize from.
	*/
	void InitContainer(TObjectPtr<AInteractable> InInteractable, TObjectPtr<UInventoryContainer> InContainerToInit);

protected:
	private
	private

private:
	/**
	* Container widget's border.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> ContainerBorder;

	/**
	* Positions a tile holder widget within the container UI based on its layout data.
	* 
	* @param InTileHolderWidget - The widget representing a tile holder to be placed.
	*/
	void PositionTileHolder(TObjectPtr<UTileHolderWidget> InTileHolderWidget);
};
