#include "PlayerUIAnim.h"
#include "GamePlayerUI.h"
#include "Animation/AnimMontage.h"


UPlayerUIAnim::UPlayerUIAnim()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> hitMontageAsset(TEXT("/Script/Engine.AnimMontage'/Game/Player/Animation/PlayerHitMontage.PlayerHitMontage'"));
	if (hitMontageAsset.Succeeded())
	{
		hitMontage = hitMontageAsset.Object;
	}
}

void UPlayerUIAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerUIAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	playerUI = Cast<AGamePlayerUI>(GetOwningActor());
}

void UPlayerUIAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!playerUI) return;

	animationState = playerUI->GetAnimationState();
}

void UPlayerUIAnim::PlayHitAnimation(FName section)
{
	float duration = Montage_Play(hitMontage, 1.f);
	if (duration > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *section.ToString());
		Montage_JumpToSection(section, hitMontage);
	}
}

void UPlayerUIAnim::AnimNotify_HitEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("AnimNotify_HitEnd"));
	playerUI->SetAnimationState(EPlayerUIAnimationState::IDLE);
}
