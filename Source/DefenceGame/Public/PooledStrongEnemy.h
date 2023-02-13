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
	float HP = 50;

	class AEnemyAxe* axe;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* axeBox;

	//UPROPERTY()
	//	class UcharacterHPWidget* shpWidget;

	//UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	//	class UWidgetComponent* strongEnemyHPui;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect Sound")
	class USoundBase* axeHitSound;

	//금고에 공격
	void OnTakeSEnemyDamage(float attack);

	//플레이어의 공격
	//void OnTakeSEnemyDamagePlayer(int32 damage);
};
