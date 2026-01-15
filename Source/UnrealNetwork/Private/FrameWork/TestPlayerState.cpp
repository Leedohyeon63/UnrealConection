// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameWork/TestPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "FrameWork/MainHUD.h"
#include "UI/ScoreHudWidget.h"
#include "Character/PlayerStateCharacter.h"


void ATestPlayerState::AddMyScore(int32 InPoint)
{
	if (HasAuthority())
	{
		MyScore+=InPoint;
		OnRep_MyScore();
	}
}

void ATestPlayerState::SetMyName(const FString& NewName)
{
	if (HasAuthority())
	{
		if (NewName.IsEmpty())
		{
			MyName = TEXT("MyPlayer");
		}
		else
		{
			MyName = NewName;
		}
		OnRep_MyName();
	}
}

void ATestPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestPlayerState, MyScore);
}



void ATestPlayerState::OnRep_MyScore()
{

	// UI 갱신
	UE_LOG(LogTemp, Log, TEXT("[%d]Score : %d"), GetPlayerId(), MyScore);
	if (!ScoreHud.IsValid())
	{
		if (GetPlayerController())
		{
			//UE_LOG(LogTemp, Log, TEXT("플레이어 컨트롤러 있음"));
			AMainHUD* HUD = GetPlayerController()->GetHUD<AMainHUD>();
			if (HUD && HUD->GetMainHudwidget().IsValid())
			{
				//UE_LOG(LogTemp, Log, TEXT("HUD와 HUD위젯도 있음"));
				ScoreHud = Cast<UScoreHudWidget>(HUD->GetMainHudwidget().Get());
			}
		}
	}
	if (ScoreHud.IsValid())
	{
		ScoreHud->UpdateScore(MyScore);
	}
}

void ATestPlayerState::OnRep_MyName()
{
	UE_LOG(LogTemp, Log, TEXT("[%d]Name : %s"), GetPlayerId(), *MyName);

	if (APlayerStateCharacter* Character = GetPawn<APlayerStateCharacter>())
	{
		Character->UpdateNamePlate(MyName);
	}
}
