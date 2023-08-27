// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_EnableCombo.h"
#include "CPlayer.h"

FString UCAnimNotifyState_EnableCombo::GetNotifyName_Implementation() const
{
	return TEXT("EnableCombo");
}

void UCAnimNotifyState_EnableCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp == nullptr) return;
	ACPlayer* MyPlayer = Cast<ACPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->SetIsEnableCombo(true);
}

void UCAnimNotifyState_EnableCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp == nullptr) return;
	ACPlayer* MyPlayer = Cast<ACPlayer>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;
	MyPlayer->SetIsEnableCombo(false);
}
