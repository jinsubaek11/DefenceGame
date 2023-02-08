#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"


UCLASS()
class DEFENCEGAME_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void Restart();
	UFUNCTION()
	void Exit();

public:
	UPROPERTY(EditDefaultsOnly, meta = (bindwidget))
	class UButton* RestartBtn;
	UPROPERTY(EditDefaultsOnly, meta = (bindwidget))
	class UButton* ExitBtn;

};
