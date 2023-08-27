// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UCAnimInstance_Enemy : public UAnimInstance
{
	GENERATED_BODY()
public:
	UCAnimInstance_Enemy();
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
		float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
		float Direction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
		class ACEnemy* MyEnemy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
		class UAnimMontage* AttackMontage;
public:
	void PlayAttackAnim();
private:
	UFUNCTION()
		void AnimNotify_Damage();
	UFUNCTION()
		void AnimNotify_Attack23();
	
};
