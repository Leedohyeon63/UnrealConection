// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreHudWidget.generated.h"

class UDataLineUserWidget;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class UNREALNETWORK_API UScoreHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateScore(int32 NewScore);

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void NameCommitted(const FText& Text, ETextCommit::Type CommitMethod);

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UDataLineUserWidget> SCore;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> NameInput;

private:
	TWeakObjectPtr<class APlayerStateCharacter> OwningPlayerCharacter = nullptr;
};
