#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "HandGrenade.generated.h"


UCLASS()
class DEFENCEGAME_API AHandGrenade : public AWeapon
{
	GENERATED_BODY()
	
public:
	AHandGrenade();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Shoot() override;
	virtual void ReLoad() override;
	bool GetIsExploded();
	bool GetIsShootStart();

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DrawGrenadeOrbit();
	void ClearSpline();

private:
	UPROPERTY(EditAnywhere)
	class USphereComponent* sphereComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMesh* staticMesh;
	UPROPERTY(EditAnywhere)
	class UMaterialInterface* material;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosion;

	UPROPERTY(EditAnywhere)
	class USplineComponent* splineComponent;
	TArray<class USplineMeshComponent*> splineMesh;

	FVector launchVelocity;
	FVector gravity;
	bool isShootStart;
	bool isExploded;
	bool isOverlapped;
};
