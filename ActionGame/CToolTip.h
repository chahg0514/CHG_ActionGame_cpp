// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemData.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CToolTip.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UCToolTip : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(VisibleAnywhere, Category = "ToolTip", meta = (BindWidget))
		class UTextBlock* NameText;
	UPROPERTY(VisibleAnywhere, Category = "ToolTip", meta = (BindWidget))
		class UTextBlock* PriceText;
	UPROPERTY(VisibleAnywhere, Category = "ToolTip", meta = (BindWidget))
		class UTextBlock* AmountText;
	UPROPERTY(VisibleAnywhere, Category = "ToolTip", meta = (BindWidget))
		class UTextBlock* DescriptionText;
	UPROPERTY(VisibleAnywhere, Category = "ToolTip", meta = (BindWidget))
		class UImage* IconImage;
private:
	FSlotData SlotData;
public:
	void SetSlotData(FSlotData InSlotData);

};
