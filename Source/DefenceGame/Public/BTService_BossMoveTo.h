#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_BossMoveTo.generated.h"


UCLASS()
class DEFENCEGAME_API UBTService_BossMoveTo : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_BossMoveTo();

public:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
