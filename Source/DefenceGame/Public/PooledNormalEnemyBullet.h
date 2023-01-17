#pragma once

#include "CoreMinimal.h"
#include "PooledEnemyBullet.h"
#include "PooledNormalEnemyBullet.generated.h"


UCLASS()
class DEFENCEGAME_API APooledNormalEnemyBullet : public APooledEnemyBullet
{
	GENERATED_BODY()
	
public:
	APooledNormalEnemyBullet();

protected:
	virtual void OnHitSpecificBullet(AActor* OtherActor) override;

};
