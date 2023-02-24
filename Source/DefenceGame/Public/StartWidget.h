#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"


UCLASS()
class DEFENCEGAME_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void Start();
	UFUNCTION()
	void Exit();

public:
	UPROPERTY(EditDefaultsOnly, meta = (bindwidget))
	class UButton* StartBtn;
	UPROPERTY(EditDefaultsOnly, meta = (bindwidget))
	class UButton* ExitBtn;
};
