#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Item.h"
#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GamePlayer.generated.h"

DECLARE_DELEGATE_OneParam(FInputSwitchWeapon, int32);
DECLARE_DELEGATE_OneParam(FInputSwitchItem, int32);

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
	void SetAttackMode(bool isAttackMode);
	void SetIsShoot(bool value);
	void SetAnimationState(EPlayerAnimationState state);
	EPlayerAnimationState GetAnimationState();

private:
	void OnAxisLookUp(float value);
	void OnAxisTurnRight(float value);
	void OnAxisMoveForward(float value);
	void OnAxisMoveRight(float value);
	void OnActionClick();
	void OnActionReLoad();
	void OnActionJump();

	UFUNCTION()
	void OnActionUseItemMode(int32 itemIndex);
	UFUNCTION()
	void OnActionSwitchWeapon(int32 weaponIndex);

	void CheckEnableItemPosition(class AItem& item);
	void ClearItem();

public:
	UPROPERTY(EditAnywhere, Category=Camera)
	class USpringArmComponent* springArmComponent;
	UPROPERTY(EditAnywhere, Category=Camera)
	class UCameraComponent* cameraComponent;
	UPROPERTY(EditAnywhere, Category = Icon)
	class UStaticMeshComponent* planeComponent;


private:
	TArray<class AItem*> items;
	class AItem* newItem;
	FTimerHandle animationTimer;
	FVector direction;
	float hp = 100.f;
	float maxHp = 100.f;
	bool isAttackEnable;
	bool isShoot;

	bool isItemMode;
	ItemType currentItemType;
	float itemCoolTime;
	float obstacleRemainingTime;
	float turretRemainingTime;
	float second = 1.f;

	class AGamePlayerUI* playerUI;
	EPlayerAnimationState animationState;

	class AWeapon* currentWeapon;

	class ARifle* rifle;
	class ABazooka* bazooka;
	class AHandGrenade* handGrenade;

	class ADefenceGameMode* gameMode;
};
