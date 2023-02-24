#include "StartGameMode.h"
#include "StartWidget.h"


AStartGameMode::AStartGameMode()
{

}	

void AStartGameMode::BeginPlay()
{
	startUIWidget = Cast<UStartWidget>(CreateWidget(GetWorld(), startUI));

	if (startUIWidget)
	{
		startUIWidget->AddToViewport();
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}

}

