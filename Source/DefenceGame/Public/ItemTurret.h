#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemTurret.generated.h"


UCLASS()
class DEFENCEGAME_API AItemTurret : public AItem
{
	GENERATED_BODY()
	
public:
	AItemTurret();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	virtual void SetPositionSucceed(bool value);

private:
	void StareEnemy(FRotator enemyRotation);
	void Shoot(class APooledEnemy* target);

private:
	UPROPERTY()
	class APlayerTurretBulletPool* turretBulletPool;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* towerTurretComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* towerBaseComponent;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* turretFlash;

	UPROPERTY(EditAnywhere)
	class APooledPlayerBullet* turretBullet;

	UPROPERTY()
	TArray<class UMaterialInterface*> originalTowerTurretMaterial;
	UPROPERTY()
	TArray<class UMaterialInterface*> originalTowerBaseMaterial;

	float currentTime;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect Sound")
	class USoundBase* turretFireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect Sound")
	class USoundBase* turretinstallSound;
};
