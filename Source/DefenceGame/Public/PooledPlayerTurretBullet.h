#pragma once

#include "CoreMinimal.h"
#include "PooledPlayerBullet.h"
#include "PooledPlayerTurretBullet.generated.h"


UCLASS()
class DEFENCEGAME_API APooledPlayerTurretBullet : public APooledPlayerBullet
{
	GENERATED_BODY()

public:
	APooledPlayerTurretBullet();

protected:
	virtual void OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult) override;
};
