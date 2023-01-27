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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* meshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "HPWidgetSettings")
	class UWidgetComponent* towerHPui;
	//Pooled Enemy Bullet�� ������ ü���� �����Ѵ�.
	
	UPROPERTY()
	class UHPWidget* chpWidget;


};
