// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RPCCharacter.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
ARPCCharacter::ARPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FireLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FireLocation"));
	FireLocation->SetupAttachment(GetMesh(), TEXT("Fire"));
}


// Called when the game starts or when spawned
void ARPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARPCCharacter::Client_OnHit_Implementation()
{
	FString RoleName = HasAuthority() ? TEXT("Server") : TEXT("Client");
	FString ControllerName = GetController() ? GetController()->GetName() : TEXT("NoController");

	GEngine->AddOnScreenDebugMessage(
		-1, 5.0f, FColor::Red,
		FString::Printf(TEXT("[%s] %s : 내가 맞았음"), *RoleName, *ControllerName)
	);

	APlayerController* PC = Cast<APlayerController>(GetController());
	PC->ClientStartCameraShake(CameraShakeClass);
}

void ARPCCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HasAuthority())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("맞았음"));	
		//APlayerController* PC = Cast<APlayerController>(GetController());
		//GEngine->AddOnScreenDebugMessage(
		//	-1, 5.0f, FColor::Yellow,
		//	FString::Printf(TEXT("Contoller: %s"), PC ? *PC->GetName() : TEXT("null")));
		//GEngine->AddOnScreenDebugMessage(
		//	-1, 5.0f, FColor::Yellow,
		//	FString::Printf(TEXT("Owner: %s"), GetOwner() ? *GetOwner()->GetName() : TEXT("null")));
		//GEngine->AddOnScreenDebugMessage(
		//	-1, 5.0f, FColor::Yellow,
		//	FString::Printf(TEXT("Connection: %s"), GetNetConnection() ? TEXT("O") : TEXT("X")));

		Client_OnHit();	// ClientRPC로 호출
		//Client_OnHit_Implementation(); // 그냥 호출해서 로컬 실행
	}
}

void ARPCCharacter::Fire()
{
	if (IsLocallyControlled())// 내가 조종하는 캐릭터다
	{
		Sever_Fire();
	}
}

void ARPCCharacter::Sever_Fire_Implementation()
{
	//서버가 실행하는 코드
	if (ProjectileCLass)
	{
		FVector SpawnLocation = FireLocation->GetComponentLocation();
		FRotator SpawnRotation = FireLocation->GetComponentRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(ProjectileCLass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}

