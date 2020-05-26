// Fill out your copyright notice in the Description page of Project Settings.


#include "LServerRow.h"
#include "Components/Button.h"
#include "LMainMenu.h"

void ULServerRow::Setup(class ULMainMenu* InParent, uint32 InIndex)
{
	if (ServerRowButton)
		ServerRowButton->OnClicked.AddDynamic(this, &ULServerRow::OnClicked);

	Parent = InParent;
	Index = InIndex;

}

void ULServerRow::OnClicked()
{
	if (Parent)
		Parent->SelectIndex(Index);
}
