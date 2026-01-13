// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DataLineUserWidget.h"
#include "Components/TextBlock.h"

void UDataLineUserWidget::UpdateName(FText InName)
{
	Name->SetText(InName);
}

void UDataLineUserWidget::UpdateIntValue(int32 InValue)
{
	Value->SetText(FText::AsNumber(InValue));

}

void UDataLineUserWidget::UpdateFloatValue(float InValue)
{
	Value->SetText(FText::AsNumber(static_cast<int32>(InValue)));
}
