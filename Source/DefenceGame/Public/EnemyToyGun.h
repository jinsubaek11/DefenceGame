// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "EnemyToyGun.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API AEnemyToyGun : public AWeapon
{
	GENERATED_BODY()

public:
	AEnemyToyGun();

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Shoot() override;


private:
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* skeletalMeshComponent;

	UPROPERTY()
	class UParticleSystem* explosion;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APooledNormalEnemyBullet> nEnemyBulletPool;

};
