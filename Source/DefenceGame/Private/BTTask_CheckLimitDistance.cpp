#include "BTTask_CheckLimitDistance.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PooledEnemy.h"


UBTTask_CheckLimitDistance::UBTTask_CheckLimitDistance()
{
	NodeName = TEXT("Check Limit Distance");
}

EBTNodeResult::Type UBTTask_CheckLimitDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	FVector targetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	FVector enemyLocation;

	if (enemy)
	{
		enemyLocation = enemy->GetActorLocation();

		float distance = FVector::Distance(enemyLocation, targetLocation);
		if (distance <= 500.f)
		{
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}