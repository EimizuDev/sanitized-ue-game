#pragma once

#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "CollectableDragVisual.generated.h"

UCLASS()
class /*name*/_API UCollectableDragVisual : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FCollectableBase CollectableReference;
	bool bIsRotated = false;

	void Init();

	FORCEINLINE FIntPoint GetDimesions() const { return bIsRotated ? FIntPoint(/*value*/, /*value*/) : /*value*/; }
	FORCEINLINE void Rotate() { bIsRotated = !bIsRotated; }

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> BackgroundSizeBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image;

	FORCEINLINE TObjectPtr<UMaterialInstance> GetIcon() const { return bIsRotated ? /*value*/ : /*value*/; }
};
