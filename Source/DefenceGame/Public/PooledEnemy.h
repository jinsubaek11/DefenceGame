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
	void OnTakeDamage(int32 damage);
	void SetAnimationState(EEnemyAnimationState animState);
	EEnemyAnimationState GetAnimationState();

	UFUNCTION()
	void OnDeath();


protected:
	virtual void Reset();
	void SetEnemyState(float health);

public:


	UPROPERTY(EditAnywhere)
	TSubclassOf<class AController> EnemyAIControllerFactory;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAnimInstance> EnemyAnimFactory;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* planeComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect Sound")
	class USoundAttenuation* soundDistance;

	UPROPERTY()
	class UcharacterHPWidget* enemyHPwidget;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HPWidgetSettings")
	//class UWidgetComponent* enemyHPui;

protected:
	UPROPERTY(EditAnywhere, Category = MonsterProperty)
	int32 hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterAnimation)
	EEnemyAnimationState animationState;
	UPROPERTY(EditAnywhere)
	class AEnemyAIController* aiController;
	
};
