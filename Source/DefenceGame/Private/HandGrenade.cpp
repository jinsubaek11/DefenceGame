#include "HandGrenade.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"


AHandGrenade::AHandGrenade()
{
	PrimaryActorTick.bCanEverTick = true;

	weaponType = WeaponType::HAND_GRENADE;

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(sphereComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComponent->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> handGrenadeMesh(TEXT("//Script/Engine.StaticMesh'/Game/Weapons/HandGrenade/HandGrenade.HandGrenade'"));
	if (handGrenadeMesh.Succeeded())
	{
		meshComponent->SetStaticMesh(handGrenadeMesh.Object);
		//meshComponent->SetRelativeLocation(FVector(20, -10, -10));
		meshComponent->SetRelativeScale3D(FVector(0.1));
	}

	splineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	splineComponent->SetupAttachment(RootComponent);

	decalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Component"));
	decalComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UMaterialInterface> decal(TEXT("/Script/Engine.Material'/Game/Material/M_Target.M_Target'"));
	if (decal.Succeeded())
	{
		decalComponent->SetDecalMaterial(decal.Object);
		decalComponent->SetRelativeRotation(FRotator(-90, 0, 0));
		decalComponent->SetRelativeScale3D(FVector(0.5));
		decalComponent->SetVisibility(false);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (mesh.Succeeded())
	{
		staticMesh = mesh.Object;
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (mat.Succeeded())
	{
		material = mat.Object;
	}

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void AHandGrenade::BeginPlay()
{
	Super::BeginPlay();

}

void AHandGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawGrenadeOrbit();
}

void AHandGrenade::Shoot()
{

}


void AHandGrenade::DrawGrenadeOrbit()
{
	splineComponent->ClearSplinePoints();
	if (splineMesh.Num() > 0)
	{
		for (auto spline : splineMesh)
		{
			spline->DestroyComponent();
		}
	}
	splineMesh.Empty();

	FHitResult hitResult;
	TArray<FVector> path;
	FVector lastPosition;

	FVector startLocation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
	startLocation.Z += 100;
	FRotator controllerRotation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetControlRotation();
	controllerRotation.Add(65, 0, 0);
	FVector launchVelocity = controllerRotation.Vector() * 900;

	FPredictProjectilePathParams params;
	params.StartLocation = startLocation;
	params.LaunchVelocity = launchVelocity;
	params.TraceChannel = ECollisionChannel::ECC_WorldStatic;
	params.bTraceWithCollision = true;
	params.MaxSimTime = 2.f;

	FPredictProjectilePathResult result;

	bool isHit = UGameplayStatics::PredictProjectilePath(GetWorld(), params, result);

	if (result.PathData.Num() > 0)
	{
		for (int i = 0; i < result.PathData.Num(); i++)
		{
			splineComponent->AddSplinePointAtIndex(result.PathData[i].Location, i, ESplineCoordinateSpace::World);
		}
	}
	
	for (int i = 0; i < splineComponent->GetNumberOfSplinePoints(); i++)
	{
		USplineMeshComponent* splineMeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		splineMeshComponent->SetStaticMesh(staticMesh);
		splineMeshComponent->SetMobility(EComponentMobility::Movable);
		//splineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		splineMeshComponent->RegisterComponentWithWorld(GetWorld());
		splineMeshComponent->AttachToComponent(splineComponent, FAttachmentTransformRules::KeepRelativeTransform);
		splineMeshComponent->SetStartScale(FVector2D(0.1f, 0.01f));
		splineMeshComponent->SetEndScale(FVector2D(0.1f, 0.01f));

		FVector startPoint = splineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		FVector startTangent = splineComponent->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
		FVector endPoint = splineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		FVector endTangent = splineComponent->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		splineMeshComponent->SetStartAndEnd(startPoint, startTangent, endPoint, endTangent);

		splineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		splineMeshComponent->CastShadow = false;

		if (material)
		{
			splineMeshComponent->SetMaterial(0, material);
		}

		splineMesh.Emplace(splineMeshComponent);
	}

	decalComponent->SetVisibility(true);
	decalComponent->SetWorldLocation(result.LastTraceDestination.Location);
}