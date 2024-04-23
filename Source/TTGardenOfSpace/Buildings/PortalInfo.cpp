#include "PortalInfo.h"


void UPortalInfo::SetClosestBuilding(UBuildingInfo* NewClosestBuilding)
{
	if (NewClosestBuilding->GetClass() == UPortalInfo::StaticClass())
	{
		NewClosestBuilding = nullptr;
	}
	SetClosestBuildingWithBroadcast(NewClosestBuilding);
}


