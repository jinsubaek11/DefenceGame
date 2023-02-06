// Fill out your copyright notice in the Description page of Project Settings.


#include "characterHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UcharacterHPWidget::ShowHPBar(float hp)
{
	if (nullptr == charHPBar)
	{
		return;
	}

	//체력바 보여주는 함수	
	UE_LOG(LogTemp, Warning, TEXT("ShowHealthBar hp of char is decreasing %f"), hp)
	charHPBar->SetPercent(hp / charMaxHP);

	charHPNum->SetText(FText::AsNumber(hp));

}

void UcharacterHPWidget::OnTakeDamage(int32 attackTowerScore)
{
	//공격당한 후 남은 hp 계산
	charCurrentHP -= attackTowerScore;
	UE_LOG(LogTemp, Warning, TEXT("SetTowerHP hp of char is decreasing %f"), charCurrentHP)

		if (charCurrentHP)
		{
			//남은 체력 숫자 보여주기
			ShowHPBar(charCurrentHP);
		}
}

void UcharacterHPWidget::SetcharacterHP(float hp)
{
	ShowHPBar(hp);

}

