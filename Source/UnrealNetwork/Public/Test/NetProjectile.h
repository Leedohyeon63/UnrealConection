// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetProjectile.generated.h"

UCLASS()
class UNREALNETWORK_API ANetProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ANetProjectile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_HitEffect(const FVector& InLocation, const FRotator& InRotation);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<class USphereComponent> Collision = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<class UProjectileMovementComponent> Movement = nullptr;

	UPROPERTY(EditAnywhere, Category = "Component")
	TObjectPtr<class UNiagaraSystem> HitEffect = nullptr;

private:
	bool bIsHit = false;
};
