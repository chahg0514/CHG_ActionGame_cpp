// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_NextAttack.h"
#include "CPlayer.h"

FString UCAnimNotify_NextAttack::GetNotifyName_Implementation() const
{
	return TEXT("NextAttack");
}
void UCAnimNotify_NextAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
