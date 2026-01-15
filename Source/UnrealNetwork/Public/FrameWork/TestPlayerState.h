// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TestPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALNETWORK_API ATestPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddMyScore(int32 InPoint);

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetMyScore() { return MyScore; }

	UFUNCTION(BlueprintCallable, Category = "Name")
	void SetMyName(const FString& NewName);

	UFUNCTION(BlueprintCallable, Category = "Name")
	const FString& GetMyName() const { return MyName; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_MyScore();

	UFUNCTION()
	void OnRep_MyName();
protected:
	UPROPERTY(ReplicatedUsing = OnRep_Score, BlueprintReadOnly, Category = "Data")
	int32 MyScore = 0;

	TWeakObjectPtr<class UScoreHudWidget> ScoreHud = nullptr;

	UPROPERTY(ReplicatedUsing = OnRep_MyName, BlueprintReadOnly, Category = "Data")
	FString MyName;

};
