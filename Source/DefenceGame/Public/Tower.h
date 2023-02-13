#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

UCLASS()
class DEFENCEGAME_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	ATower();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnTakeDamage(float attack);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* meshComponent;
	UPROPERTY()
	class AGamePlayer* gPlayer;
	UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	class UWidgetComponent* towerHPui;
	UPROPERTY()
	TSubclassOf<class UUserWidget> widgetFactory;
	UPROPERTY()
	class UHPWidget* chpWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float towerHP = 100000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float towerMaxHP = 100000;

private:
	class ADefenceGameMode* gameMode;
};

