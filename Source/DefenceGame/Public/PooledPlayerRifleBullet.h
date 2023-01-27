#pragma once

#include "CoreMinimal.h"
#include "PooledPlayerBullet.h"
#include "PooledPlayerRifleBullet.generated.h"


UCLASS()
class DEFENCEGAME_API APooledPlayerRifleBullet : public APooledPlayerBullet
{
	GENERATED_BODY()
	
public:
	APooledPlayerRifleBullet();

protected:
	virtual void OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult) override;

};
