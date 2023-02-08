#include "GamePlayerUI.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SkeletalMeshComponent.h"


AGamePlayerUI::AGamePlayerUI()
{
	PrimaryActorTick.bCanEverTick = false;

	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(sceneComponent);

	skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Player/Skeleton/Player.Player'"));
	if (mesh.Succeeded())
	{
		skeletalMeshComponent->SetSkeletalMesh(mesh.Object);
		skeletalMeshComponent->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
		skeletalMeshComponent->bReceivesDecals = false;
		skeletalMeshComponent->CastShadow = false;
	}	
	
	skeletalMeshComponent->SetupAttachment(RootComponent);

	sceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture Component"));
	sceneCaptureComponent->SetRelativeRotation(FRotator(-90, 0, 0));
	sceneCaptureComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FClassFinder<UPlayerUIAnim> bpPlayerUIAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/Animation/ABP_PlayerUIAnim.ABP_PlayerUIAnim_C'"));
	if (bpPlayerUIAnim.Succeeded())
	{
		//bossAnimFactory = bpEnemyAnim.Class;
		skeletalMeshComponent->SetAnimInstanceClass(bpPlayerUIAnim.Class);
	}
}

void AGamePlayerUI::BeginPlay()
{
	Super::BeginPlay();
	
	animationState = EPlayerUIAnimationState::IDLE;
}

USkeletalMeshComponent* AGamePlayerUI::GetMesh() const
{
	return skeletalMeshComponent;
}

void AGamePlayerUI::SetAnimationState(EPlayerUIAnimationState state)
{
	animationState = state;
}

EPlayerUIAnimationState AGamePlayerUI::GetAnimationState() const
{
	return animationState;
}


