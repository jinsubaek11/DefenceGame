#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UENUM(BlueprintType)
enum class EEnemyAnimationState : uint8
{
	IDLE,
	WALK,
	ATTACK,
	DEAD
};

UCLASS()
class DEFENCEGAME_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UEnemyAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION()
	void AnimNotify_DeathEnd();

	UFUNCTION()
	void AnimNotify_dAttackEnd();

public:
	FOnDeath OnDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyAnimationState animationState;

	UPROPERTY()
	bool bdDeath;

};
