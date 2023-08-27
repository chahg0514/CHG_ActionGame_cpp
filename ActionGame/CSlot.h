// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ItemData.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSlot.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UCSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UCSlot(const FObjectInitializer& ObjectInitializer);
	//위젯은 생성자에 매개변수를 넣어야 함.

protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Slot", meta = (BindWidget))
		class UImage* Icon;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slot")//이렇게 두개도 설정 가능하구나
		FSlotData SlotData; //이거 변수이름에 빨간줄 cpp에서 include ItemData 해줬더니 해결됨
public:
	void SetSlotData(FSlotData InSlotData);
private:
	UPROPERTY(VisibleAnywhere, Category = "Tooltip")
		TSubclassOf<UUserWidget> TooltipClass;
	UPROPERTY(VisibleAnywhere, Category = "Tooltip")
		class UCToolTip* Tooltip;  
	UPROPERTY(VisibleAnywhere, Category = "Tooltip", meta = (BindWidget))
		class UScaleBox* SlotScaleBox;

	//여기는 또 include CTooltip.h안해도 되네.. 변수생성은 되는데 이제 cpp에서도 include 를 안하면 cpp에서 자세한 접근을 못하는건가

private:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//위젯 내부에서 마우스 클릭시 호출되는 함수
	//FGeometry : 위젯의 위치, 크기, 절대위치를 나타냄
	//FPointerEvent: 마우스 또는 터치에 따른 이벤트 핸들러
	//FEventReply: 사용자가 이벤트를 처리하고 기본 UI계층에 정보를 반환하며 반환할 정보를 담은 구조체

private:
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override; //드래그 시작 시 호출되는 함수

	//virtual void NativeOnDragCancelled() override;
	//virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation*& InOperation) override; //드래그 시작 시 호출되는 함수
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
public:
	void SpawnItem();
};
