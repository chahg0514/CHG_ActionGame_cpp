// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_EndAttack.h"
#include "CPlayer.h"

FString UCAnimNotify_EndAttack::GetNotifyName_Implementation() const
{
	return TEXT("EndAttack");
}
void UCAnimNotify_EndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr) return;
	ACPlayer* MyPlayer = Cast<ACPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->EndAttack();
}