#include "EnemyAnimInstance.h"
#include "PooledEnemy.h"
#include "Animation/AnimMontage.h"


UEnemyAnimInstance::UEnemyAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> shootMontageAsset(TEXT("/Script/Engine.AnimMontage'/Game/Enemy/Mousey/Animation/Attack_Montage.Attack_Montage'"));
	if (shootMontageAsset.Succeeded())
	{
		shootMontage = shootMontageAsset.Object;
	}
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

void UEnemyAnimInstance::PlayShootMontage()
{
	Montage_Play(shootMontage, 1.f);
}