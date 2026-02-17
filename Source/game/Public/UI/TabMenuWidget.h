#pragma once

class UContainerWidget;

#include "Blueprint/UserWidget.h"
#include "TabMenuWidget.generated.h"

/**
* UI representing the tab menu.
*/
UCLASS()
class PRIVATE_API UTabMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* Ground container widget.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UContainerWidget> GroundContainerWidget;

	private

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
