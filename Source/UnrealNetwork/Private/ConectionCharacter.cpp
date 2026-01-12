// Fill out your copyright notice in the Description page of Project Settings.


#include "ConectionCharacter.h"

// Sets default values
AConectionCharacter::AConectionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConectionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConectionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FString OwnerString = GetOwner() ? GetOwner()->GetName() : TEXT("오너 없음");
	const FString ConnectionString = GetNetConnection() ? TEXT("커넥션 있음") : TEXT("커넥션 없음");
	const FString Value = FString::Printf(TEXT("Owner : %s \n Connection : %s"), *OwnerString, *ConnectionString);
	DrawDebugString(GetWorld(), GetActorLocation(), Value, nullptr, FColor::White, 0.0f, true);
}

// Called to bind functionality to input
void AConectionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

