// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"

#include "CEnemyAIController.h"
#include "CEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	NodeName = TEXT("ChangeSpeed");
}

void UBTService_ChangeSpeed::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
	if (SearchData.OwnerComp.GetAIOwner() == nullptr) return;
	ACEnemy* Enemy = Cast<ACEnemy>(SearchData.OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy == nullptr) return;
	Enemy->GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}
