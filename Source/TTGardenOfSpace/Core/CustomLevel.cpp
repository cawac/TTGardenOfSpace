#include "CustomLevel.h"

#include "TTGardenOfSpace/Buildings/BuildingInfo.h"

void UCustomLevel::Update()
{
	for (auto& Building: Buildings)
	{
		Building->Update();
	}
}

