// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include "CEnemyAIController.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"



// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonSunWukong/Characters/Heroes/Wukong/Meshes/Wukong.Wukong'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	//Tags.Add("Enemy");

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Blueprint/Enemy/Animation/ABP_Enemy.ABP_Enemy_C'"));
	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}
	AIControllerClass = ACEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//Tags.Add("Enemy");
	Tags.Add(FName(TEXT("Enemy")));
}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* Causer)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, Causer);
	currentHP -= Damage;
	if (currentHP <= 0)
	{
		Destroy();
	}

	return 0.0f;
}

void ACEnemy::SendDamage()
{
	FVector Start, End, Direction;
	Start = GetActorLocation();
	Direction = GetActorForwardVector();
	End = Start += (Direction * attackRange);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; //충돌가능 오브젝트 유형
	TEnumAsByte<EObjectTypeQuery> PawnType = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn); //폰타입
	ObjectTypes.Add(PawnType);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	FHitResult HitResult;

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, attackRadius, ObjectTypes,
		false, IgnoreActors, EDrawDebugTrace::None, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.5f))
	{
		if (IsValid(HitResult.GetActor()))
		{
			if (HitResult.Actor.Get()->ActorHasTag(FName(TEXT("Player"))))
			{
				UGameplayStatics::ApplyDamage(HitResult.GetActor(), damage, GetController(), this, UDamageType::StaticClass()); //데미지 전달

			}
		}
		
	}
}

