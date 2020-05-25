// Fill out your copyright notice in the Description page of Project Settings.


#include "LInGameMenu.h"
#include "Components/Button.h"

bool ULInGameMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (ResumeButton)
		ResumeButton->OnClicked.AddDynamic(this, &ULInGameMenu::ResumeGame);
	if (ExitMainMenuButton)
		ExitMainMenuButton->OnClicked.AddDynamic(this, &ULInGameMenu::ExitToMainMenu);

	return true;
}

void ULInGameMenu::ResumeGame()
{
	this->RemoveFromViewport();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}
}

void ULInGameMenu::ExitToMainMenu()
{
	this->RemoveFromViewport();

	//GetWorld()->ServerTravel("/Game/Maps/MainMenu");

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
	}
		
}
