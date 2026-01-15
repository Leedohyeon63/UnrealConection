// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"
class UUserWidget;
/**
 * 
 */
UCLASS()
class UNREALNETWORK_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	FORCEINLINE TWeakObjectPtr<UUserWidget> GetMainHudwidget() const { return MainHudWidget; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainHudWidgetclass = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UUserWidget> MainHudWidget = nullptr;
};
