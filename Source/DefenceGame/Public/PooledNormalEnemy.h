#pragma once

#include "CoreMinimal.h"
#include "PooledEnemy.h"
#include "PooledNormalEnemy.generated.h"


UCLASS()
class DEFENCEGAME_API APooledNormalEnemy : public APooledEnemy
{
	GENERATED_BODY()
	
public:
	APooledNormalEnemy();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Attack(AActor* target) override;

protected:
	virtual void Reset() override;

private:
	const float HP = 30;
	UPROPERTY()
	class AEnemyToyGun* gun;
	UPROPERTY()
	class UEnemyAnimInstance* enemyAnim;
};
