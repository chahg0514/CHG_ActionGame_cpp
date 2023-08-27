// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetRandomLocation.h"
#include "CEnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTask_GetRandomLocation.h"
#include "BlackboardKeys.h"

UBTTask_GetRandomLocation::UBTTask_GetRandomLocation()
{
	NodeName = TEXT("GetRandomLocation");
}

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACEnemyAIController* EnemyAIController = Cast<ACEnemyAIController>(OwnerComp.GetAIOwner());
	if (EnemyAIController == nullptr)
		return EBTNodeResult::Failed; //���й�ȯ

	APawn* Enemy = EnemyAIController->GetPawn();
	if (Enemy == nullptr) return EBTNodeResult::Failed;

	FVector Origin = Enemy->GetActorLocation();
	FNavLocation NavPos;
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()); //���忡 �ִ� �׺���̼��� ������
	if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, NavPos))
	{
		EnemyAIController->GetBlackboardComponent()->SetValueAsVector(BBKeys::randomPos, NavPos.Location);
		return EBTNodeResult::Succeeded;
		//������ǥ�� �����忡 ����
	}
	return EBTNodeResult::Failed;

}
