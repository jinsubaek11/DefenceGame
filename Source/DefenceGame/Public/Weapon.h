#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM()
enum class WeaponType: uint8
{
	RIFLE = 1,
	BAZOOKA,
	HAND_GRENADE
};

UCLASS()
class DEFENCEGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Shoot();
	void SetActive(bool value);
	WeaponType GetWeaponType() const;

protected:
	WeaponType weaponType;
};
