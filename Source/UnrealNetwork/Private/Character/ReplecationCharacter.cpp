// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ReplecationCharacter.h"
#include "Net/UnrealNetwork.h"
// Sets default values
AReplecationCharacter::AReplecationCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReplecationCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReplecationCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FString Str = FString::Printf(TEXT("LV(%d), Exp(%.1f), Health(%.1f)"), Level, Exp, Health);
	DrawDebugString(GetWorld(), GetActorLocation(), Str, nullptr, FColor::White, 0, true);
}

// Called to bind functionality to input
void AReplecationCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AReplecationCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME(AReplecationCharacter, Health, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(AReplecationCharacter, Level, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AReplecationCharacter, Exp, COND_OwnerOnly);
}

void AReplecationCharacter::OnRepNotify_Level()
{
	const FString Str = FString::Printf(TEXT("서버에서 레벨을 %d로 변경"), Level);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Str);
}

void AReplecationCharacter::TestSetLevel(int32 InLevel)
{
	if (HasAuthority())
	{
		Level = InLevel;
	}
}

void AReplecationCharacter::TestSetHealth(float InHealth)
{
	if (HasAuthority())
	{
		Health = InHealth;
	}


}

void AReplecationCharacter::TestSetExp(float InExp)
{
	if (HasAuthority())
	{
		Exp = InExp;
	}
}

