// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinActor.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ASpinActor::ASpinActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpinActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpinActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsSpinning)
		this->AddActorLocalRotation(FQuat(Speed * DeltaTime * IsReVersed, 0, 0, 1));
}

void ASpinActor::SetReVerse(bool val)
{
	if (val)
		IsReVersed = -1;
	else
		IsReVersed = 1;
}
void ASpinActor::SetSpin()
{
	IsSpinning = !IsSpinning;
}
void  ASpinActor::ResetVal()
{
	IsReVersed = 1;
	IsSpinning = false;
	this->SetActorRotation(FQuat(0, 0, 0, 1), ETeleportType::TeleportPhysics);
}