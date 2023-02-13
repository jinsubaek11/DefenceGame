#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShoot);

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
	void AnimNotify_ShootStart();
	UFUNCTION()
	void AnimNotify_ShootEnd();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerAnimationState animationState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isMovingOnGround;

	FOnShoot OnShoot;

private:
	class AGamePlayer* player;
};
