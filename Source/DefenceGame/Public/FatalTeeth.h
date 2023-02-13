#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "FatalTeeth.generated.h"


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

public:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
