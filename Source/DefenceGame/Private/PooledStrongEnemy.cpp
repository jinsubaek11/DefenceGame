#include "PooledStrongEnemy.h"
#include "StrongEnemyBulletPool.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAIController.h"
#include "EnemyAxe.h"
#include "characterHPWidget.h"
#include "PooledStrongEnemyBullet.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


APooledStrongEnemy::APooledStrongEnemy()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(140);
	GetCapsuleComponent()->SetCapsuleRadius(60);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Doosey/Skeleton/doosey.doosey'"));
	if (mesh.Succeeded())
	{
		USkeletalMeshComponent* meshComponent = GetMesh();
		meshComponent->SetSkeletalMesh(mesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));
		meshComponent->SetRelativeScale3D(FVector(2));
	}

	ConstructorHelpers::FClassFinder<AEnemyAIController> bpAIControllerClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/EnemyAI/BP_StrongEnemyAIController.BP_StrongEnemyAIController_C'"));
	if (bpAIControllerClass.Succeeded())
	{
		EnemyAIControllerFactory = bpAIControllerClass.Class;
	}

	ConstructorHelpers::FClassFinder<UEnemyAnimInstance> bpEnemyAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Enemy/Doosey/Animation/ABP_DooseyAnim.ABP_DooseyAnim_C'"));
	if (bpEnemyAnim.Succeeded())
	{
		EnemyAnimFactory = bpEnemyAnim.Class;
		GetMesh()->SetAnimInstanceClass(EnemyAnimFactory);
	}

	SetEnemyState(HP);

	/*Effect Sound*/
	axeHitSound = CreateDefaultSubobject<USoundBase>(TEXT("axeHitSound Sound"));
	ConstructorHelpers::FObjectFinder<USoundBase> axeSound(TEXT("/Script/Engine.SoundWave'/Game/Sound/Wood2.Wood2'"));
	if (axeSound.Succeeded())
	{
		axeHitSound = (axeSound.Object);
	}
}

void APooledStrongEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APooledStrongEnemy::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters params;
	//strongEnemyBulletPool = GetWorld()->SpawnActor<AStrongEnemyBulletPool>();
	

	aiController = GetWorld()->SpawnActor<AEnemyAIController>(EnemyAIControllerFactory, params);
	if (aiController)
	{
		aiController->Possess(this);
	}

	axe = GetWorld()->SpawnActor<AEnemyAxe>();
	axe->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandaxeSocket"));
	//axe->AddActorLocalOffset(FVector(97, 9, 13));
	//axe->AddActorLocalRotation(FRotator(0, 16, 11));
}

void APooledStrongEnemy::Attack(AActor* target)
{
	Super::Attack(target);

	SetAnimationState(EEnemyAnimationState::ATTACK);
	axe->Shoot();
	UGameplayStatics::PlaySoundAtLocation(this, axeHitSound, GetActorLocation(), 0.7f, 1, 0, soundDistance);
}

void APooledStrongEnemy::Reset()
{
	SetEnemyState(HP);
}

void APooledStrongEnemy::OnTakeSEnemyDamage(float attack)
{
	//if (!shpWidget) return;

	//HP -= attack;
	//UE_LOG(LogTemp, Warning, TEXT("APooledStrongEnemy_____________Damage %f"), HP)

	//	shpWidget->SetcharacterHP(HP);
}

//void APooledStrongEnemy::OnTakeSEnemyDamagePlayer(int32 damage)
//{
//	HP -= damage;
//	shpWidget->SetcharacterHP(HP);
//	UE_LOG(LogTemp, Error, TEXT("Strong Enemy On Take Damage %f"), HP)
//}