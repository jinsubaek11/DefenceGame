#include "HandGrenade.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "GamePlayer.h"
#include "PooledEnemy.h"


AHandGrenade::AHandGrenade()
{
	PrimaryActorTick.bCanEverTick = true;

	weaponType = WeaponType::HAND_GRENADE;
	maxBulletCounts = 1;
	bulletCounts = maxBulletCounts;
	attackRange = 2000.f;
	att = 100;

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(sphereComponent);
	sphereComponent->SetCollisionProfileName(TEXT("PlayerBulletPreset"));
	sphereComponent->SetSphereRadius(18);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComponent->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> handGrenadeMesh(TEXT("//Script/Engine.StaticMesh'/Game/Weapons/HandGrenade/HandGrenade.HandGrenade'"));
	if (handGrenadeMesh.Succeeded())
	{
		meshComponent->SetStaticMesh(handGrenadeMesh.Object);
		meshComponent->SetRelativeLocation(FVector(0, 0, -20));
		meshComponent->SetRelativeScale3D(FVector(0.1));
	}

	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (particle.Succeeded())
	{
		explosion = particle.Object;
	}

	splineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	//splineComponent->SetupAttachment(RootComponent);

	decalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Component"));

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

	gravity = FVector(0, 0, -9.8);

	SetActive(false);
}

void AHandGrenade::BeginPlay()
{
	Super::BeginPlay();

	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AHandGrenade::OnBeginOverlap);
}

void AHandGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isShootStart)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		launchVelocity += gravity * 80 * DeltaTime;
		FVector position = GetActorLocation() + launchVelocity * DeltaTime;
		SetActorLocation(position);

		decalComponent->SetVisibility(false);
		ClearSpline();
		return;
	}

	if (bulletCounts)
	{
		DrawGrenadeOrbit();
	}
}

void AHandGrenade::Shoot()
{
	Super::Shoot();

	isShootStart = true;
	isExploded = false;
}

void AHandGrenade::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (isExploded) return;

	UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap"));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, GetActorLocation());

	TArray<FHitResult> hitResults;
	FVector sweepStart = GetActorLocation();
	FVector sweepEnd = GetActorLocation();
	FCollisionShape sphereCollision = FCollisionShape::MakeSphere(350.f);
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

	DrawDebugSphere(GetWorld(), GetActorLocation(), sphereCollision.GetSphereRadius(), 50, FColor::Green, false, 3.f);

	bool isHit = GetWorld()->SweepMultiByObjectType(hitResults, sweepStart, sweepEnd, FQuat::Identity, objectQueryParams, sphereCollision);

	if (isHit)
	{
		for (auto hitResult : hitResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *hitResult.GetActor()->GetName());
			APooledEnemy* enemy = Cast<APooledEnemy>(hitResult.GetActor());
			if (enemy)
			{
				enemy->OnTakeDamage(att);
			}
		}
	}

	isShootStart = false;
	isExploded = true;
	SetActive(false);
}


void AHandGrenade::DrawGrenadeOrbit()
{
	ClearSpline();

	FHitResult hitResult;
	TArray<FVector> path;
	FVector lastPosition;

	FVector startLocation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
	startLocation.Z += 100;
	FRotator controllerRotation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetControlRotation();
	controllerRotation.Add(60, 0, 0);
	launchVelocity = controllerRotation.Vector() * 1100;

	FPredictProjectilePathParams params;
	params.StartLocation = startLocation;
	params.LaunchVelocity = launchVelocity;
	params.TraceChannel = ECollisionChannel::ECC_WorldStatic;
	params.bTraceWithCollision = true;
	params.MaxSimTime = 3.f;

	FPredictProjectilePathResult result;

	bool isHit = UGameplayStatics::PredictProjectilePath(GetWorld(), params, result);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), result.PathData.Num());
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


	FVector decalLocation = result.LastTraceDestination.Location;
	decalLocation.Z = 0;
	decalComponent->SetVisibility(true);
	decalComponent->SetWorldLocation(decalLocation);
	decalComponent->DecalSize = FVector(50, 700, 700);

}

void AHandGrenade::ClearSpline()
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
}


void AHandGrenade::ReLoad()
{
	if (isShootStart) return;

	Super::ReLoad();

	AttachToComponent(player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));
	SetActorLocation(player->GetMesh()->GetSocketLocation(TEXT("RifleSocket")));
	SetActive(true);
}

bool AHandGrenade::GetIsExploded()
{
	return isExploded;
}

bool AHandGrenade::GetIsShootStart()
{
	return isShootStart;
}
