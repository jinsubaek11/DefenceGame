#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GamePlayer.generated.h"

UCLASS()
class DEFENCEGAME_API AGamePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AGamePlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void OnTakeDamage(float damage);

private:
	void OnAxisLookUp(float value);
	void OnAxisTurnRight(float value);
	void OnAxisMoveForward(float value);
	void OnAxisMoveRight(float value);
	void OnActionClick();
	void OnActionUseItemMode();

	void SetItemPosition();

public:
	UPROPERTY(EditAnywhere, Category=Camera)
	class USpringArmComponent* springArmComponent;

	UPROPERTY(EditAnywhere, Category = Camera)
	class UCameraComponent* cameraComponent;


private:
	TArray<class AItem*> obstacles;
	class AItem* newObstacle;
	FVector direction;
	float hp = 100.f;
	bool isItemMode;
};
