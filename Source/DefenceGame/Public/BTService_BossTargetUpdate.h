#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_BossTargetUpdate.generated.h"


UCLASS()
class DEFENCEGAME_API UBTService_BossTargetUpdate : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_BossTargetUpdate();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float chaseRange = 700;
	float detectRange = 1500.f;
};
