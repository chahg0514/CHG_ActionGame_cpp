// Fill out your copyright notice in the Description page of Project Settings.


#include "CItem.h"
#include "Components/SphereComponent.h"
#include "CPlayer.h"
#include "CInventoryComponent_Real.h"

// Sets default values
ACItem::ACItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UDataTable> DataAsset(TEXT("DataTable'/Game/Blueprint/Player/DataTable/DT_ItemData.DT_ItemData'"));
	if (DataAsset.Succeeded())
	{
		ItemDataTable = DataAsset.Object;
		ItemRowHandle.DataTable = DataAsset.Object;
		ItemRowHandle.RowName = TEXT("Bow"); //기본아이템, RowHandle은 특정 행
	}
	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetCollisionProfileName(FName(TEXT("Item")));
	ItemMesh->SetRelativeScale3D(FVector(0.5f));
	RootComponent = ItemMesh;
	Tags.Add(FName(TEXT("Item")));

	ItemMesh->SetSimulatePhysics(true); //물리 적용, 아래로 떨어짐
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->AttachToComponent(ItemMesh, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned

void ACItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ItemData = *ItemDataTable->FindRow<FItemData>(ItemRowHandle.RowName, TEXT("")); //행을 찾음
	
	if (&ItemData != nullptr && ItemMesh != nullptr)
	{
		ItemMesh->SetSkeletalMesh(ItemData.ItemMesh);
	}
}

void ACItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (ACPlayer* MyPlayer = Cast<ACPlayer>(OtherActor))
	{
		if (MyPlayer->InventoryComponent != nullptr)
		{
			//MyPlayer->InventoryComponent
			MyPlayer->InventoryComponent->AddItem(ItemData);
			Destroy();
		}
	}
}

void ACItem::SetItemRowName(FName InItemName)
{
	ItemRowHandle.RowName = InItemName;
}
