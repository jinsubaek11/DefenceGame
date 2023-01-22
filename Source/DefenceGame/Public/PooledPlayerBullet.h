#pragma once

#include "CoreMinimal.h"
#include "PooledBullet.h"
#include "PooledPlayerBullet.generated.h"


UCLASS()
class DEFENCEGAME_API APooledPlayerBullet : public APooledBullet
{
	GENERATED_BODY()
	
public:
	APooledPlayerBullet();

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
	virtual void OnHitSpecificBullet(AActor* OtherActor);

};
