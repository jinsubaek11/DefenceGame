#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemObstacle.generated.h"


UCLASS()
class DEFENCEGAME_API AItemObstacle : public AItem
{
	GENERATED_BODY()

public:
	AItemObstacle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnBeginOverlapItem(AActor* OtherActor) override;
	virtual void OnEndOverlapItem(AActor* OtherActor) override;
};
