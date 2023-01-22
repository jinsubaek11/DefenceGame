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

protected:
	virtual void OnHitSpecificBullet(AActor* OtherActor) override;

};
