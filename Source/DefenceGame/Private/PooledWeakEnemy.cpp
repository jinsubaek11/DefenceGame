#include "PooledWeakEnemy.h"
#include "WeakEnemyBulletPool.h"
#include "PooledWeakEnemyBullet.h"
#include "Components/CapsuleComponent.h"


APooledWeakEnemy::APooledWeakEnemy()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(120);
	GetCapsuleComponent()->SetCapsuleRadius(40);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Zombie/Skeleton/zombie.zombie'"));
	if (mesh.Succeeded())
	{
		USkeletalMeshComponent* meshComponent = GetMesh();
		meshComponent->SetSkeletalMesh(mesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, 0, -70), FRotator(0, -90, 0));
		meshComponent->SetRelativeScale3D(FVector(1.5));
	}

	SetEnemyState(HP);
}

void APooledWeakEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APooledWeakEnemy::BeginPlay()
{
	Super::BeginPlay();

	weakEnemyBulletPool = GetWorld()->SpawnActor<AWeakEnemyBulletPool>();
}

void APooledWeakEnemy::Attack(AActor* target)
{
	Super::Attack(target);

	FVector spawnPosition = GetActorLocation() + GetActorForwardVector();
	FRotator spawnRotator = GetActorRotation();

	APooledWeakEnemyBullet* weakEnemyBullet = Cast<APooledWeakEnemyBullet>(
		weakEnemyBulletPool->SpawnPooledObject(spawnPosition, spawnRotator));

	if (IsValid(weakEnemyBullet))
	{
		weakEnemyBullet->SetDeactiveTimer(4.f);
	}
}

void APooledWeakEnemy::Reset()
{
	SetEnemyState(HP);
}