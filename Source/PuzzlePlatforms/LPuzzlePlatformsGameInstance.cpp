// Fill out your copyright notice in the Description page of Project Settings.


#include "LPuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "LPressurePad.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/LMainMenu.h"
#include "MenuSystem/LInGameMenu.h"
#include "OnlineSessionSettings.h"


const static FName SESSION_NAME = TEXT("My session name");

ULPuzzlePlatformsGameInstance::ULPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuClassBP(TEXT("/Game/Menu/WB_MainMenu"));
	MenuClass = MenuClassBP.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuClassBP(TEXT("/Game/Menu/WB_InGameMenu"));
	InGameMenuClass = InGameMenuClassBP.Class;

}

void ULPuzzlePlatformsGameInstance::Init()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Online subsystem is valid. %s"), *OnlineSubsystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface)
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &ULPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &ULPuzzlePlatformsGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &ULPuzzlePlatformsGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &ULPuzzlePlatformsGameInstance::OnJoinSessionComplete);

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Online subsystem is nullptr"));
	}
}

void ULPuzzlePlatformsGameInstance::LoadMenuWidget()
{
	if (MenuClass)
	{
		Menu = CreateWidget<ULMainMenu>(this, MenuClass);
		if (Menu)
		{
			Menu->Setup();
			Menu->SetMenuInterface(this);
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("ManuClass is nullptr!"));
}

void ULPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	if (InGameMenuClass)
	{
		InGameMenu = CreateWidget<ULInGameMenu>(this, InGameMenuClass);
		if (InGameMenu)
		{
			InGameMenu->AddToViewport();
			InGameMenu->bIsFocusable = true;

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				FInputModeUIOnly InputData;

				InputData.SetWidgetToFocus(InGameMenu->TakeWidget());
				InputData.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);

				PC->SetInputMode(InputData);
				PC->bShowMouseCursor = true;
			}
		}
	}
}

void ULPuzzlePlatformsGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch)
	{
		SessionSearch->bIsLanQuery = true;
		UE_LOG(LogTemp, Warning, TEXT("Starting find session"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void ULPuzzlePlatformsGameInstance::Host()
{
	if (SessionInterface)
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);

		if (ExistingSession)
			SessionInterface->DestroySession(SESSION_NAME); 
		else
			CreateSession();

	}
}

void ULPuzzlePlatformsGameInstance::Join(uint32 Index)
{
	if (!SessionInterface || !SessionSearch) return;

	if (Menu)
	{
		Menu->Teardown();
	}

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);


}

void ULPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success) return;
	UEngine* engine = GetEngine();
	if (engine)
	{
		engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Hosting..."));
	}

	if (Menu)
	{
		Menu->Teardown();
	}

	GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void ULPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
		CreateSession();
}

void ULPuzzlePlatformsGameInstance::OnFindSessionComplete(bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("Find session complete"));
	if (Success && SessionSearch && Menu)
	{
		TArray<FString> ServerNames;
		for (const FOnlineSessionSearchResult& result : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *result.GetSessionIdStr());
			ServerNames.Add(result.GetSessionIdStr());
		}

		Menu->SetServerList(ServerNames);
	}
}

void ULPuzzlePlatformsGameInstance::OnJoinSessionComplete(FName JoinName, EOnJoinSessionCompleteResult::Type REsult)
{

	if (REsult != EOnJoinSessionCompleteResult::Success || !SessionInterface) return;

	FString Address;
	if (!SessionInterface->GetResolvedConnectString(JoinName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get resolve string"));
		return;
	}

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

void ULPuzzlePlatformsGameInstance::CreateSession()
{
	if (SessionInterface)
	{
		//FOnlineSessionSetting SessionSettings;
		FOnlineSessionSettings NewSessionSettings = FOnlineSessionSettings();
		NewSessionSettings.bIsLANMatch = true;
		NewSessionSettings.NumPublicConnections = 2;
		NewSessionSettings.bShouldAdvertise = true;
		SessionInterface->CreateSession(0, SESSION_NAME, NewSessionSettings);
	}
}
