#include "PooledStrongEnemy.h"
#include "PooledStrongEnemyBullet.h"
#include "StrongEnemyBulletPool.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAIController.h"


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

	ConstructorHelpers::FClassFinder<AEnemyAIController> bpAIControllerClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/EnemyAI/BP_EnemyAIController.BP_EnemyAIController_C'"));
	if (bpAIControllerClass.Succeeded())
	{
		EnemyAIControllerFactory = bpAIControllerClass.Class;
	}

	ConstructorHelpers::FClassFinder<UEnemyAnimInstance> bpEnemyAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Enemy/Doosey/Animation/ABP_DooseyAnim.ABP_DooseyAnim_C'"));
	if (bpEnemyAnim.Succeeded())
	{
		EnemyAnimFactory = bpEnemyAnim.Class;
		GetMesh()->SetAnimInstanceClass(EnemyAnimFactory);
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

	FActorSpawnParameters params;
	aiController = GetWorld()->SpawnActor<AEnemyAIController>(EnemyAIControllerFactory, params);
	if (aiController)
	{
		aiController->Possess(this);
	}
}

void APooledStrongEnemy::Attack(AActor* target)
{
	Super::Attack(target);

	FVector spawnPosition = GetActorLocation() + GetActorForwardVector();
	FRotator spawnRotator = (target->GetActorLocation() - GetActorLocation()).Rotation();

	APooledStrongEnemyBullet* strongEnemyBullet = Cast<APooledStrongEnemyBullet>(
		strongEnemyBulletPool->SpawnPooledObject(spawnPosition, spawnRotator));

	if (IsValid(strongEnemyBullet))
	{
		strongEnemyBullet->SetDeactiveTimer(1.5f);
	}
}

void APooledStrongEnemy::Reset()
{
	SetEnemyState(HP);
}