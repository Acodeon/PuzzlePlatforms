// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LMenuInterface.h"
#include "LMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ULMainMenu : public UUserWidget
{
	GENERATED_BODY()


protected:

	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* JoinIP_AddressTextBox;

	UFUNCTION()
	void HostGame();
	
	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void JoinGame();

	UFUNCTION()
	void BackToMainMenu();

	ILMenuInterface* MenuInterface;

public:

	void SetMenuInterface(ILMenuInterface* MenuInterfac);

	void Setup();

	void Teardown();
	
};
