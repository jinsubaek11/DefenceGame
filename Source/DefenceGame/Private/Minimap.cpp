#include "Minimap.h"
#include "Components/SceneCaptureComponent2D.h"


AMinimap::AMinimap()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(sceneComponent);

	sceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture Component"));
	sceneCaptureComponent->SetRelativeRotation(FRotator(-90, 0, 0));
	sceneCaptureComponent->SetupAttachment(RootComponent);
}

void AMinimap::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMinimap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

