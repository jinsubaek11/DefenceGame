// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "FatalTeeth.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API AFatalTeeth : public AWeapon
{
	GENERATED_BODY()

public:
	AFatalTeeth();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Shoot() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* boxComp;	

	class APooledWeakEnemy* pwEnemy;

	float teethAttackScore = 3;


public:

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
