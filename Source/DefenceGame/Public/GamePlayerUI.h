#pragma once

#include "CoreMinimal.h"
#include "PlayerUIAnim.h"
#include "GameFramework/Actor.h"
#include "GamePlayerUI.generated.h"

UCLASS()
class DEFENCEGAME_API AGamePlayerUI : public AActor
{
	GENERATED_BODY()

public:
	AGamePlayerUI();

protected:
	virtual void BeginPlay() override;

public:
	USkeletalMeshComponent* GetMesh() const;
	void SetAnimationState(EPlayerUIAnimationState state);
	EPlayerUIAnimationState GetAnimationState() const;

private:
	UPROPERTY()
	class USceneComponent* sceneComponent;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* sceneCaptureComponent;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* skeletalMeshComponent;

	EPlayerUIAnimationState animationState;
};
