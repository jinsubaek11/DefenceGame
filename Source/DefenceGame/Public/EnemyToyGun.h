#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "EnemyToyGun.generated.h"


UCLASS()
class DEFENCEGAME_API AEnemyToyGun : public AWeapon
{
	GENERATED_BODY()

public:
	AEnemyToyGun();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	void Shoot(AActor* target);



private:
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* skeletalMeshComponent;
	UPROPERTY()
	class UParticleSystem* explosion;
	UPROPERTY()
	class ANormalEnemyBulletPool* normalEnemyBulletPool;

};
