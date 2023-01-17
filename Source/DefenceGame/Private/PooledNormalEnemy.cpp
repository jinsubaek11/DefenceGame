#include "PooledNormalEnemy.h"
#include "Components/CapsuleComponent.h"
#include "normalEnemyBulletPool.h"
#include "PooledNormalEnemyBullet.h"


APooledNormalEnemy::APooledNormalEnemy()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(140);
	GetCapsuleComponent()->SetCapsuleRadius(60);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Mousey/Skeleton/mousey.mousey'"));
	if (mesh.Succeeded())
	{
		USkeletalMeshComponent* meshComponent = GetMesh();
		meshComponent->SetSkeletalMesh(mesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));
		meshComponent->SetRelativeScale3D(FVector(2));
	}

	SetEnemyState(HP);
}

void APooledNormalEnemy::BeginPlay()
{
	Super::BeginPlay();

	normalEnemyBulletPool = GetWorld()->SpawnActor<ANormalEnemyBulletPool>();
}

void APooledNormalEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APooledNormalEnemy::Attack(AActor* target)
{
	Super::Attack(target);

	FVector spawnPosition = GetActorLocation() + GetActorForwardVector();
	FRotator spawnRotator = GetActorRotation();

	APooledNormalEnemyBullet* normalEnemyBullet = Cast<APooledNormalEnemyBullet>(
		normalEnemyBulletPool->SpawnPooledObject(spawnPosition, spawnRotator));

	if (IsValid(normalEnemyBullet))
	{
		normalEnemyBullet->SetDeactiveTimer(4.f);
	}
}

void APooledNormalEnemy::Reset()
{
	SetEnemyState(HP);
}