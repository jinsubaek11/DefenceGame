#include "VictoryWidget.h"
#include "kismet/KismetSystemLibrary.h"
#include "kismet/GameplayStatics.h"
#include "components/Button.h"


void UVictoryWidget::NativeConstruct()
{
	RestartBtn->OnClicked.AddDynamic(this, &UVictoryWidget::Restart);
	ExitBtn->OnClicked.AddDynamic(this, &UVictoryWidget::Exit);
}

void UVictoryWidget::Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("AsianLevel_2"));
	RemoveFromParent();
}

void UVictoryWidget::Exit()
{
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
}
