// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"
class UDataLineUserWidget;
/**
 * 
 */
UCLASS()
class UNREALNETWORK_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void UpdateLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable)
	void UpdateExp(float NewExp);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UDataLineUserWidget> Level = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UDataLineUserWidget> Exp = nullptr;
};
