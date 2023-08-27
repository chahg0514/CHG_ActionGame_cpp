// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerAnimInstance.h"
#include "CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

UCPlayerAnimInstance::UCPlayerAnimInstance()
{
	Speed = 0.f;
	Direction = 0.f;
	isAir = false;
}
void UCPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MyPlayer = Cast<ACPlayer>(TryGetPawnOwner());
}
void UCPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!IsValid(MyPlayer)) return;
	Speed = MyPlayer->GetVelocity().Size2D();
	FRotator Rot = FRotator(0, MyPlayer->GetControlRotation().Yaw, 0);
	
	Direction = CalculateDirection(MyPlayer->GetVelocity(), Rot);
	isAir = MyPlayer->GetCharacterMovement()->IsFalling();
}
