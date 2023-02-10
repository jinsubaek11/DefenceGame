#pragma once

#include "CoreMinimal.h"
#include "PooledBullet.h"
#include "PooledEnemyBullet.generated.h"


UCLASS()
class DEFENCEGAME_API APooledEnemyBullet : public APooledBullet
{
	GENERATED_BODY()

public:
	APooledEnemyBullet();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult
	);

protected:
	virtual void SpawnEffect(FVector location);
	virtual void OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult);

public:

	//공격 한번의 점수 10
	int32 attackScore = 10;
};
