// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ULServerRow : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	class UButton* ServerRowButton;

	void Setup(class ULMainMenu* InParent, uint32 InIndex);

protected:

	UFUNCTION()
	void OnClicked();

	UPROPERTY()
	class ULMainMenu* Parent;

	uint32 Index;
	
};
