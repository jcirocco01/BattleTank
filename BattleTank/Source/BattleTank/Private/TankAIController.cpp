// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerPawn = GetPlayerTank();
		if (!PlayerPawn) {
		UE_LOG(LogTemp, Warning, TEXT("No player found"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank: %s"), *(PlayerPawn->GetName()))
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{ //TODO move towards player
	
	//aim towards player
		GetAITank()->AimAt(GetPlayerTank()->GetActorLocation());

	//TODO fire projectile
	}
}

ATank * ATankAIController::GetAITank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) { return nullptr; }
	return Cast<ATank>(PlayerTank);
}

void ATankAIController::AimAt(FVector HitLocation)
{

}