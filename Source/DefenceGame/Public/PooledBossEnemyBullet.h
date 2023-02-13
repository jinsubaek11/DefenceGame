#pragma once

#include "CoreMinimal.h"
#include "PooledEnemyBullet.h"
#include "PooledBossEnemyBullet.generated.h"


UCLASS()
class DEFENCEGAME_API APooledBossEnemyBullet : public APooledEnemyBullet
{
	GENERATED_BODY()
	
public:
	APooledBossEnemyBullet();

public:
	virtual void Tick(float DeltaTime) override;

public:
	void SetDestroyRange(FVector startPosition, float range = 1200.f);
	void DrawExplosionRange();

private:
	virtual void SpawnEffect(FVector location) override;
	virtual void OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult) override;
	void Explode();

private:
	UPROPERTY()
	class UParticleSystem* explosion;
	UPROPERTY(EditAnywhere)
	class UDecalComponent* decalComponent;

	FVector currentPosition;
	FVector spawnPosition;
	float autoDestroyRange = 1200.f;
};
