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
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* tower = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Tower")));
	AGamePlayer* player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	AItem* item = nullptr;

	if (!tower || !player || !enemy) return;

	//enemy->SetAnimationState(EEnemyAnimationState::WALK);

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
			//UE_LOG(LogTemp, Warning, TEXT("Set Item"));

			//if (!OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Item"))) return;

			//OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Tower"));
			OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Player"));
			OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("ItemLocation"), item->GetActorLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Item"), item);
			//enemy->SetAnimationState(EEnemyAnimationState::WALK);
		}
		return;

	}
	//UE_LOG(LogTemp, Warning, TEXT("Item Clear"));

	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("ItemLocation"));
	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Item"));

	if (!OwnerComp.GetAIOwner()->LineOfSightTo(player) || 
		playerToEnemyDistance >= 700)
	{	
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Player"));
		//OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Tower"));
	}

	if (OwnerComp.GetAIOwner()->LineOfSightTo(player) && 
		playerToEnemyDistance < 700)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Set Player"));

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), player->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), player);

	}
}