#pragma once

#include "CoreMinimal.h"
#include "PooledEnemy.h"
#include "PooledWeakEnemy.generated.h"


UCLASS()
class DEFENCEGAME_API APooledWeakEnemy : public APooledEnemy
{
	GENERATED_BODY()

public:
	APooledWeakEnemy();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Attack(AActor* target) override;

protected:
	virtual void Reset() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* teethBox;

	//UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	//class UcharacterHPWidget* weakEnemyHPBar;

	//UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	//class UWidgetComponent* wEnemyHPui;

	UPROPERTY()
	class UcharacterHPWidget* whpWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect Sound")
	class USoundBase* teethAttackSound;



	void OnTakeWEnemyDamage(int32 damage);

private:
	class AWeakEnemyBulletPool* weakEnemyBulletPool;
	float HP = 20;

	class AFatalTeeth* teeth;
};
