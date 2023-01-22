#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Rifle.generated.h"


UCLASS()
class DEFENCEGAME_API ARifle : public AWeapon
{
	GENERATED_BODY()
	
public:
	ARifle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Shoot() override;

private:
	void DrawRifleRange();

public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* meshComponent;
	UPROPERTY(EditAnywhere)
	class UDecalComponent* decalComponent;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* emitParticle;

private:
	float attackRange = 1500.f;
	class AGamePlayer* player;
	class APlayerRifleBulletPool* rifleBulletPool;
};
