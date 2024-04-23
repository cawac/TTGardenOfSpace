#pragma once

#include "CoreMinimal.h"
#include "BuildingInfo.h"
#include "SpringInfo.generated.h"

UCLASS()
class USpringInfo : public UBuildingInfo
{
	GENERATED_BODY()

public:
	USpringInfo() { Resources = 100; MinResources = 0; MaxResources = 100; }
	
	virtual void Update() override;
};