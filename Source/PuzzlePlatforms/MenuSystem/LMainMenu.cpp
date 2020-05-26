// Fill out your copyright notice in the Description page of Project Settings.


#include "LMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "UObject/ConstructorHelpers.h"
#include "LServerRow.h"
#include "Components/TextBlock.h"



ULMainMenu::ULMainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowClassBP(TEXT("/Game/Menu/WB_ServerRow"));
	ServerRowClass = ServerRowClassBP.Class;
}

void ULMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
}

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
	if (MenuInterface)
		MenuInterface->RefreshServerList();
}

void ULMainMenu::JoinGame()
{
	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index %d"), SelectedIndex.GetValue());
		if (MenuInterface)
		{
			//FText IP_Address = JoinIP_AddressTextBox->GetText();
			MenuInterface->Join(SelectedIndex.GetValue());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index not set"));
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

void ULMainMenu::SetServerList(TArray<FString> ServerNames)
{
	ServerList->ClearChildren();

	if (ServerRowClass)
	{
		uint32 i = 0;
		for (const FString& ServerName : ServerNames)
		{
			ULServerRow* Row = CreateWidget<ULServerRow>(this, ServerRowClass);
			if (Row)
			{
				Row->ServerName->SetText(FText::FromString(ServerName));
				Row->Setup(this, i);
				i++;
				ServerList->AddChild(Row);
			}
		}
		

	}
}
