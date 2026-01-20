// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GASPlayerState.generated.h"

class UTestAttributeSet;
class UGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class UNREALNETWORK_API AGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return ASC; }
	UTestAttributeSet* GetResourceAttributeSet() const { return ResourceAS; }

	void SetDefaultAbilitySystemData();
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAbilitySystemComponent> ASC = nullptr;

	UPROPERTY()
	TObjectPtr<UTestAttributeSet> ResourceAS = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Effect")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;
};
