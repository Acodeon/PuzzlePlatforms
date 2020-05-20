// Fill out your copyright notice in the Description page of Project Settings.


#include "LPuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"

void ULPuzzlePlatformsGameInstance::Host()
{
	UEngine* engine = GetEngine();
	if (engine)
	{
		engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Hosting"));
	}

	GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void ULPuzzlePlatformsGameInstance::Join(FString Address)
{
	UEngine* engine = GetEngine();
	if (engine)
	{
		FString printString = "Joining " + Address;
		engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, printString);
	}

	APlayerController* PC = GetFirstLocalPlayerController();
	if (PC)
	{
		PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}
