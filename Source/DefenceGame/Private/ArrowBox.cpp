#include "ArrowBox.h"
#include "Components/StaticMeshComponent.h"


AArrowBox::AArrowBox()
{
	PrimaryActorTick.bCanEverTick = false;

	boxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> boxMesh(TEXT("/Script/Engine.StaticMesh'/Game/Weapons/Bow/Mesh/ArrowBox.ArrowBox'"));
	if (boxMesh.Succeeded())
	{
		boxMeshComponent->SetStaticMesh(boxMesh.Object);
		boxMeshComponent->SetRelativeScale3D(FVector(2));
	}
	boxMeshComponent->SetupAttachment(RootComponent);

	arrow1MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow1 Mesh Component"));
	arrow2MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow2 Mesh Component"));
	arrow3MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow3 Mesh Component"));
	arrow4MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow4 Mesh Component"));
	arrow5MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow5 Mesh Component"));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> arrowMesh(TEXT("/Script/Engine.StaticMesh'/Game/Weapons/Bow/Mesh/Arrow.Arrow'"));
	if (arrowMesh.Succeeded())
	{
		arrow1MeshComponent->SetStaticMesh(arrowMesh.Object);
		arrow1MeshComponent->SetRelativeLocation(FVector(-0.2, 0.3, 18));
		arrow1MeshComponent->SetRelativeScale3D(FVector(0.5));
		arrow2MeshComponent->SetStaticMesh(arrowMesh.Object);
		arrow2MeshComponent->SetRelativeLocation(FVector(-1.4, 0.6, 15));
		arrow2MeshComponent->SetRelativeScale3D(FVector(0.5));
		arrow3MeshComponent->SetStaticMesh(arrowMesh.Object);
		arrow3MeshComponent->SetRelativeLocation(FVector(2.8, 0.85, 17));
		arrow3MeshComponent->SetRelativeScale3D(FVector(0.5));
		arrow4MeshComponent->SetStaticMesh(arrowMesh.Object);
		arrow4MeshComponent->SetRelativeLocation(FVector(1, 0.6, 16.5));
		arrow4MeshComponent->SetRelativeScale3D(FVector(0.5));
		arrow5MeshComponent->SetStaticMesh(arrowMesh.Object);
		arrow5MeshComponent->SetRelativeLocation(FVector(-3, 0.1, 17));
		arrow5MeshComponent->SetRelativeScale3D(FVector(0.5));
	}

	arrow1MeshComponent->SetupAttachment(boxMeshComponent);
	arrow2MeshComponent->SetupAttachment(boxMeshComponent);
	arrow3MeshComponent->SetupAttachment(boxMeshComponent);
	arrow4MeshComponent->SetupAttachment(boxMeshComponent);
	arrow5MeshComponent->SetupAttachment(boxMeshComponent);
}

