// Fill out your copyright notice in the Description page of Project Settings.


#include "CToolTip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCToolTip::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCToolTip::SetSlotData(FSlotData InSlotData)
{
	SlotData = InSlotData;
	NameText->SetText(FText::FromString(SlotData.ItemData.ItemName));
	PriceText->SetText(FText::AsNumber(SlotData.ItemData.Price));
	AmountText->SetText(FText::AsNumber(SlotData.Amount));
	DescriptionText->SetText(FText::FromString(SlotData.ItemData.Description));
	IconImage->SetBrushFromTexture(SlotData.ItemData.Icon);
	IconImage->SetBrushSize(FVector2D(70));


}
