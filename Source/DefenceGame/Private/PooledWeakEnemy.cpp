#include "PooledWeakEnemy.h"
#include "WeakEnemyBulletPool.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "EnemyAIController.h"
#include "FatalTeeth.h"


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
		meshComponent->SetRelativeScale3D(FVector(1));
	}

	teethBox = CreateDefaultSubobject<UBoxComponent>(TEXT("teethBox"));
	teethBox->SetupAttachment(GetMesh(), TEXT("TeethSocket"));
	teethBox->SetRelativeLocation(FVector(0, 52, 156));
	

	ConstructorHelpers::FClassFinder<AEnemyAIController> bpAIControllerClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/EnemyAI/BP_EnemyAIController.BP_EnemyAIController_C'"));
	if (bpAIControllerClass.Succeeded())
	{
		EnemyAIControllerFactory = bpAIControllerClass.Class;
	}

	ConstructorHelpers::FClassFinder<UEnemyAnimInstance> bpEnemyAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Enemy/Zombie/Animation/ABP_ZombieAnim.ABP_ZombieAnim_C'"));
	if (bpEnemyAnim.Succeeded())
	{
		EnemyAnimFactory = bpEnemyAnim.Class;
		GetMesh()->SetAnimInstanceClass(EnemyAnimFactory);
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

	FActorSpawnParameters params;
	aiController = GetWorld()->SpawnActor<AEnemyAIController>(EnemyAIControllerFactory, params);
	if (aiController)
	{
		aiController->Possess(this);
	}

	teeth = GetWorld()->SpawnActor<AFatalTeeth>();
	teeth->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("TeethSocket"));

}

void APooledWeakEnemy::Attack(AActor* target)
{
	Super::Attack(target);

	//목을 무는 것이 공격
	teeth->Shoot();

}

void APooledWeakEnemy::Reset()
{
	SetEnemyState(HP);
}