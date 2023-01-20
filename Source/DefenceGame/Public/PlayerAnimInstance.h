#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EPlayerAnimationState : uint8
{
	MOVE,
	JUMP,
	ATTACK,
	DEAD
};

UCLASS()
class DEFENCEGAME_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:	
	UFUNCTION()
	void AnimNotify_JumpEnd();	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerAnimationState animationState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isMovingOnGround;

private:
	class AGamePlayer* player;
};
