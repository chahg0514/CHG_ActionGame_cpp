// Fill out your copyright notice in the Description page of Project Settings.


#include "CInventoryComponent_Real.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "CInventory.h"


// Sets default values for this component's properties
UCInventoryComponent_Real::UCInventoryComponent_Real()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryAsset(TEXT("WidgetBlueprint'/Game/Blueprint/Player/Widget/WB_Inventory.WB_Inventory_C'"));
	if (InventoryAsset.Succeeded())
	{
		InventoryClass = InventoryAsset.Class;
	}
	// ...
}


// Called when the game starts
void UCInventoryComponent_Real::BeginPlay()
{
	Super::BeginPlay();
	if (InventoryClass != nullptr)
	{
		Inventory = Cast<UCInventory>(CreateWidget<UUserWidget>(GetWorld(), InventoryClass)); //�κ��丮 ����
		if (Inventory != nullptr)
		{
			Inventory->AddToViewport(); //����Ʈ �߰�
			Inventory->SetVisibility(ESlateVisibility::Hidden);// ������ ������
		}
	}

	// ...
	
}


// Called every frame
void UCInventoryComponent_Real::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCInventoryComponent_Real::AddItem(FItemData InItem)
{
	int index = FindStack(InItem);
	Inventory->AddSlotToItem(InItem);
	if (index == -1) //FindStack ���� ������ -1��ȯ���ٰǰ���
	{
		FSlotData NewSlot;
		NewSlot.ItemData = InItem;
		NewSlot.Amount = 1;
		SlotDatas.Add(NewSlot);
	}
	else
	{
		SlotDatas[index].Amount++;
	}
}

void UCInventoryComponent_Real::ShowInventory()
{
	if (!IsValid(Inventory)) return;
	if (!isInventory) //�κ��丮�� ���ٸ�
	{
		Inventory->SetVisibility(ESlateVisibility::Visible);
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetShowMouseCursor(true);
		FInputModeGameAndUI InputMode; //��Ʈ�ѷ��� �Է��� UI�� ������ �����ϴ� �Լ��� ���� ����
		InputMode.SetWidgetToFocus(Inventory->TakeWidget()); //�Է¿� ����� ���� ����
		PlayerController->SetInputMode(FInputModeGameAndUI(InputMode)); //�Է¸�� ����
		isInventory = true;
	}
	else //�κ��丮�� �ִٸ�
	{
		Inventory->SetVisibility(ESlateVisibility::Hidden);

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly()); 
		isInventory = false;




	}
}

int UCInventoryComponent_Real::FindStack(FItemData ItemData)
{
	
	for (int32 i = 0; i < SlotDatas.Num(); i++)
	{
		if (SlotDatas[i].ItemData == ItemData)
		{
			return i;
		}
	}
	return -1;
}

TArray<FSlotData> UCInventoryComponent_Real::GetSlotDatas()
{

	return SlotDatas;
}

