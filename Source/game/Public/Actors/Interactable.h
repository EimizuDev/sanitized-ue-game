#pragma once

class UInventoryComponent;
class AGameHUD;
class UWidgetComponent;

#include "GameFramework/Actor.h"
#include "Data/Inventory/CollectableBase.h"
#include "Interactable.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnContainerContentsChanged)

UCLASS()
class PRIVATE_API AInteractable : public AActor
{
	GENERATED_BODY()

public:
	/**
	* Is broadcasted when this container's content changes.
	*/
	FOnContainerContentsChanged OnContainerContentsChanged;

	AInteractable();

	/**
	* Opens this ground container.
	* 
	* @param InHUD - Player's HUD who will open this ground container.
	*/
	void Interact(TObjectPtr<AGameHUD> InHUD);

	/** Marks this ground container dirty thus refreshing this container's tile holders UI for everyone bound to 'OnContainerContentsChanged' delegate. */
	FORCEINLINE void DirtyTheContainer() { bDirtyFlag = !bDirtyFlag; }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	/**
	* Indicates if this interactable functions as a container.
	* 
	* When true:
	* - Enables configuration of container-specific properties.
	* - Disables configuration of collectable-specific properties.
	* 
	* Note: Mutually exclusive with 'bIsCollectable'.
	*/
	UPROPERTY(EditInstanceOnly, Category = "Interactable", meta = (EditCondition = "!bIsCollectable"))
	bool bIsContainer = false;

private:
	/*
	* ID referencing a container in the containers data table.
	* 
	* Only configurable when 'bIsContainer' is true.
	*/
	UPROPERTY(EditInstanceOnly, Category = "Interactable|Container", meta = (EditCondition = "bIsContainer"))
	FName ContainerID = TEXT("");

public:
	/**
	* Indicates if this interactable functions as a collectable.
	* 
	* When true:
	* - Enables configuration of collectable-specific properties.
	* - Disables configuration of container-specific properties.
	* 
	* Note: Mutually exclusive with 'bIsContainer'.
	*/
	UPROPERTY(Replicated, EditInstanceOnly, Category = "Interactable", meta = (EditCondition = "!bIsContainer"))
	bool bIsCollectable = false;

private:
	/**
	* ID referencing a collectable in the collectables data table.
	* 
	* Only configurable if 'bIsCollectable' is true.
	*/
	UPROPERTY(EditInstanceOnly, Category = "Interactable|Collectable", meta = (EditCondition = "bIsCollectable"))
	FName CollectableID = TEXT("");

	/**
	* The quantity of the collectable
	* 
	* Only configurable if 'bIsCollectable' is true.
	*/
	UPROPERTY(EditInstanceOnly, Category = "Interactable|Collectable", meta = (EditCondition = "bIsCollectable", ClampMin = 1, ClampMax = 99))
	int8 Amount = 1;

	/**
	* A data table of all collectables.
	* 
	* Used to look up collectable details by collectableID.
	*/
	TObjectPtr<UDataTable> CollectablesDataTable = nullptr;

	/**
	* A data table of all containers.
	* 
	* Used to look up container details by containerID.
	*/
	TObjectPtr<UDataTable> ContainersDataTable = nullptr;
	
	private

public:
	/**
	* Mesh of the interactable.
	*/
	UPROPERTY(Replicated)
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	/**
	* Details of the collectable.
	*/
	UPROPERTY(Replicated, VisibleInstanceOnly, Category = "Interactable|Collectable")
	FCollectableBase Collectable;

	/**
	* Details of the container.
	*/
	UPROPERTY(Replicated, VisibleInstanceOnly, Category = "Interactable|Container")
	TObjectPtr<UInventoryContainer> Container;

private:
	/**
	* A dirty flag which when toggled refreshes this container's tile holders UI for everyone bound to 'OnContainerContentsChanged' delegate.
	*/
	UPROPERTY(ReplicatedUsing = OnRep_ContainerContentsChanged)
	bool bDirtyFlag = false;

	UFUNCTION()
	void OnRep_ContainerContentsChanged();
};
