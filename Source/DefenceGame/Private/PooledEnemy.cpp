#include "PooledEnemy.h"
#include "GamePlayer.h"
#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BrainComponent.h"
#include "EnemyAnimInstance.h"


APooledEnemy::APooledEnemy()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyPreset"));
}

void APooledEnemy::BeginPlay()
{
	Super::BeginPlay();

	UEnemyAnimInstance* enemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (enemyAnimInstance)
	{
		enemyAnimInstance->OnDeath.AddDynamic(this, &APooledEnemy::OnDeath);
	}

	SetAnimationState((EEnemyAnimationState::WALK));
}

void APooledEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APooledEnemy::Attack(AActor* target)
{

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