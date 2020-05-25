// Fill out your copyright notice in the Description page of Project Settings.


#include "LMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool ULMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (HostButton)
		HostButton->OnClicked.AddDynamic(this, &ULMainMenu::HostGame);
	if(JoinMenuButton)
		JoinMenuButton->OnClicked.AddDynamic(this, &ULMainMenu::OpenJoinMenu);
	if (CancelJoinButton)
		CancelJoinButton->OnClicked.AddDynamic(this, &ULMainMenu::BackToMainMenu);
	if (JoinGameButton)
		JoinGameButton->OnClicked.AddDynamic(this, &ULMainMenu::JoinGame);

	return true;
}

void ULMainMenu::HostGame()
{
	// normal way
	//ULPuzzlePlatformsGameInstance* GI = Cast<ULPuzzlePlatformsGameInstance>(GetGameInstance());
	//if (GI)
	//{
	//	GI->Host(); 
	//}

	// interface way
	if (MenuInterface)
	{
		MenuInterface->Host();
	}

}

void ULMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher && JoinMenu)
		MenuSwitcher->SetActiveWidget(JoinMenu);
}
void ULMainMenu::JoinGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Joining a game..."));
	if (JoinIP_AddressTextBox && MenuInterface)
	{
		FText IP_Address = JoinIP_AddressTextBox->GetText();
		MenuInterface->Join(IP_Address.ToString());
		//Teardown(); called in game instance
	}

}

void ULMainMenu::BackToMainMenu()
{
	if (MenuSwitcher && MainMenu)
		MenuSwitcher->SetActiveWidget(MainMenu);
}

void ULMainMenu::SetMenuInterface(ILMenuInterface* MenuInterfac)
{
	this->MenuInterface = MenuInterfac;
}

void ULMainMenu::Setup()
{
	this->AddToViewport();
	this->bIsFocusable = true;

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		FInputModeUIOnly InputData;

		InputData.SetWidgetToFocus(this->TakeWidget());
		InputData.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);

		PC->SetInputMode(InputData);
		PC->bShowMouseCursor = true;
	}
}

void ULMainMenu::Teardown()
{
	this->RemoveFromViewport();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}
}
