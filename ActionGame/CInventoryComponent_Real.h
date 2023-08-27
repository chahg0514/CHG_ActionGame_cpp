// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemData.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInventoryComponent_Real.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UCInventoryComponent_Real : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCInventoryComponent_Real();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void AddItem(struct FItemData InItem);
	void ShowInventory();
	int FindStack(struct FItemData ItemData);
private:
	UPROPERTY(VisibleAnywhere)
		TArray<FSlotData> SlotDatas; //구조체 전방선언 지워줌 이거 지워주면 저 struct가 들어있는 헤더파일 include 해줘야됨
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true))
		TSubclassOf<class UUserWidget> InventoryClass;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true))
		class UCInventory* Inventory;
private:
	bool isInventory = false;
public:
	UFUNCTION()
		TArray<FSlotData> GetSlotDatas();
};
