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
	int32 GetDamage() const;

protected:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;

	float speed;
	int32 damage;
};
