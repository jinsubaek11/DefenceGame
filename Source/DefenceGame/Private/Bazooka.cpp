#include "Bazooka.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GamePlayer.h"
#include <Camera/CameraComponent.h>
#include "Engine/SkeletalMeshSocket.h"
#include "Particles/ParticleSystem.h"
#include "PlayerBazookaBulletPool.h"
#include "PooledPlayerBazookaBullet.h"


ABazooka::ABazooka()
{
	PrimaryActorTick.bCanEverTick = true;

	weaponType = WeaponType::BAZOOKA;
	maxBulletCounts = 5;
	bulletCounts = maxBulletCounts;
	attackRange = 2000.f;
	att = 30;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/Weapons/Bazooka/Mesh/Bazooka.Bazooka'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetupAttachment(RootComponent);
		meshComponent->SetRelativeLocation(FVector(20, -5, -10));
		meshComponent->SetRelativeScale3D(FVector(0.1, 0.07, 0.1));
	}

	decalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Component"));
	ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("/Script/Engine.Material'/Game/Weapons/Generic/Materials/M_DistanceChecking.M_DistanceChecking'"));
	if (mat.Succeeded())
	{
		originalMaterial = mat.Object;
		decalComponent->SetVisibility(false);
	}

	SetActive(false);
	SetActorRotation(FRotator(90, 0, 180));
}

void ABazooka::BeginPlay()
{
	Super::BeginPlay();

	bazookaBulletPool = GetWorld()->SpawnActor<APlayerBazookaBulletPool>();

	dynamicMaterial = UMaterialInstanceDynamic::Create(originalMaterial, this);
	decalComponent->SetMaterial(0, dynamicMaterial);

	decalRotation = player->GetActorRotation().Add(0, 3, 0);
}

void ABazooka::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	decalRotation = player->GetActorRotation().Add(0, 3, 0);
	DrawWeaponRange();
}

void ABazooka::DrawWeaponRange()
{
	Super::DrawWeaponRange();

}

void ABazooka::Shoot()
{
	Super::Shoot();

	if (bulletCounts < 0)
	{
		// no bullet sound;
		return;
	}

	FVector start;
	FRotator rotation;
	player->GetController()->GetPlayerViewPoint(start, rotation);
	FVector end = start + rotation.Vector() * attackRange;

	FVector spawnPosition = player->GetActorLocation() - player->GetActorRightVector() * 50;
	FRotator spawnRotation = (end - spawnPosition).Rotation();

	APooledPlayerBazookaBullet* bullet = Cast<APooledPlayerBazookaBullet>(
		bazookaBulletPool->SpawnPooledObject(spawnPosition, spawnRotation)
	);

	bullet->SetDestroyRange(spawnPosition, autoDestroyRange);
}


