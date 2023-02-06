#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_BossWait.generated.h"


UCLASS()
class DEFENCEGAME_API UBTService_BossWait : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_BossWait();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
