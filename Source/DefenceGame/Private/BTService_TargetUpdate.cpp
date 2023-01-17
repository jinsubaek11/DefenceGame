#include "BTService_TargetUpdate.h"
#include "GamePlayer.h"
#include "PooledEnemy.h"
#include "kismet/GameplayStatics.h"
#include "EnemyAIController.h"
#include "Tower.h"
#include "EngineUtils.h"


UBTService_TargetUpdate::UBTService_TargetUpdate()
{
	NodeName = TEXT("Target Update");
}

void UBTService_TargetUpdate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AGamePlayer* player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	float playerEnemyDistance = FVector::Distance(player->GetActorLocation(), enemy->GetActorLocation());

	if (!OwnerComp.GetAIOwner()->LineOfSightTo(player) || playerEnemyDistance >= 700)
	{
		UE_LOG(LogTemp, Warning, TEXT("Clear PlayerLocation"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}

	if (OwnerComp.GetAIOwner()->LineOfSightTo(player) && playerEnemyDistance < 700)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set PlayerLocation"));
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), player->GetActorLocation());
	}
	

}