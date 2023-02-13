#include "PooledWeakEnemy.h"

#include "characterHPWidget.h"
#include "WeakEnemyBulletPool.h"
#include "PooledWeakEnemyBullet.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "EnemyAIController.h"
#include "FatalTeeth.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


APooledWeakEnemy::APooledWeakEnemy()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(120);
	GetCapsuleComponent()->SetCapsuleRadius(40);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Zombie/Skeleton/zombie.zombie'"));
	if (mesh.Succeeded())
	{
		USkeletalMeshComponent* meshComponent = GetMesh();
		meshComponent->SetSkeletalMesh(mesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, 0, -120), FRotator(0, -90, 0));
		meshComponent->SetRelativeScale3D(FVector(1.5, 1.5, 1.3));
	}

	teethBox = CreateDefaultSubobject<UBoxComponent>(TEXT("teethBox"));
	teethBox->SetupAttachment(GetMesh(), TEXT("TeethSocket"));
	teethBox->SetRelativeLocation(FVector(0, 52, 156));

	///*HP widget*/
	//wEnemyHPui = CreateDefaultSubobject<UWidgetComponent>(TEXT("weakEnemyHPui"));
	//wEnemyHPui->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//wEnemyHPui->SetRelativeLocationAndRotation(FVector(0, 0, 110), FRotator(0, 0, 0));
	//wEnemyHPui->SetWidgetSpace(EWidgetSpace::World);

	//ConstructorHelpers::FClassFinder<UUserWidget> weakEnemyhpwidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/WBP_characterHPWidget.WBP_characterHPWidget_C'"));

	//if (weakEnemyhpwidget.Succeeded())
	//{
	//	wEnemyHPui->SetWidgetClass(weakEnemyhpwidget.Class);
	//	wEnemyHPui->SetRelativeLocation(FVector(0, 0, 100));
	//	wEnemyHPui->SetRelativeScale3D(FVector(0.3f));
	//	wEnemyHPui->SetDrawSize(FVector2D(600, 500));
	//}

	ConstructorHelpers::FClassFinder<AEnemyAIController> bpAIControllerClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/EnemyAI/BP_WeakEnemyAIController.BP_WeakEnemyAIController_C'"));
	if (bpAIControllerClass.Succeeded())
	{
		EnemyAIControllerFactory = bpAIControllerClass.Class;
	}

	ConstructorHelpers::FClassFinder<UEnemyAnimInstance> bpEnemyAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Enemy/Zombie/Animation/ABP_ZombieAnim.ABP_ZombieAnim_C'"));
	if (bpEnemyAnim.Succeeded())
	{
		EnemyAnimFactory = bpEnemyAnim.Class;
		GetMesh()->SetAnimInstanceClass(EnemyAnimFactory);
	}

	SetEnemyState(HP);

	/*Effect Sound*/
	teethAttackSound = CreateDefaultSubobject<USoundBase>(TEXT("rifle Fire Sound"));
	ConstructorHelpers::FObjectFinder<USoundBase> teethSound(TEXT("/Script/Engine.SoundWave'/Game/Sound/Teeth_Sound1.Teeth_Sound1'"));
	if (teethSound.Succeeded())
	{
		teethAttackSound = (teethSound.Object);
	}

}

void APooledWeakEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APooledWeakEnemy::BeginPlay()
{
	Super::BeginPlay();

	//weakEnemyBulletPool = GetWorld()->SpawnActor<AWeakEnemyBulletPool>();

	FActorSpawnParameters params;
	aiController = GetWorld()->SpawnActor<AEnemyAIController>(EnemyAIControllerFactory, params);
	if (aiController)
	{
		aiController->Possess(this);
	}

	teeth = GetWorld()->SpawnActor<AFatalTeeth>();
	teeth->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("TeethSocket"));
}

void APooledWeakEnemy::Attack(AActor* target)
{
	Super::Attack(target);

	SetAnimationState(EEnemyAnimationState::ATTACK);

	teeth->Shoot();
	UGameplayStatics::PlaySoundAtLocation(this, teethAttackSound, GetActorLocation(), GetActorRotation(), 2);
	
}

void APooledWeakEnemy::OnTakeWEnemyDamage(int32 damage)
{
	//HP -= damage;
	//weakEnemyHPBar->SetcharacterHP(HP);
	//UE_LOG(LogTemp, Error, TEXT("Normal Enemy On Take Damage %f"), HP)
}

void APooledWeakEnemy::Reset()
{
	SetEnemyState(HP);
}