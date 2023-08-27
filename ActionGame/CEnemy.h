// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

UCLASS()
class ACTIONGAME_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* Causer) override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Stat")
		float damage = 10.f;
	UPROPERTY(VisibleAnywhere, Category = "Stat")
		float currentHP = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Stat")
		float maxHP = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Stat")
		float attackRange = 150.f;
	UPROPERTY(VisibleAnywhere, Category = "Stat")
		float attackRadius = 80.f;

public:
	void SendDamage();

};
