#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM()
enum class ItemType
{
	NONE,
	OBSTACLE,
	TURRET
};

UCLASS()
class DEFENCEGAME_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	ItemType GetType() const;
	float GetCoolTime() const;
	bool GetIsPositionSucceed() const;
	bool GetIsCollision() const;
	virtual void SetPositionSucceed(bool value);
	void OnTakeDamage(int32 damage);

protected:
	virtual void OnBeginOverlapItem(AActor* actor);
	virtual void OnEndOverlapItem(AActor* actor);
	void SetMaterialColor(FVector color);

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	class UWidgetComponent* hpWidgetComponent;
	UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	class UcharacterHPWidget* hpWidget;

protected:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	UPROPERTY()
	class UMaterialInterface* transparentMaterial;
	UPROPERTY()
	class UMaterialInstanceDynamic* dynamicMaterial;

	UPROPERTY(EditAnywhere)
	bool isSetSucceed;
	UPROPERTY(EditAnywhere)
	bool isCollision;

	ItemType type;
	int32 hp;
	int32 maxHp;
	float coolTime;
};
