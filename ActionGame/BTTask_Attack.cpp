// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "CEnemyAIController.h"
#include "CAnimInstance_Enemy.h"
#include "CEnemy.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true; //틱함수 사용
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	if (OwnerComp.GetAIOwner()->GetPawn() == nullptr) return EBTNodeResult::Failed;

	ACEnemy* Enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	UCAnimInstance_Enemy* Anim = Cast<UCAnimInstance_Enemy>(Enemy->GetMesh()->GetAnimInstance());

	if (Anim == nullptr) return EBTNodeResult::Failed;
	Anim->PlayAttackAnim();
	return EBTNodeResult::InProgress;

}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (OwnerComp.GetAIOwner() == nullptr) return;
	if (OwnerComp.GetAIOwner()->GetPawn() == nullptr) return ;

	ACEnemy* Enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	UCAnimInstance_Enemy* Anim = Cast<UCAnimInstance_Enemy>(Enemy->GetMesh()->GetAnimInstance());
	
	if (Anim == nullptr) return;
	if (Anim->Montage_GetIsStopped(Enemy->GetCurrentMontage())) //이거 복습 다시
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); //성공반환
	}

}
