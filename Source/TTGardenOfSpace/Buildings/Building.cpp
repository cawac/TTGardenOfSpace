#include "Building.h"
#include "Components/TextRenderComponent.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Create and RootScene
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(RootScene);

	// Create and TextRender
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	TextRender->SetupAttachment(RootComponent);
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void ABuilding::RegisterChangeState(const int32 NewResources)
{
	TextRender->SetText(FText::AsNumber(NewResources));
}

void ABuilding::Init_Implementation()
{
	if (BuildingInfo == nullptr)
	{
		return;
	}
	BuildingInfo->OnChangeState.AddDynamic(this,  &ABuilding::RegisterChangeState);
	BuildingInfo->OnChangeState.Broadcast(BuildingInfo->GetResources());
	
}
