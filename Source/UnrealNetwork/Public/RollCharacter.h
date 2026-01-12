// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConectionCharacter.h"
#include "RollCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALNETWORK_API ARollCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;

};
