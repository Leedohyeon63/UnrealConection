// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameWork/PracticeController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Character/ParticeCharacter.h"
#include "GameFramework/PlayerState.h"
#include "UI/HUDWidget.h"

void APracticeController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (HUDWidgetClass)
		{
			HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
			if (HUDWidget.IsValid())
			{
				HUDWidget.Get()->AddToViewport();
			}
		}
	}
}

void APracticeController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalController())
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		if (SubSystem)
		{
			SubSystem->AddMappingContext(MappingContext, 0);
		}

		UEnhancedInputComponent* EnhanedInput = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhanedInput)
		{
			EnhanedInput->BindAction(IA_Key1, ETriggerEvent::Started, this, &APracticeController::OnKey1Press);
			EnhanedInput->BindAction(IA_Key2, ETriggerEvent::Started, this, &APracticeController::OnKey2Press);
			EnhanedInput->BindAction(IA_Key3, ETriggerEvent::Started, this, &APracticeController::OnKey3Press);
		}
	}
}

void APracticeController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	ControlledCharacter = Cast<AParticeCharacter>(aPawn);

	ControlledCharacter->OnLevelUpdated.BindWeakLambda(
		this,
		[this](int NewLevel)
		{
			if (HUDWidget.IsValid())
			{
				HUDWidget->UpdateLevel(NewLevel);
			}
		}
	);

	ControlledCharacter->OnExpUpdated.BindWeakLambda(
		this,
		[this](int NewExp)
		{
			if (HUDWidget.IsValid())
			{
				HUDWidget->UpdateExp(NewExp);
			}
		}
	);
}

void APracticeController::OnUnPossess()
{
	ControlledCharacter = nullptr;
	Super::OnUnPossess();
}

void APracticeController::OnKey1Press()
{
	const FString Str = FString::Printf(
		TEXT("%s[%d] : OnKey1Press"),
		HasAuthority() ? TEXT("Server") : TEXT("Client"),
		PlayerState->GetPlayerId());

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Str);
	if (ControlledCharacter.IsValid())
	{
		ControlledCharacter.Get()->OnKey1();
	}
}

void APracticeController::OnKey2Press()
{
	const FString Str = FString::Printf(
		TEXT("%s[%d] : OnKey2Press"),
		HasAuthority() ? TEXT("Server") : TEXT("Client"),
		PlayerState->GetPlayerId());

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Str);
	if (ControlledCharacter.IsValid())
	{
		ControlledCharacter.Get()->OnKey2();
	}
}

void APracticeController::OnKey3Press()
{
	const FString Str = FString::Printf(
		TEXT("%s[%d] : OnKey3Press"),
		HasAuthority() ? TEXT("Server") : TEXT("Client"),
		PlayerState->GetPlayerId());

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Str);
	if (ControlledCharacter.IsValid())
	{
		ControlledCharacter.Get()->OnKey3();
	}
}