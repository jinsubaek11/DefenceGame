#pragma once

#include "CoreMinimal.h"
#include "BossAnimInstance.h"
#include "Weapon.h"
#include "PooledEnemy.h"
#include "PooledBossEnemy.generated.h"

UENUM()
enum class EBossAttackType : uint8
{
	SHOOTING_ARROW,
};

UCLASS()
class DEFENCEGAME_API APooledBossEnemy : public APooledEnemy
{
	GENERATED_BODY()
	
public:
	APooledBossEnemy();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void Shoot();

	void Attack(AActor* target);
	EBossAttackType GetCurrentAttackType() const;

	AWeapon* GetCurrentWeapon() const;
	WeaponType GetCurrentWeaponType() const;
	EBossAnimationState GetAnimationState() const;
	virtual void SetAnimationState(EBossAnimationState nextState) override;
	bool GetIsPlayingAnimation() const; 
	void SetIsPlayingAnimation(bool isPlaying);
	FRotator GetTargetRotation() const;

protected:
	virtual void Reset() override;

private:
	void SetCurrentWeapon(WeaponType weaponType);

public:
	UPROPERTY(EditAnywhere)
	class ASword* sword;
	UPROPERTY(EditAnywhere)
	class ABow* bow;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class AWeapon* currentWeapon;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class AArrowBox* arrowBox;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBossAnimInstance> bossAnimFactory;
	UPROPERTY(EditAnywhere)
	EBossAnimationState state = EBossAnimationState::WALKING;

	bool isPlayingAnimation;

	UPROPERTY()
	TArray<EBossAttackType> attackBehaviors;
	int32 currentAttackTypeIndex;

	FRotator targetRotation;
};
