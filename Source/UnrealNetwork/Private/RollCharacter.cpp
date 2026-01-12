// Fill out your copyright notice in the Description page of Project Settings.


#include "RollCharacter.h"
void ARollCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FString LocalRoleStrig = UEnum::GetValueAsString(GetLocalRole());
	const FString RemoteRoleStrig = UEnum::GetValueAsString(GetRemoteRole());

	const FString OwnerString = GetOwner() ? GetOwner()->GetName() : TEXT("오너 없음");
	const FString ConnectionString = GetNetConnection() ? TEXT("커넥션 있음") : TEXT("커넥션 없음");
	
	const FString Value = 
		FString::Printf(TEXT("LocalRole : %s / RemoteRole : %s \n Owner : %s \n Connection : %s")
			,*LocalRoleStrig, *RemoteRoleStrig, *OwnerString, *ConnectionString);
	DrawDebugString(GetWorld(), GetActorLocation(), Value, nullptr, FColor::White, 0.0f, true);


}
