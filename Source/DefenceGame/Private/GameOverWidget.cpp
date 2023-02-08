#include "GameOverWidget.h"
#include "kismet/KismetSystemLibrary.h"
#include "kismet/GameplayStatics.h"
#include "components/Button.h"


void UGameOverWidget::NativeConstruct()
{
	RestartBtn->OnClicked.AddDynamic(this, &UGameOverWidget::Restart);
	ExitBtn->OnClicked.AddDynamic(this, &UGameOverWidget::Exit);
}

void UGameOverWidget::Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("AsianLevel_2"));
	RemoveFromParent();
}

void UGameOverWidget::Exit()
{
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
}
