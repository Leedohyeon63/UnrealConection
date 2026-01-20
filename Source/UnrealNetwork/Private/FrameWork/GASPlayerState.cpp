// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameWork/GASPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GAS/TestAttributeSet.h"


AGASPlayerState::AGASPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	ResourceAS = CreateDefaultSubobject<UTestAttributeSet>(TEXT("Resource"));

	//SetNetUpdateFrequency = 100.0f;
}

void AGASPlayerState::SetDefaultAbilitySystemData()
{
	if (HasAuthority() && ASC)
	{
		for (TSubclassOf<UGameplayAbility>& Abilityclass : DefaultAbilities)
		{
			if (Abilityclass)
			{
				ASC->GiveAbility(
					FGameplayAbilitySpec(Abilityclass, 1, -1, this)
				);
			}
		}
	}

	for (TSubclassOf <UGameplayEffect>& Effectclass : DefaultEffects)
	{
		if (Effectclass)
		{
			FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(Effectclass, 1, EffectContext);

			if (SpecHandle.IsValid())
			{
				ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

void AGASPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetDefaultAbilitySystemData();
	}

}
