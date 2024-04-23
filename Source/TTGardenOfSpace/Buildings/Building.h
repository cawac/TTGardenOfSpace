#pragma once

#include "CoreMinimal.h"
#include "BuildingInfo.h"
#include "Building.generated.h"

class UTextRenderComponent;

UCLASS(BlueprintType)
class ABuilding: public AActor
{
	GENERATED_BODY()

public:
	ABuilding();
	
	UBuildingInfo* GetBuildingInfo() const { return BuildingInfo; }

	void SetBuildingInfo(UBuildingInfo* NewBuildingInfo) { BuildingInfo = NewBuildingInfo; }

	UFUNCTION(BlueprintCallable)
	void RegisterChangeState(int32 NewResources);

	UFUNCTION(BlueprintNativeEvent)
	void Init();
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* RootScene = nullptr;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	UTextRenderComponent* TextRender;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta=(AllowPrivateAccess="true", ExposeOnSpawn="true"))
	UBuildingInfo* BuildingInfo = nullptr;
};
