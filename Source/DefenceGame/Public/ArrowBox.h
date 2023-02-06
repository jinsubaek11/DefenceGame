#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowBox.generated.h"


UCLASS()
class DEFENCEGAME_API AArrowBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AArrowBox();

private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* boxMeshComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* arrow1MeshComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* arrow2MeshComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* arrow3MeshComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* arrow4MeshComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* arrow5MeshComponent;
};
