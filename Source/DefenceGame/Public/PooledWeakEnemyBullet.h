#pragma once

#include "CoreMinimal.h"
#include "PooledEnemyBullet.h"
#include "PooledWeakEnemyBullet.generated.h"


UCLASS()
class DEFENCEGAME_API APooledWeakEnemyBullet : public APooledEnemyBullet
{
	GENERATED_BODY()
	
public:
	APooledWeakEnemyBullet();

protected:
	virtual void OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult) override;

};
