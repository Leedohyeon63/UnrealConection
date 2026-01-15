// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/ScoreActor.h"
#include  "Character/PlayerStateCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

// Sets default values
AScoreActor::AScoreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; //이 액터는 리플리케이션을 한다
	SetReplicateMovement(true); // 이 액터의 무브먼트 컴포넌트는 리플리케이션이 된다.

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(40.0f);
	SetRootComponent(Collision);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AScoreActor::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AScoreActor::OnOverlapBegin);

}


void AScoreActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//HasAuthority() &&
	if (OtherActor && OtherActor != this)
	{
		if (!bIsOverlap)
		{
			UE_LOG(LogTemp, Log, TEXT("획득"));
			bIsOverlap = true;
			APlayerStateCharacter* PSC = Cast<APlayerStateCharacter>(OtherActor);

			if (PSC)
			{
				PSC->TestAddScore();
			}
			Destroy();
		}
	}
}