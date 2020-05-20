// Fill out your copyright notice in the Description page of Project Settings.


#include "LMovingPlatform.h"

ALMovingPlatform::ALMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void ALMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

}

void ALMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds); 

	if (HasAuthority() && ActiveTriggers > 0)
	{
		FVector ActorLocation = GetActorLocation();
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (ActorLocation - GlobalStartLocation).Size();
		if (JourneyTravelled >= JourneyLength)
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		ActorLocation += Speed * DeltaSeconds * Direction;
		SetActorLocation(ActorLocation);
	}
}

void ALMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void ALMovingPlatform::RemoveActiveTrigger()
{
	if(ActiveTriggers > 0)
		ActiveTriggers--;
}
