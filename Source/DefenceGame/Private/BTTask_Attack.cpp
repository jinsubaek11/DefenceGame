#include "BTTask_Attack.h"
#include "GamePlayer.h"
#include "PooledEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Item.h"
#include "Tower.h"


UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//ATower* tower = nullptr;
	//for (TActorIterator<ATower> it(GetWorld()); it; ++it)
	//{
	//	if (it)
	//	{
	//		tower = *it;
	//	}
	//}

	//AActor* target = nullptr;
	//AGamePlayer* player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	//AItem* item = nullptr;
	//float itemToEnemyDistance = 98765421.f;

	//for (TActorIterator<AItem> itemIter(GetWorld()); itemIter; ++itemIter)
	//{
	//	float distance = enemy->GetDistanceTo(*itemIter);
	//	if (itemToEnemyDistance > distance)
	//	{
	//		itemToEnemyDistance = distance;
	//		item = *itemIter;
	//	}
	//}

	//if (OwnerComp.GetBlackboardComponent()->IsVectorValueSet(TEXT("TowerLocation")))
	//{
	//	if (IsValid(tower))
	//	{
	//		target = tower;
	//		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Tower"), tower);
	//	}
	//}

	//if (OwnerComp.GetBlackboardComponent()->IsVectorValueSet(TEXT("ItemLocation")))
	//{
	//	if (IsValid(item))
	//	{
	//		target = item;
	//		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Item"), item);
	//	}
	//}

	//if (OwnerComp.GetBlackboardComponent()->IsVectorValueSet(TEXT("PlayerLocation")))
	//{
	//	if (IsValid(player))
	//	{
	//		target = player;
	//		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), player);
	//	}
	//}
	
	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (target)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *target->GetName());
		enemy->Attack(target);
		//UE_LOG(LogTemp, Warning, TEXT("Attack"));
		enemy->SetAnimationState(EEnemyAnimationState::ATTACK);

		return EBTNodeResult::Succeeded;
	}

	enemy->SetAnimationState(EEnemyAnimationState::WALK);
	return EBTNodeResult::Failed;
}

