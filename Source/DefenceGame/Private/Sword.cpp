#include "Sword.h"
#include "Components/BoxComponent.h"

ASword::ASword()
{
	PrimaryActorTick.bCanEverTick = false;
	weaponType = WeaponType::SWORD;
	att = 30;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	boxComponent->SetBoxExtent(FVector(45, 5, 3));
	SetRootComponent(boxComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> swordMesh(TEXT("/Script/Engine.StaticMesh'/Game/Weapons/Sword/Mesh/Weapon1.Weapon1'"));
	if (swordMesh.Succeeded())
	{
		meshComponent->SetStaticMesh(swordMesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(196, -48, 2), FRotator(0, 90, 90));
		meshComponent->SetRelativeScale3D(FVector(2));
	}
	meshComponent->SetupAttachment(RootComponent);
}

void ASword::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASword::OnBeginOverlap);
}

void ASword::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Sword Attack"));
}