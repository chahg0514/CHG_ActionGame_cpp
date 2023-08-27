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


UCSlot::UCSlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) //������ �����ڿ� �ʱ�ȭ����Ʈ�� �ٿ��� ��
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
	//������ ���� ���� ����
	if (SlotData.ItemData.Icon) //�� �̰� �ű��� �̷����ϸ� �������� �ִ��� Ȯ�� �����ϴٰ�? ���ó�� �ζ����� ������ذ͵��ƴϰ�
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

		SlotScaleBox->SetToolTip(Tooltip); //�̰� SetToolTip �ѹ��� �������ָ� ���콺������ �� �ϴ°Ű���
		Tooltip->SetSlotData(SlotData);
	}
	else
	{
		Icon->SetBrushFromTexture(nullptr);
		SlotScaleBox->SetToolTip(nullptr); //������ ������
	}
}

FReply UCSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LeftDown"));
		//���ʸ��콺Ŭ���� �巡�״ϱ� ����ٰ� �߰�����
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		//DetectedDragIfPreseed: ��ư�� �������·� �巡�� �ߴ��� �˻��ϴ� �Լ�

	}
	if(InMouseEvent.IsMouseButtonDown(FKey("RightMouseButton")))
	{
		if (SlotData.ItemData.ItemType == EItemType::Countable)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("RightDown"));

			SlotData.Amount--; //���� ����
			Tooltip->SetSlotData(SlotData); //���� �ֽ�ȭ
			if (SlotData.Amount <= 0)
			{
				FSlotData TempData;
				SlotData = TempData;
				SetSlotData(SlotData);
				Icon->SetBrushFromTexture(nullptr);
				SlotScaleBox->SetToolTip(nullptr); //��������ü�� ������ �� �ڸ��� ����شٴ°ǰ�
			}
		}

	}
	return reply.NativeReply;
	//���� ���콺 ��ư Ŭ��
}

//�̰� �巡�����ΰŰ� �巡�� ���� ���� ���� ������ָ��
void UCSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (SlotData.ItemData.Icon == nullptr) //������ ����ִٸ����� ���ϰ� �� �������� �ֳľ��ķ� �ϴ°���
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

	ACItem* item = GetWorld()->SpawnActorDeferred<ACItem>(ACItem::StaticClass(), transform); //���͸� �����ϱ� �ϴµ� ���忡 �߰����� �ʰ� �����θ� ������ ����
	item->SetItemRowName(FName(*SlotData.ItemData.ItemName));
	item->FinishSpawning(transform); //�̰� ���忡 �߰������ִ°���
	FSlotData tempData;
	SlotData = tempData;
	SetSlotData(tempData);
}

//void UCSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation*& InOperation)
//{
//	
//}
