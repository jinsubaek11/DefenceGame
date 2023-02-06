#include "EnemyAnimInstance.h"
#include "PooledEnemy.h"


UEnemyAnimInstance::UEnemyAnimInstance()
{

}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	APooledEnemy* enemy = Cast<APooledEnemy>(TryGetPawnOwner());

	if (IsValid(enemy))
	{
		animationState = enemy->GetAnimationState();
		//UE_LOG(LogTemp, Warning, TEXT("%d"), enemy->GetAnimationState());
	}
}

void UEnemyAnimInstance::AnimNotify_DeathEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("DeathEnd"));
	OnDeath.Broadcast();
}

void UEnemyAnimInstance::AnimNotify_dAttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("dAttackEnd"));

}