// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "EnemyAxe.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API AEnemyAxe : public AWeapon
{
	GENERATED_BODY()

public:
	AEnemyAxe();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Shoot() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* axeMeshComp;

	class APooledStrongEnemy* psEnemy;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APooledStrongEnemyBullet> sEnemyBulletPool;

	float axeAttackScore = 10;


	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	
};
