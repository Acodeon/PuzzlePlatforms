// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/LMenuInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
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

	TSubclassOf<UUserWidget> InGameMenuClass;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	class ULMainMenu* Menu;
	
	class ULInGameMenu* InGameMenu;

	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(uint32 Index);

	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionComplete(bool Success);

	void OnJoinSessionComplete(FName JoinName, EOnJoinSessionCompleteResult::Type REsult);

	void CreateSession();

public:

	UFUNCTION()
		void LoadInGameMenu();

	void RefreshServerList() override;

	
};
