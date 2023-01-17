#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class DEFENCEGAME_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	bool GetIsPositionSucceed();
	bool GetIsCollision();
	void SetPositionSucceed(bool value);

protected:
	virtual void OnBeginOverlapItem(AActor* OtherActor);
	virtual void OnEndOverlapItem(AActor* OtherActor);
	void SetMaterialColor(FVector color);

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;
	UPROPERTY()
	TArray<class UMaterialInterface*> originalMaterial;
	UPROPERTY()
	class UMaterialInterface* transparentMaterial;
	UPROPERTY()
	class UMaterialInstanceDynamic* dynamicMaterial;

	UPROPERTY(EditAnywhere)
	bool isSetSucceed;
	UPROPERTY(EditAnywhere)
	bool isCollision;
};
