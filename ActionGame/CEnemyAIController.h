// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Perception/AIPerceptionTypes.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "CEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API ACEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACEnemyAIController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception", meta = (AllowPrivateAccess = true))
		class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception", meta = (AllowPrivateAccess = true))
		class UBehaviorTree* BTree;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception", meta = (AllowPrivateAccess = true))
		class UBlackboardComponent* BBComp;
private:
	UFUNCTION(BlueprintCallable, Category = "Perception")
		void OnTargetDetected(AActor* InActor, FAIStimulus Stimulus);
	
};
