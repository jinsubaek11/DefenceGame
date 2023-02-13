#include "PooledNormalEnemy.h"
#include "Components/CapsuleComponent.h"
#include "normalEnemyBulletPool.h"
#include "PooledNormalEnemyBullet.h"
#include "EnemyAIController.h"
#include "EnemyToyGun.h"
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

void APooledNormalEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	
	if (!nhpWidget) return;
	nhpWidget->SetcharacterHP(nhpWidget->charMaxHP);
}


void APooledNormalEnemy::Attack(AActor* target)
{
	Super::Attack(target);
	//UE_LOG(LogTemp, Warning, TEXT("APooledNormalEnemy Attack"));

	gun->Shoot(target);
	enemyAnim->PlayShootMontage();

	/*ToyGun Fire Sound*/
	UGameplayStatics::PlaySoundAtLocation(this, nEnemyFireSound, GetActorLocation(), 0.7f, 1, 0, soundDistance);
}

void APooledNormalEnemy::OnTakeNEnemyDamage(int32 damage)
{
	//HP -= damage;
	//normalEnemyHPBar->SetcharacterHP(HP);
	//UE_LOG(LogTemp, Error, TEXT("Normal Enemy On Take Damage %f"), HP)
}

void APooledNormalEnemy::Reset()
{
	SetEnemyState(HP);
}