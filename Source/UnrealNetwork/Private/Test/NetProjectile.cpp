// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NetProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"

// Sets default values
ANetProjectile::ANetProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true; //이 액터는 리플리케이션을 한다
	SetReplicateMovement(true); // 이 액터의 무브먼트 컴포넌트는 리플리케이션이 된다.

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(20.0f);
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(Collision);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	//Movement->UpdatedComponent = Collision;
	Movement->InitialSpeed = 1000.0f;
	Movement->MaxSpeed = 1000.0f;
	Movement->bShouldBounce = true;
}

// Called when the game starts or when spawned
void ANetProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ANetProjectile::OnHit);

	if (GetInstigator())
	{
		//발사한 사람은 무시
		Collision->IgnoreActorWhenMoving(GetInstigator(), true);
	}
}

void ANetProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		if (!IsHit && OtherActor -> IsA<ACharacter>())
		{
			if (GetInstigator())
			{
				UE_LOG(LogTemp, Log, TEXT("%s가 %s를 공격"), *GetInstigator()->GetName(), *OtherActor->GetName());
			}

			Multicast_HitEffect(Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			SetLifeSpan(2.0f);
			IsHit = true;
		}
	}

}

void ANetProjectile::Multicast_HitEffect_Implementation(const FVector& InLocation, const FRotator& InRotation)
{
	if (HitEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, InLocation, InRotation);
	}
}


