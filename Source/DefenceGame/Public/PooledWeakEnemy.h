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

private:
	class AWeakEnemyBulletPool* weakEnemyBulletPool;
	const float HP = 20;

	class AFatalTeeth* teeth;
};
