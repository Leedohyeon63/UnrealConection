// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreHudWidget.h"
#include "UI/DataLineUserWidget.h"
#include "Components/EditableTextBox.h"
#include "Framework/TestPlayerState.h"
#include "Character/PlayerStateCharacter.h"


void UScoreHudWidget::UpdateScore(int32 NewScore)
{
	SCore->UpdateIntValue(NewScore);
}

void UScoreHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Super::NativeConstruct();
	SCore->UpdateName(FText::FromString(TEXT("점수")));
	SCore->UpdateIntValue(0);

	NameInput->OnTextCommitted.AddDynamic(this, &UScoreHudWidget::NameCommitted);
}

void UScoreHudWidget::NameCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	UE_LOG(LogTemp, Log, TEXT("NameCommitted"));
	if (CommitMethod == ETextCommit::OnEnter)
	{
		UE_LOG(LogTemp, Log, TEXT("ETextCommit::OnEnter"));
		if (!OwningPlayerCharacter.IsValid())
		{
			if (APlayerController* PC = GetOwningPlayer())
			{
				OwningPlayerCharacter = Cast<APlayerStateCharacter>(PC->GetPawn());
			}
		}
		if (OwningPlayerCharacter.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("[%d] Name : %s"),
				OwningPlayerCharacter->GetPlayerState()->GetPlayerId(),
				*Text.ToString());
			OwningPlayerCharacter->SetMyName(Text.ToString());
		}
		UE_LOG(LogTemp, Log, TEXT("NameCommitted Finish"));
	}
}
