// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

DECLARE_DELEGATE(FHealthEvent); //옵저버 패턴

UCLASS()
class ACTIONGAME_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, Category = "Attack")
		class UAnimMontage* AttackMontage;
	UPROPERTY(VisibleAnywhere, Category = "Attack")
		class UAnimMontage* LastAttackMontage;
private:
	bool isAttack = false;
	bool isNextAttack = false;
	bool isEnableCombo = false;
	bool isMove = true;
	int32 ComboCount = 0;
public:
	void Zoom(float Axis);
	void Attack();
	void NextAttack();
	void EndAttack();
public:
	FORCEINLINE bool GetIsAttack() { return isAttack; }

	FORCEINLINE void SetIsAttack(bool InIsAttack) 
	{ 
		isAttack = InIsAttack;
	}

	FORCEINLINE bool GetIsEnableCombo() { return isEnableCombo; }
	FORCEINLINE void SetIsEnableCombo(bool InIsEnableCombo)
	{
		isEnableCombo = InIsEnableCombo;
	}

	FORCEINLINE bool GetIsMove() { return isMove; }
	
private:
	UPROPERTY(VisibleAnywhere, Category = "State")
		float damage = 10.f;
	UPROPERTY(VisibleAnywhere, Category = "State")
		float currentHP = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "State")
		float maxHP = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "State")
		float attackRange = 250.f;
	UPROPERTY(VisibleAnywhere, Category = "State")
		float attackRadius = 80.f;
public:
	void SendDamage();
protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	FHealthEvent HealthEvent;
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; //게임 종료시 호출
public:
	FORCEINLINE float GetCurrentHp()
	{
		return currentHP;
	}
	FORCEINLINE float GetMaxHp()
	{
		return maxHP;
	}
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
		class UCInventoryComponent_Real* InventoryComponent;
};
