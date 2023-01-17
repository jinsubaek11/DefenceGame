#include "PooledEnemy.h"
#include "GamePlayer.h"
#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"


APooledEnemy::APooledEnemy()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyPreset"));
}

void APooledEnemy::BeginPlay()
{
	Super::BeginPlay();

	//ATestTwoAIController* ai = Cast<ATestTwoAIController>(GetController());
	//ai->Possess(this);
}

void APooledEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SetActorLocation(GetActorLocation() + GetActorForwardVector() * 300 * DeltaTime);
}

void APooledEnemy::Attack(AActor* target)
{
	//SetAnimationState(EEnemyAnimationState::ATTACK);

	//AGamePlayer* player = Cast<AGamePlayer>(target);
	// 아이템 추가
	// 금고 추가

	//if (IsValid(player))
	//{
		//player->OnTakeDamage(att);
		//SetAnimationState(EEnemyAnimationState::ATTACK);
	//}
}

void APooledEnemy::OnTakeDamage(float damage)
{
	hp -= damage;

	if (hp < 0)
	{

		//Reset();
		//SetActive(false);
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
