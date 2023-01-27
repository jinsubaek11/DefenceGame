#include "BTService_TargetUpdate.h"
#include "GamePlayer.h"
#include "PooledEnemy.h"
#include "kismet/GameplayStatics.h"
#include "EnemyAIController.h"
#include "Tower.h"
#include "Item.h"
#include "EngineUtils.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_TargetUpdate::UBTService_TargetUpdate()
{
	NodeName = TEXT("Target Update");
}

void UBTService_TargetUpdate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AGamePlayer* player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	AItem* item = nullptr;

	float towerToEnemyDistance = FVector::Distance(OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("TowerLocation")), enemy->GetActorLocation());
	float playerToEnemyDistance = FVector::Distance(player->GetActorLocation(), enemy->GetActorLocation());
	float itemToEnemyDistance = 98765421.f;
	
	for (TActorIterator<AItem> itemIter(GetWorld()); itemIter; ++itemIter)
	{
		float distance = enemy->GetDistanceTo(*itemIter);
		if (itemToEnemyDistance > distance)
		{
			itemToEnemyDistance = distance;
			item = *itemIter;
		}
	}

	if (item && OwnerComp.GetAIOwner()->LineOfSightTo(item))
	{
		if (itemToEnemyDistance < playerToEnemyDistance && itemToEnemyDistance < 700)
		{
			OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("ItemLocation"), item->GetActorLocation());
		}

		return;
	}
	
	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("ItemLocation"));

	if (!OwnerComp.GetAIOwner()->LineOfSightTo(player) || 
		playerToEnemyDistance >= 700)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}

	if (OwnerComp.GetAIOwner()->LineOfSightTo(player) && 
		playerToEnemyDistance < 700)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), player->GetActorLocation());
	}
}