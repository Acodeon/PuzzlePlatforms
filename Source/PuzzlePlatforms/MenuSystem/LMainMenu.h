// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LMenuInterface.h"
#include "LMainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;

	uint16 CurrentPlayers;

	uint16 MaxPlayers;

	FString HostUserName;

};

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ULMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	ULMainMenu(const FObjectInitializer& ObjectInitializer);

	void SelectIndex(uint32 Index);

protected:

	virtual bool Initialize() override;

	TSubclassOf<UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelHostButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* ServerNameTextBox;

	UFUNCTION()
	void HostGame();
	
	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenHostMenu();

	UFUNCTION()
	void JoinGame();

	UFUNCTION()
	void BackToMainMenu();

	void UpdateChildren();

	ILMenuInterface* MenuInterface;

	TOptional<uint32> SelectedIndex;

public:

	void SetMenuInterface(ILMenuInterface* MenuInterfac);

	void Setup();

	void Teardown();

	void SetServerList(TArray<FServerData> ServerNames);

	FName GetServerName();
	
};
