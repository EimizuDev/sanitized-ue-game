#include "UI/TabMenuWidget.h"
#include "UI/GameHUD.h"
#include "UI/Inventory/CollectableDragVisual.h"

FReply UTabMenuWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return Reply.Handled();
}

FReply UTabMenuWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (const TObjectPtr<AGameHUD> HUD = Cast<AGameHUD>(GetOwningPlayer()->GetHUD()))
	{
		if (IsValid(HUD->CurrentDraggedCollectable.Visual))
		{
			HUD->OnDropClear();
		}
	}
	
	return Reply.Handled();
}