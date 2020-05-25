// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LInGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ULInGameMenu : public UUserWidget
{
	GENERATED_BODY()


protected:

	virtual bool Initialize() override;
		
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitMainMenuButton;

	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void ExitToMainMenu();

	
};
