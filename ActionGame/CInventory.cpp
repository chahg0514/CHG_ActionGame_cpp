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

		//GetWidgetFromName : �̸����� ������ ������

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
		//ȹ���� �������� �ְ� ���������̶��
		if (Item->SlotData.ItemData == InItemdata && InItemdata.ItemType == EItemType::Equipment)
		{
			continue;
		}
		else if (Item->SlotData.Amount == 0) //������ ����ִٸ�
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
