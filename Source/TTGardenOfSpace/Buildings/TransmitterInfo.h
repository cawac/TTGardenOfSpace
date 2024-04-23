#pragma once

#include "CoreMinimal.h"
#include "BuildingInfo.h"
#include "TransmitterInfo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeClosestBuilding, UBuildingInfo*, NewClosestBuildingInfo);

UCLASS()
class UTransmitterInfo : public UBuildingInfo
{
	GENERATED_BODY()
	
public:
	UTransmitterInfo();

	virtual void Update() override;

	virtual void SetClosestBuilding(UBuildingInfo* NewClosestBuilding);

	virtual void SetClosestBuildingWithBroadcast(UBuildingInfo* NewClosestBuilding);

	UPROPERTY(BlueprintAssignable)
	FOnChangeClosestBuilding OnChangeClosestBuilding;
protected:
	virtual void Absorb();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBuildingInfo* ClosestBuilding = nullptr;
	
	int32 AbsorptionSpeed = 1;
};
