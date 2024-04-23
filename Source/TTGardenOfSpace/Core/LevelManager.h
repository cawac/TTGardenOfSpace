#pragma once

#include "CoreMinimal.h"
#include "CustomLevel.h"
#include "LevelManager.generated.h"

class UBuildingInfo;
class UCustomLevel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangePortalsResources, const int32, NewResources);

UCLASS(Blueprintable)
class ULevelManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
    ULevelManager();

	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;
	
	virtual TStatId GetStatId() const override;
	
	UFUNCTION(BlueprintCallable)
	UCustomLevel* PrevLevel();

	UFUNCTION(BlueprintCallable)
	UCustomLevel* NextLevel();
	
	UFUNCTION(BlueprintCallable)
	UCustomLevel* GetCurrentLevel();

	UFUNCTION(BlueprintCallable)
	void BroadcastPortalResources(const int32 PortalResources);
	
	UFUNCTION(BlueprintCallable)
	void LoadLevel(UCustomLevel* Level);

	UFUNCTION(BlueprintCallable)
	UBuildingInfo* AddBuilding(TSubclassOf<UBuildingInfo> BuildingClass, FTransform BuildingTransform);

protected:
	FOnChangePortalsResources OnChangePortalsResources;

	UPROPERTY(BlueprintReadOnly)
	TMap<int32, UCustomLevel*> Levels;
	
	UCustomLevel* GetLevel(int32 NumberOfLevel);

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentNumberOfLevel = 0;
	
	int32 PortalResources = 0;

	float TimeSinceLastTick = 0.f;
};