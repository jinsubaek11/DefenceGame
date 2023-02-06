#pragma once

#include "CoreMinimal.h"
#include "PooledEnemy.h"
#include "PooledStrongEnemy.generated.h"


UCLASS()
class DEFENCEGAME_API APooledStrongEnemy : public APooledEnemy
{
	GENERATED_BODY()
	
public:
	APooledStrongEnemy();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Attack(AActor* target) override;

protected:
	virtual void Reset() override;

private:
	class AStrongEnemyBulletPool* strongEnemyBulletPool;
	const float HP = 50;

	class AEnemyAxe* axe;
};
