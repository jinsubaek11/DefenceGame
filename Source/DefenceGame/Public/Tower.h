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
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;
};
