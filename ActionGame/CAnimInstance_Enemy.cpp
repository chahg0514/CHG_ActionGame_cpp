// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance_Enemy.h"
#include "CEnemy.h"


UCAnimInstance_Enemy::UCAnimInstance_Enemy()
{
	Speed = 0.0f;
	Direction = 0.0f;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMtg(TEXT("AnimMontage'/Game/Blueprint/Enemy/Animation/EnemyAttackMontage.EnemyAttackMontage'"));
	if (AttackMtg.Succeeded())
	{
		AttackMontage = AttackMtg.Object;
	}
}

void UCAnimInstance_Enemy::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (IsValid(TryGetPawnOwner()))
	{
		MyEnemy = Cast<ACEnemy>(TryGetPawnOwner());
	}
}

void UCAnimInstance_Enemy::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!IsValid(MyEnemy)) return;
	Speed = MyEnemy->GetVelocity().Size2D();
	Direction = CalculateDirection(MyEnemy->GetVelocity(), MyEnemy->GetControlRotation());

}

void UCAnimInstance_Enemy::PlayAttackAnim()
{
	Montage_Play(AttackMontage); //공격몽타주 재생

}

void UCAnimInstance_Enemy::AnimNotify_Damage()
{
	MyEnemy->SendDamage();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("EnemyAttack"));
}

void UCAnimInstance_Enemy::AnimNotify_Attack23()
{
}

