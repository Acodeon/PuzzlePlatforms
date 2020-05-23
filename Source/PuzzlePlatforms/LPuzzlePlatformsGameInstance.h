// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/LMenuInterface.h"
#include "LPuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ULPuzzlePlatformsGameInstance : public UGameInstance, public ILMenuInterface
{
	GENERATED_BODY()

public:

	ULPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);

	void Init() override;

protected:

	TSubclassOf<UUserWidget> MenuClass;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(FString Address);
	
};
