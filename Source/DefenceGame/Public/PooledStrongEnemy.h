#pragma once

#include "CoreMinimal.h"
#include "PooledEnemy.h"
#include "PooledStrongEnemy.generated.h"


UCLASS()
class DEFENCEGAME_API APooledStrongEnemy : public APooledEnemy
{
	GENERATED_BODY()
	
public:
	APooledStrongEnemy();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Attack(AActor* target) override;

protected:
	virtual void Reset() override;


public:
	class AEnemyAxe* axe;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USkeletalMeshComponent* axeMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* axeBox;

	UPROPERTY()
	class UcharacterHPWidget* shpWidget;

	void OnTakeSEnemyDamage(float attack);

private:

	float HP = 50;
};
