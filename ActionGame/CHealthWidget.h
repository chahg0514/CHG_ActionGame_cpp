// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UCHealthWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	//virtual void NativeOnInitialized() override;
	//위젯 생성시 호출되는 함수

	virtual void NativeConstruct() override; //이거만 쓰는데 나머지는 설명을 위해서 만들어둔거임
	//AddToViewport할 때마다 호출되는 함수

	//virtual void NativeDestruct() override;
	//RemoveFromViewport 할때마다 호출되는 함수

	//virtual void NativeTick(const FGeometry& InGeometry, float InDeltaTime) override; 
	//틱함수
	
private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UProgressBar* HealthBar;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UTextBlock* CurrentHealthText;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
		class UTextBlock* MaxHealthText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player", meta = (AllowPrivateAccess = true))
		class ACPlayer* Player;

public:
	void SetHealth();
};
