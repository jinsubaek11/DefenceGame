#pragma once

#include "CoreMinimal.h"
#include "BossAnimInstance.h"
#include "EnemyAnimInstance.h"
#include "PooledCharacter.h"
#include "PooledEnemy.generated.h"

UENUM()
enum class EEnemyType : uint8
{
	ENEMY,
	BOSS
};

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
	virtual void SetAnimationState(EBossAnimationState animState) {};
	EEnemyAnimationState GetAnimationState();
	
	void Upgrade();

	UFUNCTION()
	void OnDeath();

protected:
	virtual void ResetState() override;
	void SetEnemyState(float health);

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AController> EnemyAIControllerFactory;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAnimInstance> EnemyAnimFactory;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* planeComponent;

	UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	class UWidgetComponent* hpWidgetComponent;
	UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	class UcharacterHPWidget* hpWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Effect Sound")
	class USoundAttenuation* soundDistance;

protected:
	UPROPERTY(EditAnywhere, Category = MonsterProperty)
	int32 hp;
	UPROPERTY(EditAnywhere, Category = MonsterProperty)
	int32 maxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterAnimation)
	EEnemyAnimationState animationState;
	UPROPERTY(EditAnywhere)
	class AEnemyAIController* aiController;
	EEnemyType type = EEnemyType::ENEMY;
};
