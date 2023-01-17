#include "PooledStrongEnemy.h"
#include "PooledStrongEnemyBullet.h"
#include "StrongEnemyBulletPool.h"
#include "Components/CapsuleComponent.h"


APooledStrongEnemy::APooledStrongEnemy()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(140);
	GetCapsuleComponent()->SetCapsuleRadius(60);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Doosey/Skeleton/doosey.doosey'"));
	if (mesh.Succeeded())
	{
		USkeletalMeshComponent* meshComponent = GetMesh();
		meshComponent->SetSkeletalMesh(mesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));
		meshComponent->SetRelativeScale3D(FVector(2));
	}

	SetEnemyState(HP);
}

void APooledStrongEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APooledStrongEnemy::BeginPlay()
{
	Super::BeginPlay();

	strongEnemyBulletPool = GetWorld()->SpawnActor<AStrongEnemyBulletPool>();
}

void APooledStrongEnemy::Attack(AActor* target)
{
	Super::Attack(target);

	FVector spawnPosition = GetActorLocation() + GetActorForwardVector();
	FRotator spawnRotator = GetActorRotation();

	APooledStrongEnemyBullet* strongEnemyBullet = Cast<APooledStrongEnemyBullet>(
		strongEnemyBulletPool->SpawnPooledObject(spawnPosition, spawnRotator));

	if (IsValid(strongEnemyBullet))
	{
		strongEnemyBullet->SetDeactiveTimer(4.f);
	}
}

void APooledStrongEnemy::Reset()
{
	SetEnemyState(HP);
}