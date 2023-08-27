// Fill out your copyright notice in the Description page of Project Settings.


#include "CHealthWidget.h"
#include "CPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UCHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->HealthEvent.BindUObject(this, &UCHealthWidget::SetHealth); //��������Ʈ�� �Լ� ����
}

void UCHealthWidget::SetHealth()
{
	HealthBar->SetPercent(Player->GetCurrentHp() / Player->GetMaxHp());

	FNumberFormattingOptions Opts; //�Ҽ��� ���� �ڸ����� ������ �����ϴ� ����ü

	Opts.SetMaximumFractionalDigits(0); //�Ҽ����� ǥ������ ����

	CurrentHealthText->SetText(FText::AsNumber(Player->GetCurrentHp(), &Opts));
	MaxHealthText->SetText(FText::AsNumber(Player->GetMaxHp(), &Opts));
}
