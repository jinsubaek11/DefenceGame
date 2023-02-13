#include "PlayerAnimInstance.h"
#include "GamePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"
#include "Rifle.h"


UPlayerAnimInstance::UPlayerAnimInstance()
{

}

void UPlayerAnimInstance::NativeInitializeAnimation()
{

}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	player = Cast<AGamePlayer>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!player) return;

	FRotator rotation = player->GetActorRotation();
	FVector velocity = player->GetCharacterMovement()->Velocity;

	speed = velocity.Size();
	direction = UKismetAnimationLibrary::CalculateDirection(velocity, rotation);
	isMovingOnGround = player->GetCharacterMovement()->IsMovingOnGround();

	animationState = player->GetAnimationState();
}


void UPlayerAnimInstance::AnimNotify_JumpEnd()
{
	//UE_LOG(LogTemp, Warning, TEXT("AnimNotify_JumpEnd"));
	if (!player) return;	
	
	player->SetAnimationState(EPlayerAnimationState::MOVE);
}

void UPlayerAnimInstance::AnimNotify_ShootStart()
{
	if (!player) return;

	OnShoot.Broadcast();
	//player->SetAttackEnable(true);
}

void UPlayerAnimInstance::AnimNotify_ShootEnd()
{
	if (!player) return;

	//player->GetRifle()->SetActorRelativeRotation(FRotator(40, -20, 125));
	player->SetIsShoot(false);
	player->SetAnimationState(EPlayerAnimationState::MOVE);
}

