// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UCAnimNotify_EndAttack : public UAnimNotify
{
	GENERATED_BODY()
protected:
	FString GetNotifyName_Implementation() const;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
