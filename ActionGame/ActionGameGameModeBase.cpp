// Copyright Epic Games, Inc. All Rights Reserved.


#include "ActionGameGameModeBase.h"

#include "CPlayer.h"
#include "CPlayerController.h"

#include "Blueprint/UserWidget.h"

AActionGameGameModeBase::AActionGameGameModeBase()
{
	DefaultPawnClass = ACPlayer::StaticClass();
	PlayerControllerClass = ACPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("WidgetBlueprint'/Game/Blueprint/Player/Widget/CWB_HealthWidget.CWB_HealthWidget_C'"));
	if (WidgetAsset.Succeeded())
	{
		HealthWidget = WidgetAsset.Class;
	}
}

void AActionGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (HealthWidget != nullptr)
	{
		CreateWidget<UUserWidget>(GetWorld(), HealthWidget)->AddToViewport();
	}
}
