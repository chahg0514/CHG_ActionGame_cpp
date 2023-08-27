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
	//������ �����ڿ� �Ű������� �־�� ��.

protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Slot", meta = (BindWidget))
		class UImage* Icon;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slot")//�̷��� �ΰ��� ���� �����ϱ���
		FSlotData SlotData; //�̰� �����̸��� ������ cpp���� include ItemData ������� �ذ��
public:
	void SetSlotData(FSlotData InSlotData);
private:
	UPROPERTY(VisibleAnywhere, Category = "Tooltip")
		TSubclassOf<UUserWidget> TooltipClass;
	UPROPERTY(VisibleAnywhere, Category = "Tooltip")
		class UCToolTip* Tooltip;  
	UPROPERTY(VisibleAnywhere, Category = "Tooltip", meta = (BindWidget))
		class UScaleBox* SlotScaleBox;

	//����� �� include CTooltip.h���ص� �ǳ�.. ���������� �Ǵµ� ���� cpp������ include �� ���ϸ� cpp���� �ڼ��� ������ ���ϴ°ǰ�

private:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//���� ���ο��� ���콺 Ŭ���� ȣ��Ǵ� �Լ�
	//FGeometry : ������ ��ġ, ũ��, ������ġ�� ��Ÿ��
	//FPointerEvent: ���콺 �Ǵ� ��ġ�� ���� �̺�Ʈ �ڵ鷯
	//FEventReply: ����ڰ� �̺�Ʈ�� ó���ϰ� �⺻ UI������ ������ ��ȯ�ϸ� ��ȯ�� ������ ���� ����ü

private:
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override; //�巡�� ���� �� ȣ��Ǵ� �Լ�

	//virtual void NativeOnDragCancelled() override;
	//virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation*& InOperation) override; //�巡�� ���� �� ȣ��Ǵ� �Լ�
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
public:
	void SpawnItem();
};
