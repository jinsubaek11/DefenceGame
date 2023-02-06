#include "BossAnimInstance.h"
#include "PooledBossEnemy.h"


void UBossAnimInstance::NativeInitializeAnimation()
{

}

void UBossAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	boss = Cast<APooledBossEnemy>(GetOwningActor());
	if (!boss) return;

	animationState = boss->GetAnimationState();
}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!boss) return;
	
	animationState = boss->GetAnimationState();
}

void UBossAnimInstance::AnimNotify_AttackStart()
{
	if (!boss) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Boss Attack Start"));

	OnAttackStart.Broadcast();
}

void UBossAnimInstance::AnimNotify_AttackEnd()
{
	if (!boss) return;

	UE_LOG(LogTemp, Warning, TEXT("Boss Attack End"));
	
	boss->SetIsPlayingAnimation(false);
}
