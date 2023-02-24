#include "StartWidget.h"
#include "kismet/KismetSystemLibrary.h"
#include "kismet/GameplayStatics.h"
#include "components/Button.h"


void UStartWidget::NativeConstruct()
{
	StartBtn->OnClicked.AddDynamic(this, &UStartWidget::Start);
	ExitBtn->OnClicked.AddDynamic(this, &UStartWidget::Exit);
}

void UStartWidget::Start()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("AsianLevel_2"));
	
	RemoveFromParent();
}

void UStartWidget::Exit()
{
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
}
