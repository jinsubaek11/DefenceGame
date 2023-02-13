#include "Bow.h"
#include "BossEnemyBulletPool.h"
#include "PooledBossEnemyBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GamePlayer.h"
#include "PooledBossEnemy.h"


ABow::ABow()
{
	PrimaryActorTick.bCanEverTick = false;
	weaponType = WeaponType::BOW;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	boxComponent->SetBoxExtent(FVector(8, 20, 98));
	SetRootComponent(boxComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> bowMesh(TEXT("/Script/Engine.StaticMesh'/Game/Weapons/Bow/Mesh/Bow.Bow'"));
	if (bowMesh.Succeeded())
	{
		meshComponent->SetStaticMesh(bowMesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, -10, -110), FRotator(0, 90, 0));
	}
	meshComponent->SetupAttachment(RootComponent);
}

void ABow::BeginPlay()
{
	Super::BeginPlay();

	boss = Cast<APooledBossEnemy>(UGameplayStatics::GetActorOfClass(GetWorld(), APooledBossEnemy::StaticClass()));
	bossEnemyBulletPool = GetWorld()->SpawnActor<ABossEnemyBulletPool>();
}

void ABow::Shoot()
{
	if (!boss) return;

	int8 randIndex = FMath::RandRange(0, 1);
	//randIndex = 0;

	switch ((EBowAttackType)randIndex)
	{
	case EBowAttackType::SINGLE_SHOOT:
		SingleShoot();
		break;
	case EBowAttackType::TRIPLE_SHOOT:
		TripleShoot();
		break;
	}
}

void ABow::SingleShoot()
{
	APooledBossEnemyBullet* arrow = Cast<APooledBossEnemyBullet>(
		bossEnemyBulletPool->SpawnPooledObject(GetActorLocation() + FVector(0, 0, 80), boss->GetTargetRotation())
	);
	
	arrow->SetDestroyRange(GetActorLocation());
	arrow->DrawExplosionRange();
}

void ABow::TripleShoot()
{
	for (int i = 0; i < 3; i++)
	{
		APooledBossEnemyBullet* arrow = Cast<APooledBossEnemyBullet>(
			bossEnemyBulletPool->SpawnPooledObject(GetActorLocation() + FVector(0, 0, 80), boss->GetTargetRotation() + FRotator(0, 10, 0) + FRotator(0, - i * 10, 0)));
		arrow->SetDestroyRange(GetActorLocation());
		arrow->DrawExplosionRange();
	}
}