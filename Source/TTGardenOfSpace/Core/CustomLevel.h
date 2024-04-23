 #pragma once

#include "CoreMinimal.h"
#include "CustomLevel.generated.h"

class UBuildingInfo;

UCLASS(Blueprintable)
class UCustomLevel : public UObject
{
	GENERATED_BODY()

public:
	UCustomLevel() {}
	
	void Update();
	
	TArray<UBuildingInfo*>& GetBuildings() { return Buildings; }

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<UBuildingInfo*> Buildings;
};