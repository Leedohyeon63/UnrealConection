// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDWidget.h"
#include "UI/DataLineUserWidget.h"


void UHUDWidget::UpdateLevel(int32 NewLevel)
{
	Level->UpdateIntValue(NewLevel);
}

void UHUDWidget::UpdateExp(float NewExp)
{
	Exp->UpdateFloatValue(NewExp);
}
