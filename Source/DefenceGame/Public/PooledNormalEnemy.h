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
	float HP = 30;

	UPROPERTY()
	class AEnemyToyGun* gun;

	UPROPERTY()
	class UEnemyAnimInstance* enemyAnim;

	class ANormalEnemyBulletPool* normalEnemyBulletPool;
	

public:
	UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	class UWidgetComponent* nEnemyHPui;

	UPROPERTY()
	class UcharacterHPWidget* nhpWidget;

	UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	class UcharacterHPWidget* normalEnemyHPBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect Sound")
	class USoundBase* nEnemyFireSound;

	void OnTakeNEnemyDamage(int32 damage);

};
