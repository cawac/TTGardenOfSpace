#include "TransmitterInfo.h"

UTransmitterInfo::UTransmitterInfo()
{
	Resources = 0;
	MinResources = 0;
	MaxResources = 100;
}

void UTransmitterInfo::Update()
{
	Super::Update();
	Absorb();
}

void UTransmitterInfo::SetClosestBuilding(UBuildingInfo* NewClosestBuilding)
{
	ClosestBuilding = NewClosestBuilding;
}

void UTransmitterInfo::SetClosestBuildingWithBroadcast(UBuildingInfo* NewClosestBuilding)
{
	ClosestBuilding = NewClosestBuilding;
	OnChangeClosestBuilding.Broadcast(ClosestBuilding);
}

void UTransmitterInfo::Absorb()
{
	if (ClosestBuilding == nullptr)
	{
		return;
	}
	const int32 LimitOfAbsorbedResources =
		std::min(std::min(MaxResources - Resources,ClosestBuilding->GetResources() - ClosestBuilding->GetMinResources()),
											  AbsorptionSpeed);
	if (LimitOfAbsorbedResources == 0)
	{
		SetClosestBuildingWithBroadcast(nullptr);
		return;
	}
	SetResourcesWithBroadcast(Resources + LimitOfAbsorbedResources);
	ClosestBuilding->SetResourcesWithBroadcast(ClosestBuilding->GetResources() - LimitOfAbsorbedResources);
}
