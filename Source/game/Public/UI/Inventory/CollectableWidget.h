#pragma once

class UTileHolderWidget;
struct FCollectableBase;

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "CollectableWidget.generated.h"

/**
* UI widget representing a collectable within a tile holder.
*/
UCLASS()
class PRIVATE_API UCollectableWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* Tile holder widget that contains this collectable UI.
	*/
	TObjectPtr<UTileHolderWidget> TileHolderWidget = nullptr;

	/**
	* Unique identifier of the linked collectable data.
	*/
	FGuid UUID;

	/**
	* Updates the widget�s visuals to reflect the current collectable state.
	*/
	void Refresh();

protected:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	/**
	* Collectable widget's background size box.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> BackgroundSizeBox;

	/**
	* Collectable widget's background border.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> BackgroundBorder;

	/**
	* Primary icon image
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CollectableImage1;

	/**
	* Secondary icon image
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CollectableImage2;

	/**
	* Tertiary icon image
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CollectableImage3;

	/**
	* @return A reference to this widget's corresponding collectable data.
	*/
	FCollectableBase& GetCollectable() const;

	/**
	* Updates how many icons are displayed based on the collectable's stack count.
	*/
	void RefreshAmount();
};
