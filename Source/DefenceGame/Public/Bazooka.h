#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Bazooka.generated.h"


UCLASS()
class DEFENCEGAME_API ABazooka : public AWeapon
{
	GENERATED_BODY()

public:
	ABazooka();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Shoot() override;

private:
	void DrawBazookaRange();

public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;
	UPROPERTY(EditAnywhere)
	class UDecalComponent* decalComponent;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* emitParticle;

private:
	float attackRange = 1500.f;
	class AGamePlayer* player;
	class APlayerRifleBulletPool* rifleBulletPool;
};
