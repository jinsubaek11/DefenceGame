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
	virtual void ReLoad();
	void SetActive(bool value);
	bool HasRemainBullet() const;
	WeaponType GetWeaponType() const;

protected:
	virtual void DrawWeaponRange();

protected:
	WeaponType weaponType;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* muzzleFlash;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* hitFlash;
	UPROPERTY(EditAnywhere)
	class UDecalComponent* decalComponent;
	UPROPERTY(EditAnywhere)
	class UMaterialInterface* originalMaterial;
	UPROPERTY(EditAnywhere)
	class UMaterialInstanceDynamic* dynamicMaterial;

	class AGamePlayer* player;

	int32 maxBulletCounts;
	int32 bulletCounts;
	float attackRange;
	float autoDestroyRange;
	int32 att;

	FRotator decalRotation;
};
