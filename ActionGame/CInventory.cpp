// Fill out your copyright notice in the Description page of Project Settings.


#include "CInventory.h"
#include "CSlot.h"

void UCInventory::NativeConstruct()
{
	Super::NativeConstruct();
	for (int32 i = 0; i < 30; i++)
	{
		FName SlotName = FName(FString::Printf(TEXT("WB_Slot_%d"), i));
		UCSlot* MySlot = Cast<UCSlot>(GetWidgetFromName(SlotName));

		//GetWidgetFromName : 이름으로 위젯을 가져옴

		if (MySlot != nullptr)
		{
			Slots.Add(MySlot);
		}
	}
}

void UCInventory::AddSlotToItem(FItemData InItemdata)
{
	for (UCSlot* Item : Slots)
	{
		//획득한 아이템이 있고 장비아이템이라면
		if (Item->SlotData.ItemData == InItemdata && InItemdata.ItemType == EItemType::Equipment)
		{
			continue;
		}
		else if (Item->SlotData.Amount == 0) //슬롯이 비어있다면
		{
			Item->SlotData.ItemData = InItemdata;
			Item->SlotData.Amount++;
			Item->SetSlotData(Item->SlotData);
			return;
		}
		else if (Item->SlotData.ItemData == InItemdata)
		{
			Item->SlotData.Amount++;
			Item->SetSlotData(Item->SlotData);
			return;

		}
	}
}
