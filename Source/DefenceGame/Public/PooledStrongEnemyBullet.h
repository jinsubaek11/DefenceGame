#pragma once

#include "CoreMinimal.h"
#include "PooledEnemyBullet.h"
#include "PooledStrongEnemyBullet.generated.h"


UCLASS()
class DEFENCEGAME_API APooledStrongEnemyBullet : public APooledEnemyBullet
{
	GENERATED_BODY()
	
public:
	APooledStrongEnemyBullet();

protected:
	virtual void OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult) override;

};
