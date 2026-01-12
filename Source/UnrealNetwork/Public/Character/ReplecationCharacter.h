// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ReplecationCharacter.generated.h"

UCLASS()
class UNREALNETWORK_API AReplecationCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AReplecationCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void OnRepNotify_Level();

public:
	UFUNCTION(BlueprintCallable)
	void TestSetLevel(int32 InLevel);

	UFUNCTION(BlueprintCallable)
	void TestSetHealth(float InHealth);

	UFUNCTION(BlueprintCallable)
	void TestSetExp(float InExp);
protected:
	UPROPERTY(ReplicatedUsing = OnRepNotify_Level)
	int32 Level = 1;

	UPROPERTY(Replicated)
	float Health = 100.0f;

	UPROPERTY(Replicated)
	float Exp = 0.0f;
};
