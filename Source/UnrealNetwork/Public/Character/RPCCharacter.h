// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPCCharacter.generated.h"

UCLASS()
class UNREALNETWORK_API ARPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPCCharacter();

	UFUNCTION(BlueprintCallable, Category = "TestRPC")
	void Fire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Reliable)//서버 rpc, 무조건 실행 수신 확인시까지 요청 반복
	void Sever_Fire();

	UFUNCTION(Client, Reliable)
	void Client_OnHit();

	UFUNCTION()
	void OnTakeDamage(
		AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TestRPC")
	TObjectPtr<USceneComponent> FireLocation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TestRPC")
	TSubclassOf<AActor> ProjectileCLass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TestRPC")
	TSubclassOf<class UCameraShakeBase> CameraShakeClass = nullptr;
};
