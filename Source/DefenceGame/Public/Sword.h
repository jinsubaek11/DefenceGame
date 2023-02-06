#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Sword.generated.h"


UCLASS()
class DEFENCEGAME_API ASword : public AWeapon
{
	GENERATED_BODY()
	
public:
	ASword();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
