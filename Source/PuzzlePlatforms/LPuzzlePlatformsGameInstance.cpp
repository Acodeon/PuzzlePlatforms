// Fill out your copyright notice in the Description page of Project Settings.


#include "LPuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "LPressurePad.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/LMainMenu.h"
#include "MenuSystem/LInGameMenu.h"


ULPuzzlePlatformsGameInstance::ULPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuClassBP(TEXT("/Game/Menu/WB_MainMenu"));
	MenuClass = MenuClassBP.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuClassBP(TEXT("/Game/Menu/WB_InGameMenu"));
	InGameMenuClass = InGameMenuClassBP.Class;

}

void ULPuzzlePlatformsGameInstance::Init()
{
	if (MenuClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Found class %s"), *MenuClass->GetName());
	}
}

void ULPuzzlePlatformsGameInstance::LoadMenu()
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

void ULPuzzlePlatformsGameInstance::Host()
{
	UEngine* engine = GetEngine();
	if (engine)
	{
		engine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Hosting"));
	}

	if (Menu)
	{
		Menu->Teardown();
	}

	GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void ULPuzzlePlatformsGameInstance::Join(FString Address)
{
	if (Menu)
	{
		Menu->Teardown();
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
