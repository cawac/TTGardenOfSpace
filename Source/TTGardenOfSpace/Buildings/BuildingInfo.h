#pragma once

#include "CoreMinimal.h"
#include "BuildingInfo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeResources, const int32, NewResources);

class UCustomLevel;

UCLASS(Blueprintable)
class UBuildingInfo : public UObject
{
	GENERATED_BODY()

public:
	UBuildingInfo() {}
	
	int32 GetResources() const { return Resources; }

	UFUNCTION(BlueprintCallable)
	void SetResourcesWithBroadcast(const int32 NewResources)
	{
		Resources = NewResources;
		OnChangeState.Broadcast(NewResources);
	}

	void SetResources(const int32 NewResources) { Resources = NewResources; }

	int32 GetMinResources() const { return MinResources; }

	void SetMinResources(const int32 NewMinResources) { MinResources = NewMinResources; }
	
	int32 GetMaxResources() const { return MaxResources; }

	void SetMaxResources(const int32 NewMaxResources) { MaxResources = NewMaxResources; }

	FTransform GetTransform() const { return BuildingTransform; }

	void SetTransform(const FTransform& NewTransform) { BuildingTransform = NewTransform; }

	UClass* GetBlueprintClass() const { return BlueprintClass; }

	void SetBlueprintClass(UClass* Class) { BlueprintClass = Class; }
	
	virtual void Update() {}

	UPROPERTY(Category="Buildings", BlueprintReadOnly)
	FOnChangeResources OnChangeState;
	
protected:
	UPROPERTY(Category="Buildings", BlueprintReadWrite)
	UClass* BlueprintClass = nullptr;
	
	UPROPERTY(Category="Buildings", BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	FTransform BuildingTransform;

	UPROPERTY(Category="Buildings", BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	int32 Resources = 0;
	
	int32 MinResources = 0;

	int32 MaxResources = 0;
};