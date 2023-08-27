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
	Player->HealthEvent.BindUObject(this, &UCHealthWidget::SetHealth); //델리게이트에 함수 연결
}

void UCHealthWidget::SetHealth()
{
	HealthBar->SetPercent(Player->GetCurrentHp() / Player->GetMaxHp());

	FNumberFormattingOptions Opts; //소수점 같은 자릿수의 포멧을 지정하는 구조체

	Opts.SetMaximumFractionalDigits(0); //소수점을 표시하지 않음

	CurrentHealthText->SetText(FText::AsNumber(Player->GetCurrentHp(), &Opts));
	MaxHealthText->SetText(FText::AsNumber(Player->GetMaxHp(), &Opts));
}
