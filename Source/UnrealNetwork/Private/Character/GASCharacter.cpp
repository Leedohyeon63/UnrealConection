// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/TestAttributeSet.h"

AGASCharacter::AGASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	ResourceAttributeSet = CreateDefaultSubobject<UTestAttributeSet>(TEXT("ResourceAS"));
}

void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);

		FOnGameplayAttributeValueChange& onHealthChange
			= ASC->GetGameplayAttributeValueChangeDelegate(UTestAttributeSet::GetHealthAttribute());
	}
}

void AGASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGASCharacter::OnHealthChange(const FOnAttributeChangeData& Data)
{
	const float NewHealth = Data.NewValue;

	UE_LOG(LogTemp, Log, TEXT("현재 체력 : %.1f"), NewHealth);	
}

