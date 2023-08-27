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
	PrimaryActorTick.bCanEverTick = true; //ƽ�Լ� Ȱ��ȭ
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"))); //�ۼ��� ������Ʈ ���� 
																								 //�����Ϳ� ���κ����� �ִµ� ���κ����� ��Ͻ����ش�?
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComp"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAsset(TEXT("BehaviorTree'/Game/Blueprint/Enemy/AI/BT_Enemy.BT_Enemy'"));
	if (BTAsset.Succeeded())
	{
		BTree = BTAsset.Object;
	}
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig")); //�þ� ���� ��ü ����
	SightConfig->SightRadius = 500.f; //�� �� �ִ� ����
	SightConfig->LoseSightRadius = 550.f; //�̹� �� ��ǥ���� �� �� �ִ� ����
	SightConfig->SetMaxAge(3.0f); //�� �� �ִ� �ð�
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation()); //�����켱������ �þ߷� ����
	GetPerceptionComponent()->ConfigureSense(*SightConfig); //�þ� ���� ���
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ACEnemyAIController::OnTargetDetected); //�þ߹����� ���Դٸ� OnTargetDetected �Լ� ȣ��

	SightConfig->DetectionByAffiliation.bDetectNeutrals = true; //�߸� ����
}

void ACEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (BTree == nullptr) return;
	RunBehaviorTree(BTree);
	if (Blackboard == nullptr) return;
	Blackboard->InitializeBlackboard(*BTree->BlackboardAsset); //�̰Ŵ� �����̺�� Ʈ���� ������� �ű� �پ��ִ� �����尡 ���� ���������
}

void ACEnemyAIController::OnTargetDetected(AActor* InActor, FAIStimulus Stimulus)
{
	if (InActor->ActorHasTag(FName(TEXT("Player"))))
	{
		GetBlackboardComponent()->SetValueAsBool(BBKeys::isFIndPlayer, Stimulus.WasSuccessfullySensed());
		TSubclassOf<UAISense> AISense;
		TArray<AActor*> Actors;
		GetPerceptionComponent()->GetCurrentlyPerceivedActors(AISense, Actors); //������ ���͸� ��� �迭�� �־���
		for (auto Other : Actors)
		{
			if (ACPlayer* MyPlayer = Cast<ACPlayer>(Other))
			{
				GetBlackboardComponent()->SetValueAsObject(BBKeys::target, MyPlayer);
				//�������� target�� �÷��̾ �־���
			}
		}
	}
}
