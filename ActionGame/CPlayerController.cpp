// Fill out your copyright notice in the Description page of Project Settings.

#include "CPlayerController.h"
#include "CPlayer.h"
#include "CInventoryComponent_Real.h"


ACPlayerController::ACPlayerController()
{

}

void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!IsValid(InPawn)) return;
	MyPlayer = Cast<ACPlayer>(InPawn);
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ACPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ACPlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("Zoom"), this, &ACPlayerController::Zoom);
	InputComponent->BindAxis(TEXT("Turn"), this, &ACPlayerController::Turn);
	InputComponent->BindAxis(TEXT("LookUp"), this, &ACPlayerController::LookUp);
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACPlayerController::PlayerJump);
	InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ACPlayerController::PlayerAttack);
	InputComponent->BindAction(TEXT("Inventory"), IE_Pressed, this, &ACPlayerController::ShowInventory);

}

void ACPlayerController::MoveForward(float Axis)
{
	if (Axis != 0.0f && MyPlayer->GetIsMove())
	{
		const FRotator Rot = GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		GetPawn()->AddMovementInput(Direction, Axis);
	}
}

void ACPlayerController::MoveRight(float Axis)
{
	if (Axis != 0.0f && MyPlayer->GetIsMove())
	{
		const FRotator Rot = GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		GetPawn()->AddMovementInput(-Direction, Axis);
	}
}

void ACPlayerController::Zoom(float Axis)
{
	if (IsValid(MyPlayer))
	{
		MyPlayer->Zoom(Axis);
	}
}

void ACPlayerController::Turn(float Axis)
{
	AddYawInput(Axis);
}

void ACPlayerController::LookUp(float Axis)
{
	AddPitchInput(Axis);
}

void ACPlayerController::PlayerJump()
{
	if (IsValid(MyPlayer))
	{
		MyPlayer->Jump();
	}
}

void ACPlayerController::PlayerAttack()
{
	if (IsValid(MyPlayer))
	{
		MyPlayer->Attack();
		MyPlayer->NextAttack();
	}
}

void ACPlayerController::ShowInventory()
{
	MyPlayer->InventoryComponent->ShowInventory();
}
