// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_EnableCombo.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UCAnimNotifyState_EnableCombo : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	FString GetNotifyName_Implementation() const;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
