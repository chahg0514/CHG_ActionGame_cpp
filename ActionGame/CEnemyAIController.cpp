// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyAIController.h"
#include "BlackboardKeys.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "CPlayer.h"

ACEnemyAIController::ACEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true; //틱함수 활성화
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"))); //퍼셉션 컴포넌트 생성 
																								 //포인터에 내부변수가 있는데 내부변수에 등록시켜준다?
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComp"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAsset(TEXT("BehaviorTree'/Game/Blueprint/Enemy/AI/BT_Enemy.BT_Enemy'"));
	if (BTAsset.Succeeded())
	{
		BTree = BTAsset.Object;
	}
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig")); //시야 정보 객체 생성
	SightConfig->SightRadius = 500.f; //볼 수 있는 범위
	SightConfig->LoseSightRadius = 550.f; //이미 본 목표물을 볼 수 있는 범위
	SightConfig->SetMaxAge(3.0f); //볼 수 있는 시간
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation()); //감지우선순위를 시야로 설정
	GetPerceptionComponent()->ConfigureSense(*SightConfig); //시야 정보 등록
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ACEnemyAIController::OnTargetDetected); //시야범위에 들어왔다면 OnTargetDetected 함수 호출

	SightConfig->DetectionByAffiliation.bDetectNeutrals = true; //중립 감지
}

void ACEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (BTree == nullptr) return;
	RunBehaviorTree(BTree);
	if (Blackboard == nullptr) return;
	Blackboard->InitializeBlackboard(*BTree->BlackboardAsset); //이거는 비헤이비어 트리를 갖고오면 거기 붙어있는 블랙보드가 같이 따라오나봐
}

void ACEnemyAIController::OnTargetDetected(AActor* InActor, FAIStimulus Stimulus)
{
	if (InActor->ActorHasTag(FName(TEXT("Player"))))
	{
		GetBlackboardComponent()->SetValueAsBool(BBKeys::isFIndPlayer, Stimulus.WasSuccessfullySensed());
		TSubclassOf<UAISense> AISense;
		TArray<AActor*> Actors;
		GetPerceptionComponent()->GetCurrentlyPerceivedActors(AISense, Actors); //감지된 액터를 모두 배열에 넣어줌
		for (auto Other : Actors)
		{
			if (ACPlayer* MyPlayer = Cast<ACPlayer>(Other))
			{
				GetBlackboardComponent()->SetValueAsObject(BBKeys::target, MyPlayer);
				//블랙보드의 target에 플레이어를 넣어줌
			}
		}
	}
}
