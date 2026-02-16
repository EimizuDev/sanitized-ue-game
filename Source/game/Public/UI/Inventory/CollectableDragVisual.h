#pragma once

#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Data/Inventory/CollectableBase.h"
#include "CollectableDragVisual.generated.h"

UCLASS()
class NAME_API UCollectableDragVisual : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FCollectableBase CollectableReference;
	bool bIsRotated = false;

	void Init();

	FORCEINLINE FIntPoint GetDimesions() const { return bIsRotated ? FIntPoint(CollectableReference.NumericData.Dimensions.Y, CollectableReference.NumericData.Dimensions.X) : CollectableReference.NumericData.Dimensions; }
	FORCEINLINE void Rotate() { bIsRotated = !bIsRotated; }

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> BackgroundSizeBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image;

	FORCEINLINE TObjectPtr<UMaterialInstance> GetIcon() const { return bIsRotated ? CollectableReference.ResourceData.IconRotated : CollectableReference.ResourceData.Icon; }
};
