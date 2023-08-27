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
		Inventory = Cast<UCInventory>(CreateWidget<UUserWidget>(GetWorld(), InventoryClass)); //인벤토리 생성
		if (Inventory != nullptr)
		{
			Inventory->AddToViewport(); //뷰포트 추가
			Inventory->SetVisibility(ESlateVisibility::Hidden);// 위젯을 숨겨줌
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
	if (index == -1) //FindStack 에서 없으면 -1반환해줄건가봐
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
	if (!isInventory) //인벤토리가 없다면
	{
		Inventory->SetVisibility(ESlateVisibility::Visible);
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetShowMouseCursor(true);
		FInputModeGameAndUI InputMode; //컨트롤러의 입력을 UI도 받을지 설정하는 함수에 넣을 변수
		InputMode.SetWidgetToFocus(Inventory->TakeWidget()); //입력에 사용할 위젯 지정
		PlayerController->SetInputMode(FInputModeGameAndUI(InputMode)); //입력모드 지정
		isInventory = true;
	}
	else //인벤토리가 있다면
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

