#include "BTTask_MoveToTarget.h"
#include "PooledEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tower.h"
#include "GamePlayer.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"


UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	NodeName = TEXT("MoveToTarget");
	AcceptableRadius = 400;
	ObservedBlackboardValueTolerance = 4.75;
	bObserveBlackboardValue = true;
	//bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	
	if (!enemy || !target) return EBTNodeResult::Failed;

	enemy->SetAnimationState(EEnemyAnimationState::WALK);
	distance = FVector::Distance(enemy->GetActorLocation(), target->GetActorLocation());
	
	//AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	//if (!target) return EBTNodeResult::Failed;

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey())->GetName());
	
	//UE_LOG(LogTemp, Warning, TEXT("ExcuteTask"));

	//if (distance <= 0)
	//{
	//	distance = 987654321;
	//}

	//if (distance <= AcceptableRadius)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("%f"), distance);

	//	enemy->SetAnimationState(EEnemyAnimationState::ATTACK);
	//	return EBTNodeResult::Succeeded;
	
	//}

	return EBTNodeResult::InProgress;



	//return EBTNodeResult::Succeeded;

	//APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	//if (enemy)
	//{
	//	enemy->SetAnimationState(EEnemyAnimationState::WALK);
	//	//AAIController* aiController = Cast<AAIController>(enemy->GetController());
	//
	//	if (OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()).Length() <= AcceptableRadius)
	//	{
	//		return EBTNodeResult::Succeeded;

	//	}
	//	
	//	OwnerComp.GetAIOwner()->MoveToLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()), -1, false);
	//	//FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);

	//	//return EBTNodeResult::EBTNodeResult::InProgress;
	//	return EBTNodeResult::InProgress;
	//}

	//return EBTNodeResult::Failed;
}

//void UBTTask_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//
//	UE_LOG(LogTemp, Warning, TEXT("TickTask"));
//
//	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
//	//enemy->SetAnimationState(EEnemyAnimationState::WALK);
//	
//	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
//	if (!enemy || !target) return;
//
//	distance = FVector::Distance(enemy->GetActorLocation(), target->GetActorLocation());
//
//
//	//
//	//APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
//	//if (FVector::Distance(enemy->GetActorLocation(), OwnerComp.GetAIOwner()->GetTargetLocation()) < AcceptableRadius)
//	//{
//	//	enemy->SetAnimationState(EEnemyAnimationState::WALK);
//	//}
//}

void UBTTask_MoveToTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy)
	{
		enemy->SetAnimationState(EEnemyAnimationState::ATTACK);
	}
}
