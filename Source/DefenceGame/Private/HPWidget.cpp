// Fill out your copyright notice in the Description page of Project Settings.


#include "HPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UHPWidget::ShowHealthBar(float hp)
{
	//ü�¹� �����ִ� �Լ�
	//towerHPBar->SetFillColorAndOpacity(FLinearColor(255, 0, 0, 255));
	UE_LOG(LogTemp, Warning, TEXT("ShowHealthBar hp of tower is decreasing %f"), hp)
	towerHPBar->SetPercent(hp / towerMaxHP);

	towerHPNum->SetText(FText::AsNumber(hp));
	
}

void UHPWidget::OnTakeDamage(int32 attackTowerScore)
{
	//���ݴ��� �� ���� hp ���
	towerCurrentHP -= attackTowerScore;
	UE_LOG(LogTemp, Warning, TEXT("SetTowerHP hp of tower is decreasing %f"), towerCurrentHP)

		if (towerCurrentHP)
		{
			//���� ü�� ���� �����ֱ�
			ShowHealthBar(towerCurrentHP);

		}
}

void UHPWidget::SetTowerHP(float hp)
{
	ShowHealthBar(hp);

}
