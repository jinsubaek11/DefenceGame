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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Sound")
	class USoundBase* rifleFireSound;

private:
	virtual void DrawWeaponRange() override;

private:
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* skeletalMeshComponent;
};
