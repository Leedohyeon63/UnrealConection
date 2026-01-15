// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameWork/MainHUD.h"
#include "Blueprint/UserWidget.h"
void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	if (MainHudWidgetclass)
	{
		MainHudWidget = CreateWidget<UUserWidget>(
			GetWorld(), MainHudWidgetclass
		);

		if (MainHudWidget.IsValid())
		{
			MainHudWidget->AddToViewport();
		}
	}
}
