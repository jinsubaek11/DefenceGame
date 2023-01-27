#include "BTTask_Attack.h"
#include "GamePlayer.h"
#include "PooledEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"


UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGamePlayer* player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (IsValid(player) && IsValid(enemy))
	{
		enemy->Attack(player);
		enemy->SetAnimationState(EEnemyAnimationState::ATTACK);

		return EBTNodeResult::Succeeded;
	}

	enemy->SetAnimationState(EEnemyAnimationState::WALK);
	return EBTNodeResult::Failed;

	//FVector playerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation"));
	//FVector itemLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("ItemLocation"));
	//FVector towerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("TowerLocation"));
	//
	//if (playerLocation)
	//{

	//}
}