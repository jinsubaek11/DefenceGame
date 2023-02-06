#include "BTService_FindTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "Tower.h"
#include "GamePlayer.h"
#include "EngineUtils.h"
#include "kismet/GameplayStatics.h"


UBTService_FindTarget::UBTService_FindTarget()
{

}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ATower* tower = nullptr;
	for (TActorIterator<ATower> it(GetWorld()); it; ++it)
	{
		if (it)
		{
			tower = *it;
		}
	}

	if (tower)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TowerLocation"), tower->GetActorLocation() + FVector(150, 0, 0));
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Tower"), tower);

	}
}