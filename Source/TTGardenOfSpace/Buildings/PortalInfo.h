#pragma once

#include "CoreMinimal.h"
#include "TransmitterInfo.h"
#include "PortalInfo.generated.h"

UCLASS()
class UPortalInfo : public UTransmitterInfo
{
	GENERATED_BODY()

public:
	UPortalInfo() { Resources = 0; MinResources = 0; MaxResources = 100; }
	
	virtual void SetClosestBuilding(UBuildingInfo* NewClosestBuilding) override;
};