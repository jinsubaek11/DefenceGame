#include "PooledEnemy.h"
#include "GamePlayer.h"
#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BrainComponent.h"
#include "EnemyAnimInstance.h"


APooledEnemy::APooledEnemy()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyPreset"));
	planeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> iconMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (iconMesh.Succeeded())
	{
		planeComponent->SetStaticMesh(iconMesh.Object);
		planeComponent->SetRelativeLocationAndRotation(FVector(0, 0, 3000), FRotator(0, -90, 0));
		planeComponent->SetRelativeScale3D(FVector(3, 3, 2));
		planeComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//planeComponent->bOnlyOwnerSee = true;
	}
	ConstructorHelpers::FObjectFinder<UMaterialInterface> iconMat(TEXT("/Script/Engine.Material'/Game/UI/Image/M_Enemy_Icon.M_Enemy_Icon'"));
	if (iconMat.Succeeded())
	{
		planeComponent->SetMaterial(0, iconMat.Object);
		planeComponent->CastShadow = false;
	}
	planeComponent->SetupAttachment(RootComponent);
}

void APooledEnemy::BeginPlay()
{
	Super::BeginPlay();

	UEnemyAnimInstance* enemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (enemyAnimInstance)
	{
		enemyAnimInstance->OnDeath.AddDynamic(this, &APooledEnemy::OnDeath);
	}
}

void APooledEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APooledEnemy::Attack(AActor* target)
{
	SetAnimationState(EEnemyAnimationState::ATTACK);
}

void APooledEnemy::OnTakeDamage(int32 damage)
{
	hp -= damage;

	if (hp < 0)
	{

		//Reset();
		//SetActive(false);
		if (aiController)
		{
			aiController->BrainComponent->StopLogic(TEXT("Dead"));
		}
		SetAnimationState(EEnemyAnimationState::DEAD);
		
	}
}

void APooledEnemy::SetAnimationState(EEnemyAnimationState animState)
{
	animationState = animState;
}

EEnemyAnimationState APooledEnemy::GetAnimationState()
{
	return animationState;
}

void APooledEnemy::Reset()
{

}

void APooledEnemy::SetEnemyState(float health)
{
	hp = health;
}

void APooledEnemy::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDeath"));
	SetActive(false);
}