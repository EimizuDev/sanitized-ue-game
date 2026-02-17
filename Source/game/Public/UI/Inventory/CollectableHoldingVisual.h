#pragma once

class UInventoryComponent;

#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "CollectableHoldingVisual.generated.h"

UCLASS()
class PRIVATE_API UCollectableHoldingVisual : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	* The inventory component of this HUD's owner.
	*/
	TObjectPtr<UInventoryComponent> InventoryComponent;

	/**
	* Refreshes the number of icons to match the current count.
	*/
	void RefreshAmount();

	private

	private

	/**
	* Rotates the collectable visual.
	*/
	void Rotate();

protected:
	virtual void NativeConstruct() override;

private:
	/**
	* Background container sizing the visual.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> BackgroundSizeBox;

	/**
	* First collectable icon.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CollectableImage1;

	/**
	* Second collectable icon.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CollectableImage2;

	/**
	* Third collectable icon.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CollectableImage3;

	/**
	* Performs initial setup of the visual.
	*/
	void Init();
};
