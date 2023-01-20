#include "GamePlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/Controller.h>
#include <Camera/CameraComponent.h>
#include "NormalEnemyPool.h"
#include "PooledCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GamePlayerCameraManager.h"
#include "ItemObstacle.h"
#include "Item.h"


AGamePlayer::AGamePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
	if (mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(mesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerPreset"));

	springArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	springArmComponent->SetupAttachment(RootComponent);
	springArmComponent->SetRelativeLocation(FVector(0, 70, 90));
	springArmComponent->TargetArmLength = 400;
	springArmComponent->bUsePawnControlRotation = true;
	
	cameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	cameraComponent->SetupAttachment(springArmComponent);


	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AGamePlayer::BeginPlay()
{
	Super::BeginPlay();

	isItemMode = true;
}

void AGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isItemMode)
	{
		if (newObstacle)
		{
			newObstacle->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 400);
			newObstacle->SetActorRotation(GetActorRotation().Add(0, 90, 0));
		}
		//FVector start = GetActorLocation() + GetActorForwardVector() * 100;
		//FVector end;

		//if (.Pitch <= 0)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("dd"));
		//	end = start + GetControlRotation().Vector() * -GetControlRotation().Pitch * 100;
		//}
		//else
		//{
		//	end = start + GetControlRotation().Vector() * GetControlRotation().Pitch * 100;
		//}
		//
		//end.Z = 1;

		//FHitResult hitResult;
		//FVector start = cameraComponent->GetComponentLocation();
		//FVector end = start + 

		//if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility))
		//{
			//DrawDebugLine(GetWorld(), start, end, FColor::Red);
		
			//DrawCircle(GetWorld(), end, FVector(1, 0, 0), FVector(0, 1, 0), FColor::Red, 200, 30, 0, 100);
		//}
		return;
	}

	//FMeshBatch meshbat;
	//FVertexFactory vf;

	//meshbat.VertexFactory = 

	//DrawRectangleMesh(GetWorld(),  )
}

void AGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &AGamePlayer::OnAxisLookUp);
	PlayerInputComponent->BindAxis("TurnRight", this, &AGamePlayer::OnAxisTurnRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AGamePlayer::OnAxisMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGamePlayer::OnAxisMoveRight);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionClick);
	PlayerInputComponent->BindAction("UseObstacle", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionUseItemMode);
}

void AGamePlayer::OnTakeDamage(float damage)
{
	hp -= damage;

	UE_LOG(LogTemp, Warning, TEXT("%f"), hp);
	// hp 0 Ã³¸®
}

void AGamePlayer::OnAxisLookUp(float value)
{
	//if (isItemMode) return;

	AddControllerPitchInput(value * 0.3);
}

void AGamePlayer::OnAxisTurnRight(float value)
{
	//if (isItemMode) return;

	AddControllerYawInput(value * 0.3);
}

void AGamePlayer::OnAxisMoveForward(float value)
{
	FVector axisX = FVector(value, 0, 0).RotateAngleAxis(
		GetControlRotation().Yaw, FVector(0, 0, 1)
	);

	AddMovementInput(axisX);
}

void AGamePlayer::OnAxisMoveRight(float value)
{
	FVector axisY = FVector(0, value, 0).RotateAngleAxis(
		GetControlRotation().Yaw, FVector(0, 0, 1)
	);

	AddMovementInput(axisY);
}

void AGamePlayer::OnActionClick()
{
	if (isItemMode)
	{
		if (!newObstacle) return;

		if (!newObstacle->GetIsPositionSucceed() && !newObstacle->GetIsCollision())
		{
			newObstacle->SetPositionSucceed(true);
			obstacles.Emplace(newObstacle);
			newObstacle = nullptr;
			isItemMode = false;
		}
	}

	//fire
}

void AGamePlayer::OnActionUseItemMode()
{
	if (newObstacle) return;

	newObstacle = GetWorld()->SpawnActor<AItemObstacle>(GetActorLocation() + GetActorForwardVector() * 300, GetActorRotation());
	isItemMode = true;
}

void AGamePlayer::SetItemPosition()
{

}
