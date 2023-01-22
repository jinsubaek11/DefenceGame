#include "Bazooka.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GamePlayer.h"
#include <Camera/CameraComponent.h>
#include "Engine/SkeletalMeshSocket.h"
#include "Particles/ParticleSystem.h"
#include "PlayerRifleBulletPool.h"
#include "PooledPlayerRifleBullet.h"


ABazooka::ABazooka()
{
	PrimaryActorTick.bCanEverTick = true;

	weaponType = WeaponType::BAZOOKA;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skeletal Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/Weapons/Bazooka/Bazooka.Bazooka'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetupAttachment(RootComponent);
		meshComponent->SetRelativeLocation(FVector(20, -10, -10));
		meshComponent->SetRelativeScale3D(FVector(0.1));
	}

	decalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Component"));
	ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (mat.Succeeded())
	{
		decalComponent->SetDecalMaterial(mat.Object);
		decalComponent->SetVisibility(false);
	}

	emitParticle = CreateDefaultSubobject<UParticleSystem>(TEXT("Emit Particle"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(TEXT("/Script/Engine.ParticleSystem'/Game/FX/Particles/Abilities/Primary/FX/P_Wraith_Primary_MuzzleFlash.P_Wraith_Primary_MuzzleFlash'"));
	if (particle.Succeeded())
	{
		emitParticle = particle.Object;
	}

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void ABazooka::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	rifleBulletPool = GetWorld()->SpawnActor<APlayerRifleBulletPool>();
}

void ABazooka::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawBazookaRange();
}

void ABazooka::DrawBazookaRange()
{
	if (!player) return;

}

void ABazooka::Shoot()
{
	if (!player) return;


}