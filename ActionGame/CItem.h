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
	//���Ͱ� ������ ��ġ�Ǿ��ų� �����Ǿ��ٸ� ȣ��Ǵ� �Լ�
private:
	UPROPERTY(EditAnywhere, Category = "ItemData")
		class UDataTable* ItemDataTable;
	UPROPERTY(EditAnywhere, Category = "ItemData")
		struct FDataTableRowHandle ItemRowHandle; //�̰� �࿡ ���� �ٸ��͵� �ѹ��� ��ȭ�����ִ� Ŭ�����ΰ�����
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
