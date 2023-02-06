#include "PooledStrongEnemy.h"
#include "StrongEnemyBulletPool.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAIController.h"
#include "EnemyAxe.h"
#include "characterHPWidget.h"
#include "PooledStrongEnemyBullet.h"
#include "Components/BoxComponent.h"

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


	FActorSpawnParameters params;
	aiController = GetWorld()->SpawnActor<AEnemyAIController>(EnemyAIControllerFactory, params);
	if (aiController)
	{
		aiController->Possess(this);
	}

	axe = GetWorld()->SpawnActor<AEnemyAxe>();
	axe->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandaxeSocket"));

	if(!shpWidget) return;
	shpWidget->ShowHPBar(HP);
}

void APooledStrongEnemy::Attack(AActor* target)
{
	Super::Attack(target);
	//axe가 player/tower에 닿으면 체력이 감소함
	axe->Shoot();

}

void APooledStrongEnemy::Reset()
{
	SetEnemyState(HP);
}

void APooledStrongEnemy::OnTakeSEnemyDamage(float attack)
{
	if (!shpWidget) return;

	HP -= attack;
	UE_LOG(LogTemp, Warning, TEXT("APooledStrongEnemy_____________Damage %f"), HP)

	shpWidget->SetcharacterHP(HP);
}
