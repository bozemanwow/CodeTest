// Fill out your copyright notice in the Description page of Project Settings.


#include "LeverActor.h"
#include "TimerManager.h"
#include "SpinActor.h"
#include "Components/TextRenderComponent.h"
// Sets default values
ALeverActor::ALeverActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALeverActor::BeginPlay()
{
	Super::BeginPlay();
	ScoreText = TextActor->FindComponentByClass<UTextRenderComponent>();
	ScoreText->SetTextRenderColor(FColor::Red);
}

// Called every frame
void ALeverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bool IsSwitch = Timer > GetGameTimeSinceCreation();
	Spinner->SetReVerse(IsSwitch);
	this->SetActorRotation(IsSwitch ? RotOn : RotOff, ETeleportType::TeleportPhysics);	
}



void ALeverActor::LeverClickDown(float MouseX)
{
	MouseXPos = MouseX;
}

bool ALeverActor::LeverClickUp(float MouseX)
{
	if (MouseX > MouseXPos)
	{
	 Timer = TimerLength + GetGameTimeSinceCreation();
	 return true;
	}
	return false;
}
void ALeverActor::ResetVal()
{
	Timer = 0;
	this->SetActorRotation( RotOff, ETeleportType::TeleportPhysics);
	SetText(0);
}

void ALeverActor::SetText(int8 num)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(num)));
}