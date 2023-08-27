// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "ItemData.generated.h" //이거 복습

UENUM(BlueprintType, meta = (ToolTip = "ItemType"))
enum class EItemType : uint8
{
	None UMETA(DisplayName = "None"),
	Equipment UMETA(DisplayName = "Equipment"), //장비
	Countable UMETA(DisplayName = "Countable"), //소모
	Etc UMETA(DisplayName = "Etc") //기타
};

//Atomic : 직렬화(데이터를일렬로 정렬시켜줌)
USTRUCT(Atomic, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		FString ItemName = FString(TEXT(""));
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		EItemType ItemType = EItemType::None;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		int32 Price = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		FString Description = FString(TEXT(""));
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		class USkeletalMesh* ItemMesh = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemData")
		class UTexture2D* Icon = nullptr;
	bool operator==(const FItemData& InItemData) const
	{
		bool isName = (ItemName == InItemData.ItemName);
		bool isType = (ItemType == InItemData.ItemType);
		bool isPrice = (Price == InItemData.Price);
		bool isMesh = (ItemMesh == InItemData.ItemMesh);
		bool isIcon = (Icon == InItemData.Icon);
		return (isName && isType && isPrice && isMesh && isIcon);
	}
	
};

USTRUCT(Atomic, BlueprintType)
struct FSlotData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		FItemData ItemData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		int32 Amount = 0; //개수
};