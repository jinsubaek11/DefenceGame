#pragma once

#include "CoreMinimal.h"
#include "EnemyAnimInstance.h"
#include "PooledCharacter.h"
#include "PooledEnemy.generated.h"


UCLASS(BlueprintType)
class DEFENCEGAME_API APooledEnemy : public APooledCharacter
{
	GENERATED_BODY()
	
public:
	APooledEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Attack(AActor* target);
	void OnTakeDamage(float damage);
	void SetAnimationState(EEnemyAnimationState animState);
	EEnemyAnimationState GetAnimationState();

protected:
	virtual void Reset();
	void SetEnemyState(float health);

protected:
	UPROPERTY(EditAnywhere, Category = MonsterProperty)
	float hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterAnimation)
	EEnemyAnimationState animationState;
	
};
