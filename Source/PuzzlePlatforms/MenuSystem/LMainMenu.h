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
	class UButton* Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UFUNCTION()
	void HostGame();
	
	UFUNCTION()
	void JoinGame();

	ILMenuInterface* MenuInterface;

public:

	void SetMenuInterface(ILMenuInterface* MenuInterfac);
	
};
