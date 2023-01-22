#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GamePlayer.generated.h"

DECLARE_DELEGATE_OneParam(FInputSwitchWeapon, int32);

UCLASS()
class DEFENCEGAME_API AGamePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AGamePlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void OnTakeDamage(float damage);
	void SetAttackAnimation(WeaponType weaponType);
	void SetAttackEnable(bool value);
	void SetAnimationState(EPlayerAnimationState state);
	EPlayerAnimationState GetAnimationState();
	class ARifle* GetRifle();

private:
	void OnAxisLookUp(float value);
	void OnAxisTurnRight(float value);
	void OnAxisMoveForward(float value);
	void OnAxisMoveRight(float value);
	void OnActionClick();
	void OnActionUseWeapon(int32 value);
	void OnActionUseItemMode();
	void OnActionJump();

	UFUNCTION()
	void OnActionSwitchWeapon(int32 weaponIndex);

public:
	UPROPERTY(EditAnywhere, Category=Camera)
	class USpringArmComponent* springArmComponent;
	UPROPERTY(EditAnywhere, Category = Camera)
	class UCameraComponent* cameraComponent;

private:
	TArray<class AItem*> obstacles;
	class AItem* newObstacle;
	FVector direction;
	float hp = 100.f;
	bool isItemMode;
	bool isAttackEnable;

	EPlayerAnimationState animationState;

	class AWeapon* currentWeapon;

	class ARifle* rifle;
	class ABazooka* bazooka;
	class AHandGrenade* handGrenade;
};
