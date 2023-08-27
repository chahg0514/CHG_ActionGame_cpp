// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACPlayerController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
private:
	UFUNCTION()
		void MoveForward(float Axis);
	UFUNCTION()
		void MoveRight(float Axis);
	UFUNCTION()
		void Zoom(float Axis);
	UFUNCTION()
		void Turn(float Axis);
	UFUNCTION()
		void LookUp(float Axis);
	UFUNCTION()
		void PlayerJump();
	UFUNCTION()
		void PlayerAttack();
	UFUNCTION()
		void ShowInventory();
private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
		class ACPlayer* MyPlayer;
	
};
