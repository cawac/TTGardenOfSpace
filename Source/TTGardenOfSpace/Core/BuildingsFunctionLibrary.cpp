#include "BuildingsFunctionLibrary.h"

#include "TTGardenOfSpace/Buildings/BuildingInfo.h"

UBuildingInfo* UBuildingsFunctionLibrary::CalculateClosestActor(const TArray<UBuildingInfo*>& Array, const UBuildingInfo& Origin)
{
	UBuildingInfo* TargetActor = nullptr;
	float ClosestDistance = 0;
	if (Array.Num() == 0)
	{
		return nullptr;
	}
	for (int i = 0; i < Array.Num(); i++)
	{
		UBuildingInfo* Actor = Array[i];
		const float Distance = (Origin.GetTransform().GetLocation() - Actor->GetTransform().GetLocation()).Size();
		if (i == 0 || Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			TargetActor = Actor;
		}
	}
	return TargetActor;
}
