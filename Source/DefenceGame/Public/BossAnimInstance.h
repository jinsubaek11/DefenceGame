#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackStart);

UENUM(BlueprintType)
enum class EBossAnimationState : uint8
{
	IDLE,
	WALKING,
	FLYING,
	JUMP_ATTACK,
	DEATH,
	SHEATHING_SWORD,
	WITHDRAWING_SWORD,
	SWORD_INWARD_SLASH,
	SWORD_OUTWARD_SLASH,
	SWORD_COMBO,
	SHOOTING_ARROW
};

UCLASS()
class DEFENCEGAME_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void AnimNotify_AttackStart();
	UFUNCTION()
	void AnimNotify_AttackEnd();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBossAnimationState animationState;
	
	FOnAttackStart OnAttackStart;

private:
	class APooledBossEnemy* boss;
};
