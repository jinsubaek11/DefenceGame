#include "BTTask_FindTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GamePlayer.h"
#include "EnemyAIController.h"
#include "Tower.h"
#include "PooledEnemy.h"
#include "EngineUtils.h"
#include "kismet/GameplayStatics.h"


UBTTask_FindTarget::UBTTask_FindTarget()
{
	NodeName = TEXT("Find Target");
}

EBTNodeResult::Type UBTTask_FindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	//AGamePlayer* player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//ATower* tower = nullptr;
	//for (TActorIterator<ATower> it(GetWorld()); it; ++it)
	//{
	//	if (it)
	//	{
	//		tower = *it;
	//	}
	//}

	//if (tower)
	//{
	//	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), tower->GetActorLocation());
	//}

	//if (player && enemy)
	//{
	//	FVector playerLocation = player->GetActorLocation();
	//	FVector enemyLocation = enemy->GetActorLocation();

	//	float distance = FVector::Distance(playerLocation, enemyLocation);

	//	if (distance <= 300)
	//	{
	//		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLocation);
	//	}
	//}

	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}