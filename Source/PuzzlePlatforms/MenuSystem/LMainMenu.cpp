// Fill out your copyright notice in the Description page of Project Settings.


#include "LMainMenu.h"
#include "Components/Button.h"

bool ULMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!Host || !Join) return false;
		
	Host->OnClicked.AddDynamic(this, &ULMainMenu::HostGame);
	Join->OnClicked.AddDynamic(this, &ULMainMenu::JoinGame);

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

void ULMainMenu::JoinGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Joining a game..."));
}

void ULMainMenu::SetMenuInterface(ILMenuInterface* MenuInterfac)
{
	this->MenuInterface = MenuInterfac;
}
