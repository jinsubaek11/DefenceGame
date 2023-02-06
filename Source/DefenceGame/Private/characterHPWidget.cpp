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

	//ü�¹� �����ִ� �Լ�	
	UE_LOG(LogTemp, Warning, TEXT("ShowHealthBar hp of char is decreasing %f"), hp)
	charHPBar->SetPercent(hp / charMaxHP);

	charHPNum->SetText(FText::AsNumber(hp));

}

void UcharacterHPWidget::OnTakeDamage(int32 attackTowerScore)
{
	//���ݴ��� �� ���� hp ���
	charCurrentHP -= attackTowerScore;
	UE_LOG(LogTemp, Warning, TEXT("SetTowerHP hp of char is decreasing %f"), charCurrentHP)

		if (charCurrentHP)
		{
			//���� ü�� ���� �����ֱ�
			ShowHPBar(charCurrentHP);
		}
}

void UcharacterHPWidget::SetcharacterHP(float hp)
{
	ShowHPBar(hp);

}

