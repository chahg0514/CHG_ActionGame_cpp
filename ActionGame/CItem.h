// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemData.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CItem.generated.h"


UCLASS()
class ACTIONGAME_API ACItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACItem();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	//액터가 레벨에 배치되었거나 생성되었다면 호출되는 함수
private:
	UPROPERTY(EditAnywhere, Category = "ItemData")
		class UDataTable* ItemDataTable;
	UPROPERTY(EditAnywhere, Category = "ItemData")
		struct FDataTableRowHandle ItemRowHandle; //이게 행에 따라 다른것도 한번에 변화시켜주는 클래스인가보네
	UPROPERTY(EditAnywhere, Category = "ItemData")
		struct FItemData ItemData;
	UPROPERTY(EditAnywhere, Category = "ItemData")
		class USkeletalMeshComponent* ItemMesh;
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
private:
	UPROPERTY(VisibleAnywhere, Category = "ItemData")
		class USphereComponent* SphereCollision;
public:
	void SetItemRowName(FName InItemName);
private:
	class whattheFuck* hello;
};
