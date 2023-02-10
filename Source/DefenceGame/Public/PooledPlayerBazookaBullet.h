#pragma once

#include "CoreMinimal.h"
#include "PooledPlayerBullet.h"
#include "PooledPlayerBazookaBullet.generated.h"


UCLASS()
class DEFENCEGAME_API APooledPlayerBazookaBullet : public APooledPlayerBullet
{
	GENERATED_BODY()
	
public:
	APooledPlayerBazookaBullet();

public:
	virtual void Tick(float DeltaTime) override;

public:
	void SetDestroyRange(FVector spawnPosition, float range);

protected:
	virtual void OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult) override;

private:
	void SpawnExplosionParticle(const FVector& location);

private:
	UPROPERTY()
	class UParticleSystem* explosion;

	FVector spawnPosition;
	FVector currentPosition;

	float autoDestroyRange;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Sound")
	class USoundBase* bazookaFireSound;
	
};
