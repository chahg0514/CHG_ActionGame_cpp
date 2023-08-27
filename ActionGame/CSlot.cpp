// Fill out your copyright notice in the Description page of Project Settings.

#include "CSlot.h"

#include "CToolTip.h"
#include "Components/Image.h"
#include "Components/ScaleBox.h"
#include "CItem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

#include "CDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "CItem.h"
#include "CPlayer.h"
#include "Kismet/GameplayStatics.h"


UCSlot::UCSlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) //위젯은 생성자에 초기화리스트를 붙여야 함
{
	Super::NativeOnInitialized();
	ConstructorHelpers::FClassFinder<UUserWidget> TooltipAsset(TEXT("WidgetBlueprint'/Game/Blueprint/Player/Widget/WB_ToolTip.WB_ToolTip_C'"));
	if (TooltipAsset.Succeeded())
	{
		TooltipClass = TooltipAsset.Class;
	}
}

void UCSlot::NativeConstruct()
{
	Super::NativeConstruct();
	//아이콘 사진 설정 시작
	if (SlotData.ItemData.Icon) //난 이게 신기함 이렇게하면 아이콘이 있는지 확인 가능하다고? 평소처럼 인라인을 만들어준것도아니고
	{
		Icon->SetBrushFromTexture(SlotData.ItemData.Icon);
		Icon->SetBrushSize(FVector2D(70, 70));
	}
	else
	{
		Icon->SetBrushFromTexture(nullptr);
	}
	Tooltip = Cast<UCToolTip>(CreateWidget(GetWorld(), TooltipClass));
	
	//Tooltip->SetSlotData(SlotData);
}

void UCSlot::SetSlotData(FSlotData InSlotData)
{
	SlotData = InSlotData;
	if (SlotData.ItemData.Icon)
	{
		Icon->SetBrushFromTexture(SlotData.ItemData.Icon);
		Icon->SetBrushSize(FVector2D(70, 70));

		SlotScaleBox->SetToolTip(Tooltip); //이게 SetToolTip 한번만 실행해주면 마우스감지도 다 하는거같음
		Tooltip->SetSlotData(SlotData);
	}
	else
	{
		Icon->SetBrushFromTexture(nullptr);
		SlotScaleBox->SetToolTip(nullptr); //툴팁을 없애줌
	}
}

FReply UCSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LeftDown"));
		//왼쪽마우스클릭이 드래그니까 여기다가 추가해줌
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		//DetectedDragIfPreseed: 버튼이 눌린상태로 드래그 했는지 검사하는 함수

	}
	if(InMouseEvent.IsMouseButtonDown(FKey("RightMouseButton")))
	{
		if (SlotData.ItemData.ItemType == EItemType::Countable)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("RightDown"));

			SlotData.Amount--; //갯수 차감
			Tooltip->SetSlotData(SlotData); //슬롯 최신화
			if (SlotData.Amount <= 0)
			{
				FSlotData TempData;
				SlotData = TempData;
				SetSlotData(SlotData);
				Icon->SetBrushFromTexture(nullptr);
				SlotScaleBox->SetToolTip(nullptr); //데이터자체를 없애줌 그 자리를 비워준다는건가
			}
		}

	}
	return reply.NativeReply;
	//왼쪽 마우스 버튼 클릭
}

//이건 드래그중인거고 드래그 놨을 때도 따로 만들어주면됨
void UCSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (SlotData.ItemData.Icon == nullptr) //슬롯이 비어있다면으로 안하고 왜 아이콘이 있냐없냐로 하는거지
	{
		return;
	}
	UCDragDropOperation* DragDrop = NewObject<UCDragDropOperation>();
	SetVisibility(ESlateVisibility::HitTestInvisible);
	DragDrop->SlotData = SlotData;
	DragDrop->WidgetReference = this;
	DragDrop->DefaultDragVisual = this;
	DragDrop->Pivot = EDragPivot::MouseDown;
	OutOperation = DragDrop;
}

void UCSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	SetVisibility(ESlateVisibility::Visible);
}

bool UCSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UCDragDropOperation* DragDrop = Cast<UCDragDropOperation>(InOperation);

	if (DragDrop->WidgetReference != this) 
	{
		SetSlotData(DragDrop->SlotData);
		UCSlot* slot = Cast<UCSlot>(DragDrop->WidgetReference);
		FSlotData tempData;
		if (slot != nullptr)
		{
			slot->SetSlotData(tempData);
		}
	}
	DragDrop->WidgetReference->SetVisibility(ESlateVisibility::Visible);
	return false;
}

void UCSlot::SpawnItem()
{
	ACharacter* MyPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FTransform transform = MyPlayer->GetActorTransform();
	transform.SetLocation(MyPlayer->GetActorLocation() + (MyPlayer->GetActorForwardVector() * 200));

	ACItem* item = GetWorld()->SpawnActorDeferred<ACItem>(ACItem::StaticClass(), transform); //액터를 생성하긴 하는데 월드에 추가하진 않고 변수로만 가지고 있음
	item->SetItemRowName(FName(*SlotData.ItemData.ItemName));
	item->FinishSpawning(transform); //이건 월드에 추가시켜주는거임
	FSlotData tempData;
	SlotData = tempData;
	SetSlotData(tempData);
}

//void UCSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation*& InOperation)
//{
//	
//}
