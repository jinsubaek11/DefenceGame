#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Bazooka.generated.h"


UCLASS()
class DEFENCEGAME_API ABazooka : public AWeapon
{
	GENERATED_BODY()

public:
	ABazooka();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Shoot() override;

protected:
	virtual void DrawWeaponRange() override;

private:
	UPROPERTY()
	class APlayerBazookaBulletPool* bazookaBulletPool;
	UPROPERTY()
	class UParticleSystem* trailEffect;
};
