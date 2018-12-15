// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
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
