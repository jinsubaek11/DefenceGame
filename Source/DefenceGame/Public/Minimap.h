#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Minimap.generated.h"

UCLASS()
class DEFENCEGAME_API AMinimap : public AActor
{
	GENERATED_BODY()
	
public:	
	AMinimap();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	class USceneComponent* sceneComponent;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* sceneCaptureComponent;
};
