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
	void DrawGrenadeOrbit();

private:
	UPROPERTY(EditAnywhere)
	class USphereComponent* sphereComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMesh* staticMesh;
	UPROPERTY(EditAnywhere)
	class UMaterialInterface* material;
	UPROPERTY(EditAnywhere)
	class UDecalComponent* decalComponent;

	UPROPERTY(EditAnywhere)
	class USplineComponent* splineComponent;
	TArray<class USplineMeshComponent*> splineMesh;
};
