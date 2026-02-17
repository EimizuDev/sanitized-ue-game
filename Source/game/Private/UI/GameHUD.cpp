#include "UI/GameHUD.h"
#include "UI/TabMenuWidget.h"
#include "Player/PlayerCharacter.h"
#include "UI/Inventory/ContainerWidget.h"
#include "UI/Inventory/CollectableWidget.h"
#include "Logs.h"
#include "Data/Inventory/InventoryContainer.h"
#include "UI/Inventory/TileHolderWidget.h"
#include "UI/Inventory/CollectableHoldingVisual.h"

void AGameHUD::TabMenuToggle()
{
    if (IsValid(TabMenuWidget))
    {
        if (bIsTabMenuVisible)
        {
            CloseTabMenu();
        }
        else
        {
            TabMenuWidget->SetVisibility(ESlateVisibility::Visible);
            bIsTabMenuVisible = true;

            const FInputModeGameAndUI InputMode;
            GetOwningPlayerController()->SetInputMode(InputMode);
            GetOwningPlayerController()->SetShowMouseCursor(true);
        }
    }
}

void AGameHUD::CloseTabMenu()
{
    TabMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
    bIsTabMenuVisible = false;

    TabMenuWidget->GroundContainerWidget->SetVisibility(ESlateVisibility::Hidden);
    bIsGroundContainerOpened = false;
    TabMenuWidget->GroundContainerWidget->TileHoldersCanvasPanel->ClearChildren();

    private

    private

    const FInputModeGameOnly InputMode;
    GetOwningPlayerController()->SetInputMode(InputMode);
    GetOwningPlayerController()->SetShowMouseCursor(false);
}

void AGameHUD::OpenGroundContainer()
{
    if (IsValid(TabMenuWidget))
    {
        TabMenuWidget->GroundContainerWidget->SetVisibility(ESlateVisibility::Visible);
        bIsGroundContainerOpened = true;

        TabMenuWidget->SetVisibility(ESlateVisibility::Visible);
        bIsTabMenuVisible = true;

        const FInputModeGameAndUI InputMode;
        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(true);
    }
}

private

private

private

private

TObjectPtr<UTileHolderWidget> AGameHUD::InitTileHolderWidget(TObjectPtr<AInteractable> InInteractable, TObjectPtr<UInventoryContainer> InContainer, int16 InTileHolderIndex)
{
    if (TileHolderWidgetClass)
    {
        if (const TObjectPtr<UTileHolderWidget> NewTileHolderWidget = CreateWidget<UTileHolderWidget>(GetWorld(), TileHolderWidgetClass))
        {
            if (const TObjectPtr<APlayerCharacter> PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerController()->GetPawn()))
            {
                NewTileHolderWidget->InventoryComponent = PlayerCharacter->InventoryComponent;
                NewTileHolderWidget->Interactable = InInteractable;
                NewTileHolderWidget->Container = InContainer;
                NewTileHolderWidget->TileHolderIndex = InTileHolderIndex;
                return NewTileHolderWidget;
            }
        }
    }

    return nullptr;
}

TObjectPtr<UCollectableWidget> AGameHUD::CreateCollectableWidget(TObjectPtr<UTileHolderWidget> InTileHolderWidget, FGuid InUUID)
{
    if (CollectableWidgetClass)
    {
        if (const TObjectPtr<UCollectableWidget> NewCollectableWidget = CreateWidget<UCollectableWidget>(GetWorld(), CollectableWidgetClass))
        {
            NewCollectableWidget->TileHolderWidget = InTileHolderWidget;
            NewCollectableWidget->UUID = InUUID;
            return NewCollectableWidget;
        }
    }

    return nullptr;
}

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();

    if (IsValid(TabMenuWidgetClass))
    {
        TabMenuWidget = CreateWidget<UTabMenuWidget>(GetWorld(), TabMenuWidgetClass);
        if (IsValid(TabMenuWidget))
        {
            TabMenuWidget->AddToViewport();
        }
        else
        {
            UE_LOG(LogGame, Error, TEXT("Failed to create TabMenuWidget!"));
        }
    }
}

private