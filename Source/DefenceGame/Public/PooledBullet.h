#pragma once

#include "CoreMinimal.h"
#include "PooledObject.h"
#include "PooledBullet.generated.h"


UCLASS()
class DEFENCEGAME_API APooledBullet : public APooledObject
{
	GENERATED_BODY()

public:
	APooledBullet();
	
public:
	virtual void Tick(float DeltaTime) override;

public:
	float GetDamage() const;

protected:
	class UBoxComponent* boxComponent;
	class UStaticMeshComponent* meshComponent;

	float speed;
	float damage;
};
