// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemData.h"
#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "CDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UCDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DragDrop")
		class UUserWidget* WidgetReference; //¿øº» À§Á¬
public:
	FSlotData SlotData;
	
};
