#include "ItemObstacle.h"


AItemObstacle::AItemObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	boxComponent->SetBoxExtent(FVector(180, 20, 100));
	boxComponent->SetRelativeRotation(FRotator(0, -90, 0));
	boxComponent->SetCollisionProfileName(TEXT("ObstaclePreset"));
	SetRootComponent(boxComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/Asian_Village/meshes/props/SM_box_02.SM_box_02'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetupAttachment(RootComponent);
		meshComponent->SetRelativeLocation(FVector(0, 0, -100));
		meshComponent->SetRelativeScale3D(FVector(2, 0.3, 3));
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("/Script/Engine.Material'/Game/Material/M_ObstacleGreen.M_ObstacleGreen'"));
	if (mat.Succeeded())
	{
		originalMaterial = meshComponent->GetMaterials();
		transparentMaterial = mat.Object;
	}
}

void AItemObstacle::BeginPlay()
{
	Super::BeginPlay();

	dynamicMaterial = UMaterialInstanceDynamic::Create(transparentMaterial, this);
	for (int i = 0; i < meshComponent->GetMaterials().Num(); i++)
	{
		meshComponent->SetMaterial(i, dynamicMaterial);
	}
}

void AItemObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemObstacle::OnBeginOverlapItem(AActor* OtherActor)
{
	AItem* otherItem = Cast<AItem>(OtherActor);

	if (otherItem && !isSetSucceed)
	{
		SetMaterialColor(FVector(1.5, 0.4, 0.4));
		isCollision = true;
	}
}

void AItemObstacle::OnEndOverlapItem(AActor* OtherActor)
{
	AItem* otherItem = Cast<AItem>(OtherActor);

	if (otherItem && !isSetSucceed)
	{
		SetMaterialColor(FVector(0.4, 1.5, 0.4));
		isCollision = false;
	}
}


