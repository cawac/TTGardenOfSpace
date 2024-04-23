// Copyright Eriars Studio

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BuildingsFunctionLibrary.generated.h"

class UBuildingInfo;

UCLASS()
class UBuildingsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UBuildingInfo* UBuildingsFunctionLibrary::CalculateClosestActor(const TArray<UBuildingInfo*>& Array, const UBuildingInfo& Origin);

};
