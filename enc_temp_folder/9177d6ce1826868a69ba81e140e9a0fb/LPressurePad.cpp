// Fill out your copyright notice in the Description page of Project Settings.


#include "LPressurePad.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "LMovingPlatform.h"

ALPressurePad::ALPressurePad()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

	PressurePadMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PressurePadMesh"));

	if (!ensure(TriggerVolume != nullptr)) return;
	
	RootComponent = TriggerVolume;

	PressurePadMesh->SetupAttachment(RootComponent);

	TriggerVolume->SetBoxExtent(FVector(50, 50, 100));

}

void ALPressurePad::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ALPressurePad::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ALPressurePad::OnOverlapEnd);
	
}

void ALPressurePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALPressurePad::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Trigger activated"));

	for (int i = 0; i < PlatformsToTrigger.Num(); i++)
	{
		if (PlatformsToTrigger[i])
			PlatformsToTrigger[i]->AddActiveTrigger();
	}
}

void ALPressurePad::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("Trigger deactivated"));

	for (int i = 0; i < PlatformsToTrigger.Num(); i++)
	{
		if (PlatformsToTrigger[i])
			PlatformsToTrigger[i]->RemoveActiveTrigger();
	}
}

