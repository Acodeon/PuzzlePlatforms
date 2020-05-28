// Fill out your copyright notice in the Description page of Project Settings.


#include "LLobbyGameMode.h"
#include "TimerManager.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "LPuzzlePlatformsGameInstance.h"

void ALLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	NumberOfPlayers++;
	if(NumberOfPlayers >= 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("There are 3 players joined! Starting count off..."));
		GetWorldTimerManager().SetTimer(TH_StartGame, this, &ALLobbyGameMode::StartGame, 10.0f, false, 10.0f);

	}
}

void ALLobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if(NumberOfPlayers > 0)
		NumberOfPlayers--;
}

void ALLobbyGameMode::StartGame()
{
	GetWorldTimerManager().ClearTimer(TH_StartGame);

	ULPuzzlePlatformsGameInstance* GI = Cast<ULPuzzlePlatformsGameInstance>(GetGameInstance());
	if (GI)
	{
		GI->StartSession();
	}

	bUseSeamlessTravel = true;
	GetWorld()->ServerTravel("/Game/Maps/Game?listen");
}
