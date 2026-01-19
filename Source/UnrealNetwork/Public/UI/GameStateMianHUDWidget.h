// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStateMianHUDWidget.generated.h"
class UTextBlock;
/**
 * 
 */
UCLASS()
class UNREALNETWORK_API UGameStateMianHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateTimeDisplay();

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateGameOverDisplay();
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> RemainingTimeText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> GameOverText = nullptr;

private:
	TWeakObjectPtr<class ATestGameStateBase> CachedGameState = nullptr;
};
