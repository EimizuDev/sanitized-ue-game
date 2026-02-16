#pragma once

struct FTileHolder;
struct FTileHolderData;

#include "InventoryContainer.generated.h"

UCLASS()
class UInventoryContainer : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	bool bIsReplicated = false;

	/*
	* An array which contains all tile holders inside this container.
	*/
	UPROPERTY(VisibleInstanceOnly, Replicated)
	TArray<FTileHolderData> TileHolders;

	UPROPERTY(Replicated)
	bool private = false;

	void CreateContainer(TArray<FTileHolder> InTileHolders, bool private);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override;
};