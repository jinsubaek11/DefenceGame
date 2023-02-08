#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerUIAnim.generated.h"

UENUM(BlueprintType)
enum class EPlayerUIAnimationState : uint8
{
	IDLE,
	HIT,
	DEAD
};

UCLASS()
class DEFENCEGAME_API UPlayerUIAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerUIAnim();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	void PlayHitAnimation(FName section);

private:
	UFUNCTION()
	void AnimNotify_HitEnd();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerUIAnimationState animationState;

private:
	UPROPERTY()
	class AGamePlayerUI* playerUI;
	UPROPERTY()
	class UAnimMontage* hitMontage;
};
