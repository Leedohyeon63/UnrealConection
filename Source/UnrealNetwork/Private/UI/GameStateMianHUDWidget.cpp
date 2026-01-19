// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameStateMianHUDWidget.h"
#include "Framework/TestGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UGameStateMianHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameOverText->SetVisibility(ESlateVisibility::Hidden);
}

void UGameStateMianHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<ATestGameStateBase>(UGameplayStatics::GetGameState(this));
	}
	UpdateTimeDisplay();
	UpdateGameOverDisplay();
}

void UGameStateMianHUDWidget::UpdateTimeDisplay()
{
	if (CachedGameState.IsValid())
	{
		int32 Total = FMath::FloorToInt(CachedGameState->GetGameElapsedTime());
		int32 Minutes = Total / 60;
		int32 Seconds = Total % 60;
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));

		Total = FMath::FloorToInt(CachedGameState->GetGameRemainingTime());
		Minutes = Total / 60;
		Seconds = Total % 60;
		RemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}

void UGameStateMianHUDWidget::UpdateGameOverDisplay()
{
	if (CachedGameState->IsGameOver())
	{
		GameOverText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		GameOverText->SetVisibility(ESlateVisibility::Hidden);
	}
}
