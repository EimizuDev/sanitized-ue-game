#pragma once

class UContainerWidget;

#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "TabMenuWidget.generated.h"

UCLASS()
class PRIVATE_API UTabMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	private;

	UPROPERTY(meta = (BindWidget))
	private;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UContainerWidget> GroundContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
