#include "Tower.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	boxComponent->SetBoxExtent(FVector(40, 40, 100));
	SetRootComponent(boxComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/Asian_Village/meshes/building/SM_tower_02.SM_tower_02'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeScale3D(FVector(0.1));
		meshComponent->SetRelativeLocation(FVector(0, 0, -110));
		meshComponent->SetupAttachment(RootComponent);
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

