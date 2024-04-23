#include "LevelManager.h"

#include "BuildingsFunctionLibrary.h"
#include "CustomLevel.h"
#include "TTGardenOfSpace/Buildings/Building.h"
#include "TTGardenOfSpace/Buildings/SpringInfo.h"
#include "TTGardenOfSpace/Buildings/TransmitterInfo.h"
#include "TTGardenOfSpace/Buildings/PortalInfo.h"


ULevelManager::ULevelManager()
{
	Levels.Add(0, NewObject<UCustomLevel>());
}

void ULevelManager::Tick(float DeltaTime)
{
	TimeSinceLastTick += DeltaTime;
	while (TimeSinceLastTick >= 1.f)
	{
		TimeSinceLastTick -= 1;
		for (auto &KeyValue : Levels)
		{
			KeyValue.Value->Update();
		}
	}
}

bool ULevelManager::IsTickable() const
{
	return FTickableGameObject::IsTickable();
}

TStatId ULevelManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(ULevelManager, STATGROUP_Tickables);
}

UCustomLevel* ULevelManager::GetLevel(int32 NumberOfLevel)
{
	if (Levels.Num() == 0)
	{
		return nullptr;
	}
	if (!Levels.Contains(NumberOfLevel))
	{
		UCustomLevel* Level = NewObject<UCustomLevel>();
		Levels.Emplace(NumberOfLevel, Level);
	}
	return *Levels.Find(NumberOfLevel);
}


UCustomLevel* ULevelManager::PrevLevel()
{
	CurrentNumberOfLevel -= 1;
	return GetLevel(CurrentNumberOfLevel);
}

UCustomLevel* ULevelManager::NextLevel()
{
	CurrentNumberOfLevel += 1;
	return GetLevel(CurrentNumberOfLevel);
}

UCustomLevel* ULevelManager::GetCurrentLevel()
{
	return GetLevel(CurrentNumberOfLevel);
}

void ULevelManager::BroadcastPortalResources(const int32 NewPortalResources)
{
	if (PortalResources == NewPortalResources)
	{
		return;
	}
	PortalResources = NewPortalResources;
	OnChangePortalsResources.Broadcast(NewPortalResources);
}

void ULevelManager::LoadLevel(UCustomLevel* Level)
{
	for (UBuildingInfo* BuildingInfo : Level->GetBuildings())
	{
		if (BuildingInfo == nullptr)
		{
			continue;
		}
		ABuilding* Building = GetWorld()->SpawnActor<ABuilding>(BuildingInfo->GetBlueprintClass(), BuildingInfo->GetTransform());
		Building->SetBuildingInfo(BuildingInfo);
		Building->Init();
	}
}

UBuildingInfo* ULevelManager::AddBuilding(TSubclassOf<UBuildingInfo> BuildingClass, FTransform BuildingTransform)
{
	UBuildingInfo* Building = nullptr;
	if (BuildingClass == USpringInfo::StaticClass())
	{
		USpringInfo* Spring = NewObject<USpringInfo>();
		Spring->SetTransform(BuildingTransform);
		Building = Spring;
	}
	else if (BuildingClass == UTransmitterInfo::StaticClass())
	{
		UTransmitterInfo* Transmitter = NewObject<UTransmitterInfo>();
		Transmitter->SetTransform(BuildingTransform);
		UBuildingInfo* ClosestBuilding = UBuildingsFunctionLibrary::CalculateClosestActor(GetCurrentLevel()->GetBuildings(), *Transmitter);
		Transmitter->SetClosestBuilding(ClosestBuilding);
		Building = Transmitter;
	}
	else if (BuildingClass == UPortalInfo::StaticClass())
	{
		UPortalInfo* Portal = NewObject<UPortalInfo>();
		Portal->SetTransform(BuildingTransform);
		UBuildingInfo* ClosestBuilding = UBuildingsFunctionLibrary::CalculateClosestActor(GetCurrentLevel()->GetBuildings(), *Portal);
		Portal->SetClosestBuilding(ClosestBuilding);
		Portal->SetResources(PortalResources);
		Portal->OnChangeState.AddDynamic(this, &ULevelManager::BroadcastPortalResources);
		OnChangePortalsResources.AddDynamic(Portal, &UPortalInfo::SetResourcesWithBroadcast);
		Building = Portal;
	}
	if (!Building)
	{
		return nullptr;		
	}
	if (UCustomLevel* CurrentLevel = GetCurrentLevel())
	{
		TArray<UBuildingInfo*>& BuildingInfos = CurrentLevel->GetBuildings();
		BuildingInfos.Add(Building);
	}
	return Building;
}
