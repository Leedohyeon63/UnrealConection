// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ParticeCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"
#include "UI/DataLineUserWidget.h"
#include "Framework/PracticeController.h"

// Sets default values
AParticeCharacter::AParticeCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AParticeCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthWidgetComponent && HealthWidgetComponent->GetWidget())
	{
		HealthWidget = Cast<UDataLineUserWidget>(HealthWidgetComponent->GetWidget());
		HealthWidget->UpdateName(FText::FromString(TEXT("Health")));
	}
}

// Called every frame
void AParticeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AParticeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AParticeCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AParticeCharacter, Health);
	DOREPLIFETIME_CONDITION(AParticeCharacter, Level, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AParticeCharacter, Exp, COND_OwnerOnly);
}

void AParticeCharacter::OnRef_Level()
{
	UpdateLevel();
}

void AParticeCharacter::OnRef_Exp()
{
	UpdateExp();
}

void AParticeCharacter::OnRef_Health()
{
	UpdateHealth();	// 클라이언트는 리플리케이션을 받아서 업데이트
}

void AParticeCharacter::UpdateLevel()
{
	OnLevelUpdated.Execute(Level);
}

void AParticeCharacter::UpdateExp()
{
	OnExpUpdated.Execute(Exp);
}

void AParticeCharacter::UpdateHealth()
{
	if (HealthWidget.IsValid())
	{
		HealthWidget->UpdateFloatValue(Health);
	}
}

void AParticeCharacter::OnKey1()
{
	if (HasAuthority())
	{
		Level++;
		UpdateLevel();
	}
}

void AParticeCharacter::OnKey2()
{
	if (HasAuthority())
	{
		Exp += 1.0f;
		UpdateExp();
	}
}

void AParticeCharacter::OnKey3()
{
	if (HasAuthority())
	{
		Health -= 10.0f;
		UpdateHealth();	// 서버는 직접 업데이트
	}
}