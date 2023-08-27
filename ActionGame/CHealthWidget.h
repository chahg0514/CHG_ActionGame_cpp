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
	//���� ������ ȣ��Ǵ� �Լ�

	virtual void NativeConstruct() override; //�̰Ÿ� ���µ� �������� ������ ���ؼ� �����а���
	//AddToViewport�� ������ ȣ��Ǵ� �Լ�

	//virtual void NativeDestruct() override;
	//RemoveFromViewport �Ҷ����� ȣ��Ǵ� �Լ�

	//virtual void NativeTick(const FGeometry& InGeometry, float InDeltaTime) override; 
	//ƽ�Լ�
	
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
