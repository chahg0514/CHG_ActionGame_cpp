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
		return EBTNodeResult::Failed; //실패반환

	APawn* Enemy = EnemyAIController->GetPawn();
	if (Enemy == nullptr) return EBTNodeResult::Failed;

	FVector Origin = Enemy->GetActorLocation();
	FNavLocation NavPos;
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()); //월드에 있는 네비게이션을 가져옴
	if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, NavPos))
	{
		EnemyAIController->GetBlackboardComponent()->SetValueAsVector(BBKeys::randomPos, NavPos.Location);
		return EBTNodeResult::Succeeded;
		//랜덤좌표를 블랙보드에 저장
	}
	return EBTNodeResult::Failed;

}
