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

protected:
	virtual void SetPositionSucceed(bool value) override;
	//virtual void OnBeginOverlapItem(AActor* actor) override;
	//virtual void OnEndOverlapItem(AActor* actor) override;

private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;
	UPROPERTY()
	TArray<class UMaterialInterface*> originalMaterial;
};
