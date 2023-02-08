#include "PooledNormalEnemy.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAIController.h"
#include "EnemyToyGun.h"
#include "EnemyAnimInstance.h"


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

	ConstructorHelpers::FClassFinder<AEnemyAIController> bpAIControllerClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/EnemyAI/BP_NormalEnemyAIController.BP_NormalEnemyAIController_C'"));
	if (bpAIControllerClass.Succeeded())
	{
		EnemyAIControllerFactory = bpAIControllerClass.Class;
	}

	ConstructorHelpers::FClassFinder<UEnemyAnimInstance> bpEnemyAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Enemy/Mousey/Animation/ABP_MouseyAnim.ABP_MouseyAnim_C'"));
	if (bpEnemyAnim.Succeeded())
	{
		EnemyAnimFactory = bpEnemyAnim.Class;
		GetMesh()->SetAnimInstanceClass(EnemyAnimFactory);
	}

	SetEnemyState(HP);
}

void APooledNormalEnemy::BeginPlay()
{
	Super::BeginPlay();

	gun = GetWorld()->SpawnActor<AEnemyToyGun>();
	gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandSocket"));

	FActorSpawnParameters params;
	aiController = GetWorld()->SpawnActor<AEnemyAIController>(EnemyAIControllerFactory, params);
	if (aiController)
	{
		aiController->Possess(this);
	}

	enemyAnim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

void APooledNormalEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APooledNormalEnemy::Attack(AActor* target)
{
	Super::Attack(target);

	gun->Shoot(target);
	enemyAnim->PlayShootMontage();
}

void APooledNormalEnemy::Reset()
{
	SetEnemyState(HP);
}