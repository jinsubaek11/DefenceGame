#include "PooledNormalEnemy.h"
#include "Components/CapsuleComponent.h"
#include "normalEnemyBulletPool.h"
#include "PooledNormalEnemyBullet.h"
#include "EnemyAIController.h"
#include "EnemyToyGun.h"
#include "Components/WidgetComponent.h"
#include "characterHPWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


APooledNormalEnemy::APooledNormalEnemy()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(140);
	GetCapsuleComponent()->SetCapsuleRadius(60);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Mousey/Skeleton/mousey.mousey'"));
	if (mesh.Succeeded())
	{
		USkeletalMeshComponent* meshComponent = GetMesh();
		meshComponent->SetSkeletalMesh(mesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));
		meshComponent->SetRelativeScale3D(FVector(2));
	}

	/*HP widget*/
	nEnemyHPui = CreateDefaultSubobject<UWidgetComponent>(TEXT("normalEnemyHPui"));
	nEnemyHPui->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	nEnemyHPui->SetRelativeLocationAndRotation(FVector(0, 0, 130), FRotator(0, 0, 0));
	nEnemyHPui->SetWidgetSpace(EWidgetSpace::World);

	ConstructorHelpers::FClassFinder<UUserWidget> normalEnemyhpwidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/WBP_characterHPWidget.WBP_characterHPWidget_C'"));

	if (normalEnemyhpwidget.Succeeded())
	{
		nEnemyHPui->SetWidgetClass(normalEnemyhpwidget.Class);
		nEnemyHPui->SetRelativeLocationAndRotation(FVector(0, 0, 110), FRotator(0, 0, 0));
		nEnemyHPui->SetRelativeScale3D(FVector(0.3f));
		nEnemyHPui->SetDrawSize(FVector2D(600, 500));
	}

	ConstructorHelpers::FClassFinder<AEnemyAIController> bpAIControllerClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/EnemyAI/BP_NormalEnemyAIController.BP_NormalEnemyAIController_C'"));
	if (bpAIControllerClass.Succeeded())
	{
		EnemyAIControllerFactory = bpAIControllerClass.Class;
	}

	ConstructorHelpers::FClassFinder<UEnemyAnimInstance> bpEnemyAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Enemy/Mousey/Animation/ABP_MouseyAnim.ABP_MouseyAnim_C'"));
	if (bpEnemyAnim.Succeeded())
	{
		EnemyAnimFactory = bpEnemyAnim.Class;
		GetMesh()->SetAnimInstanceClass(EnemyAnimFactory);
	}

	SetEnemyState(HP);

	/*Effect Sound*/
	nEnemyFireSound = CreateDefaultSubobject<USoundBase>(TEXT("obstacle Sound"));
	ConstructorHelpers::FObjectFinder<USoundBase> toygunFireSound(TEXT("/Script/Engine.SoundWave'/Game/Sound/Shoot1.Shoot1'"));
	if (toygunFireSound.Succeeded())
	{
		nEnemyFireSound = (toygunFireSound.Object);
	}
}

void APooledNormalEnemy::BeginPlay()
{
	Super::BeginPlay();

	normalEnemyBulletPool = GetWorld()->SpawnActor<ANormalEnemyBulletPool>();
	
	FActorSpawnParameters params;
	aiController = GetWorld()->SpawnActor<AEnemyAIController>(EnemyAIControllerFactory, params);
	if (aiController)
	{
		aiController->Possess(this);
	}	

	enemyAnim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	gun = GetWorld()->SpawnActor<AEnemyToyGun>();
	gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandSocket"));
}

void APooledNormalEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	gun->Shoot(normalEnemyBulletPool);
	APlayerCameraManager* cm = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	FRotator newRotation = UKismetMathLibrary::MakeRotFromXZ(
		cm->GetCameraLocation() - GetActorLocation(),
		GetActorUpVector());

	nEnemyHPui->SetWorldRotation(newRotation);
}

void APooledNormalEnemy::Attack(AActor* target)
{
	Super::Attack(target);

	gun->Shoot(target);
	enemyAnim->PlayShootMontage();

	/*ToyGun Fire Sound*/
	UGameplayStatics::PlaySoundAtLocation(this, nEnemyFireSound, GetActorLocation());
}

void APooledNormalEnemy::OnTakeNEnemyDamage(int32 damage)
{
	HP -= damage;
	normalEnemyHPBar->SetcharacterHP(HP);
	UE_LOG(LogTemp, Error, TEXT("Normal Enemy On Take Damage %f"), HP)
}

void APooledNormalEnemy::Reset()
{
	SetEnemyState(HP);
}