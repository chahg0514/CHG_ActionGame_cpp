// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "CInventoryComponent_Real.h"

// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonTerra/Characters/Heroes/Terra/Skins/GryphonKnight/Meshes/Terra_GryphonKnight.Terra_GryphonKnight'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeLocation(FVector(-35, 0, 0));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = false; //�ٸ� ��ü�� �浹 ����
	
	
	 

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	Tags.Add(FName(TEXT("Player")));

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Blueprint/Player/Animation/ABP_Player.ABP_Player_C'"));
	if (AnimAsset.Succeeded())
	{
		//GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
		GetMesh()->AnimClass = AnimAsset.Class;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMtg(TEXT("AnimMontage'/Game/Blueprint/Player/Animation/PlayerAttackMontage.PlayerAttackMontage'"));
	if(AttackMtg.Succeeded())
	{
		AttackMontage = AttackMtg.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LastAttackMtg(TEXT("AnimMontage'/Game/Blueprint/Player/Animation/PlayerLastAttackMontage.PlayerLastAttackMontage'"));
	if (AttackMtg.Succeeded())
	{
		LastAttackMontage = LastAttackMtg.Object;
	}

	InventoryComponent = CreateDefaultSubobject<UCInventoryComponent_Real>(TEXT("InventoryComponent"));

}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPlayer::Zoom(float Axis)
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength - (Axis * 10), 100.0f, 1200.0f);
	//FMath::Clamp: 100���� ������ 100 ��ȯ, 1200���� ũ�� 1200 ��ȯ, 100���� 1200 ������ ���� ���� �� �ִ�.
}

void ACPlayer::Attack()
{
	if (!isAttack)
	{
		PlayAnimMontage(AttackMontage, 1.7f, FName(TEXT("Attack1")));
		isAttack = true;
		ComboCount++;
	}
	else
	{
		isNextAttack = true;
	}
}

void ACPlayer::NextAttack()
{
	if (isNextAttack)
	{
		if (isEnableCombo)
		{
			if (ComboCount == 1)
			{
				PlayAnimMontage(AttackMontage, 1.7f, FName(TEXT("Attack2")));
				isNextAttack = false;
				ComboCount++;
			}
			else if (ComboCount == 2)
			{
				PlayAnimMontage(LastAttackMontage, 1.f);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PlayLastMontage"));
				isNextAttack = false;
				isMove = false;
				ComboCount = 0;
			}
		}
		
	}
}

void ACPlayer::EndAttack()
{
	isMove = true;
	isAttack = false;
	isNextAttack = false;
	ComboCount = 0;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("EndAttack!!!"));
}

void ACPlayer::SendDamage() //���� ������ ����
{
	FVector Start, End, Direction;
	Start = GetActorLocation();
	Direction = GetActorForwardVector();
	End = Start += (Direction * attackRange);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; //�浹���� ������Ʈ ����
	TEnumAsByte<EObjectTypeQuery> PawnType = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn); //��Ÿ��
	TEnumAsByte<ETraceTypeQuery> sdf = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Pawn);
	ObjectTypes.Add(PawnType);
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	FHitResult HitResult;

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, attackRadius, ObjectTypes,
		false, IgnoreActors, EDrawDebugTrace::None, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.5f))
	{
		if (HitResult.Actor.Get()->ActorHasTag(FName(TEXT("Enemy"))))
		{
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), damage, GetController(), this,UDamageType::StaticClass());

		}
	}
}

float ACPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	currentHP -= Damage;
	if (HealthEvent.IsBound()) //�Լ��� ����Ǿ��ִ���?
	{
		HealthEvent.Execute();

	}
	if (currentHP <= 0)
	{
		GetCharacterMovement()->StopMovementImmediately(); //�̵� ����
		GetCharacterMovement()->DisableMovement();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�ݸ��� ��Ȱ��ȭ
		GetController()->UnPossess(); //��������
	}
	return 0.0f;
}

void ACPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	HealthEvent.Unbind(); //��������
}

