#include "UI/Inventory/CollectableDragVisual.h"
#include "Components/CanvasPanelSlot.h"

void UCollectableDragVisual::Init()
{
	const FVector2D Size{ GetDimesions().X * /*size*/, GetDimesions().Y * /*size*/ };
	
	BackgroundSizeBox->SetWidthOverride(Size.X);
	BackgroundSizeBox->SetHeightOverride(Size.Y);

	if (const TObjectPtr<UCanvasPanelSlot> CanvasSlot = Cast<UCanvasPanelSlot>(Image->Slot))
	{
		CanvasSlot->SetSize(FVector2D(Size));
	}

	FSlateBrush Brush;
	Brush.SetResourceObject(GetIcon());
	Brush.ImageSize = Size;
	Image->SetBrush(Brush);
}
