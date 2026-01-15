// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreActor.generated.h"

UCLASS()
class UNREALNETWORK_API AScoreActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AScoreActor();

protected:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> MeshComp = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<class USphereComponent> Collision = nullptr;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	bool bIsOverlap = false;
};
