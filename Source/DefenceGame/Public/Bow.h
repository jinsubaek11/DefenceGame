#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Bow.generated.h"

UENUM()
enum class EBowAttackType: uint8
{
	SINGLE_SHOOT,
	TRIPLE_SHOOT,
};

UCLASS()
class DEFENCEGAME_API ABow : public AWeapon
{
	GENERATED_BODY()
	
public:
	ABow();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Shoot() override;

private:	
	void SingleShoot();
	void TripleShoot();

private:
	class ABossEnemyBulletPool* bossEnemyBulletPool;
	class APooledBossEnemy* boss;
};
