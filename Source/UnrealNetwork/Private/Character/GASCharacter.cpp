// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/TestAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "UI/DataLineUserWidget.h"

AGASCharacter::AGASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(GetRootComponent());

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	ResourceAttributeSet = CreateDefaultSubobject<UTestAttributeSet>(TEXT("ResourceAS"));


}



void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority() && ASC && AbilityClass)
	{
		ASC->InitAbilityActorInfo(this, this);

		FOnGameplayAttributeValueChange& onHealthChange
			= ASC->GetGameplayAttributeValueChangeDelegate(UTestAttributeSet::GetHealthAttribute());

		ASC->GiveAbility(
			FGameplayAbilitySpec(AbilityClass, 1, -1, this)
		);

		if (Widget && Widget->GetWidget())
		{
			UDataLineUserWidget* HealthWidget = Cast<UDataLineUserWidget>(Widget->GetWidget());
			HealthWidget->UpdateName(FText::AsNumber(ResourceAttributeSet->GetHealth()));
			HealthWidget->UpdateIntValue(FMath::FloorToInt32(ResourceAttributeSet->GetMaxHealth()));
		}
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

	if (Widget && Widget->GetWidget())
	{
		UDataLineUserWidget* HealthWidget = Cast<UDataLineUserWidget>(Widget->GetWidget());
		HealthWidget->UpdateName(FText::AsNumber(NewHealth));
		HealthWidget->UpdateIntValue(FMath::FloorToInt32(ResourceAttributeSet->GetMaxHealth()));
	}
}

void AGASCharacter::TestActivateAbility()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("TestActivateAbility 시작"));
	if (ASC)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("TestActivateAbility : ASC 있음"));
		bool Result = ASC->TryActivateAbilityByClass(AbilityClass);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
			FString::Printf(TEXT("TestActivateAbility : %s"),
				Result ? TEXT("성공") : TEXT("실패")));
	}
}