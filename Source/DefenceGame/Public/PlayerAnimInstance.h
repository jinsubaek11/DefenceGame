#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EPlayerAnimationState : uint8
{
	MOVE,
	JUMP,
	SHOOT_RIFLE,
	SHOOT_BAZOOKA,
	SHOOT_GRENADE,
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
	UFUNCTION()
	void AnimNotify_ShootRifleStart();
	UFUNCTION()
	void AnimNotify_ShootRifleEnd();
	UFUNCTION()
	void AnimNotify_ShootBazookaEnd();
	UFUNCTION()
	void AnimNotify_ShootGrenadeEnd();

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
