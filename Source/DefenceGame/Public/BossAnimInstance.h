#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathBoss);

UENUM(BlueprintType)
enum class EBossAnimationState : uint8
{
	IDLE,
	WALKING,
	DEATH,
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
	UFUNCTION()
	void AnimNotify_DeathEnd();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBossAnimationState animationState;
	
	FOnAttackStart OnAttackStart;
	FOnDeathBoss OnDeath;

private:
	class APooledBossEnemy* boss;
};
