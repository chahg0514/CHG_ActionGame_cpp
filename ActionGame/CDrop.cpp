// Fill out your copyright notice in the Description page of Project Settings.


#include "CDrop.h"
#include "CSlot.h"
#include "CDragDropOperation.h"

bool UCDrop::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UCDragDropOperation* DragDrop = Cast<UCDragDropOperation>(InOperation);
	if (DragDrop->WidgetReference != this)
	{
		UCSlot* slot = Cast<UCSlot>(DragDrop->WidgetReference);
		slot->SpawnItem();
	}
	DragDrop->WidgetReference->SetVisibility(ESlateVisibility::Visible);
	return false;
}