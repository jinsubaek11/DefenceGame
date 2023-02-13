#include "BTService_BossTargetUpdate.h"
#include "GamePlayer.h"
#include "PooledBossEnemy.h"
#include "Tower.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "EngineUtils.h"


UBTService_BossTargetUpdate::UBTService_BossTargetUpdate()
{
	NodeName = TEXT("Boss Target Update");
}

void UBTService_BossTargetUpdate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AGamePlayer* player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	APooledBossEnemy* boss = Cast<APooledBossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (!player || !boss) return;
	if (boss->GetIsPlayingAnimation()) return;

	// player

	float playerToBossDistance = player->GetDistanceTo(boss);

	if (playerToBossDistance > chaseRange)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Player"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}

	if (playerToBossDistance < detectRange)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), player);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), player->GetActorLocation());
		return;
	}

	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Player"));
	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));

	// item

	AItem* item = nullptr;
	float itemToEnemyDistance = 98765421.f;

	for (TActorIterator<AItem> itemIter(GetWorld()); itemIter; ++itemIter)
	{
		float distance = boss->GetDistanceTo(*itemIter);
		if (itemToEnemyDistance > distance)
		{
			itemToEnemyDistance = distance;
			item = *itemIter;
		}
	}

	if (item)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Item"), item);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("ItemLocation"), item->GetActorLocation());
		return;
	}

	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Item"));
	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("ItemLocation"));


	/*AActor* tower = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Tower")));
	AGamePlayer* player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	APooledBossEnemy* enemy = Cast<APooledBossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	AItem* item = nullptr;

	if (!tower || !player || !enemy) return;

	float towerToEnemyDistance = FVector::Distance(tower->GetActorLocation(), enemy->GetActorLocation());
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

	if (item && OwnerComp.GetAIOwner()->LineOfSightTo(item) && item->GetIsPositionSucceed())
	{
		if ((itemToEnemyDistance < playerToEnemyDistance && itemToEnemyDistance < 700) ||
			itemToEnemyDistance < towerToEnemyDistance)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("ItemLocation"), item->GetActorLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Item"), item);
		}
		return;

	}

	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("ItemLocation"));
	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Item"));

	if (playerToEnemyDistance > 1200)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Player"));
	}

	if (playerToEnemyDistance < 1200)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), player->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), player);

	}*/
}