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
#include "HandGrenade.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Rifle.h"
#include "Bazooka.h"
#include "Weapon.h"

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

	animationState = EPlayerAnimationState::MOVE;

	rifle = GetWorld()->SpawnActor<ARifle>();
	rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));
	bazooka = GetWorld()->SpawnActor<ABazooka>();
	bazooka->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));
	handGrenade = GetWorld()->SpawnActor<AHandGrenade>();
	handGrenade->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));

	currentWeapon = Cast<AWeapon>(rifle);
	//GetActorLocation() + GetActorForwardVector() * 300, GetActorRotation()

	//isItemMode = true;

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

	if (isAttackEnable)
	{
		//currentWeapon->
		//currentWeapon->Shoot();
		//SetAttackEnable(false);
	}
	else
	{
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
	PlayerInputComponent->BindAction<FInputSwitchWeapon>("UseRifle", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionSwitchWeapon, 1);
	PlayerInputComponent->BindAction<FInputSwitchWeapon>("UseBazooka", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionSwitchWeapon, 2);
	PlayerInputComponent->BindAction<FInputSwitchWeapon>("UseHandGrenade", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionSwitchWeapon, 3);
	PlayerInputComponent->BindAction("UseObstacle", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionUseItemMode);
}

void AGamePlayer::OnTakeDamage(float damage)
{
	hp -= damage;

	UE_LOG(LogTemp, Warning, TEXT("%f"), hp);
	// hp 0 ó��
}

void AGamePlayer::SetAttackAnimation(WeaponType weaponType)
{
	switch (weaponType)
	{
	case WeaponType::RIFLE:
		rifle->SetActorRelativeRotation(FRotator(0, 270, 95));
		SetAnimationState(EPlayerAnimationState::SHOOT_RIFLE);
		break;
	case WeaponType::BAZOOKA:
		SetAnimationState(EPlayerAnimationState::SHOOT_BAZOOKA);
		break;
	case WeaponType::HAND_GRENADE:
		SetAnimationState(EPlayerAnimationState::SHOOT_GRENADE);
		break;
	}

}

void AGamePlayer::SetAttackEnable(bool value)
{
	isAttackEnable = value;
}

void AGamePlayer::SetAnimationState(EPlayerAnimationState state)
{
	//if (animationState == state) return;

	animationState = state;
}

EPlayerAnimationState AGamePlayer::GetAnimationState()
{
	return animationState;
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

		return;
	}

	//fire
	//Attack();
	SetAttackAnimation(currentWeapon->GetWeaponType());
	//rifle->Shoot();
	//rifle->SetActorRelativeRotation(FRotator(0, 270, 95));
	//SetAnimationState(EPlayerAnimationState::SHOOT_RIFLE);
}

void AGamePlayer::OnActionUseItemMode()
{
	if (newObstacle) return;

	newObstacle = GetWorld()->SpawnActor<AItemObstacle>(GetActorLocation() + GetActorForwardVector() * 300, GetActorRotation());
	isItemMode = true;
}

void AGamePlayer::OnActionSwitchWeapon(int32 weaponIndex)
{
	currentWeapon->SetActive(false);

	switch ((WeaponType)weaponIndex)
	{
	case WeaponType::RIFLE:
		currentWeapon = Cast<AWeapon>(rifle);
		break;
	case WeaponType::BAZOOKA:
		currentWeapon = Cast<AWeapon>(bazooka);
		break;
	case WeaponType::HAND_GRENADE:
		currentWeapon = Cast<AWeapon>(handGrenade);
		break;
	}

	currentWeapon->SetActive(true);
}

ARifle* AGamePlayer::GetRifle()
{
	return rifle;
}