// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_SendDamage.h"
#include "CPlayer.h"

void UCAnimNotify_SendDamage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr) return;
	ACPlayer* MyPlayer = Cast<ACPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->SendDamage();
}
