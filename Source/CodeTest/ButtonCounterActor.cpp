// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonCounterActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"
#include "SpinActor.h"
#include "Components/TextRenderComponent.h"
// Sets default values
AButtonCounterActor::AButtonCounterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AButtonCounterActor::BeginPlay()
{
	Super::BeginPlay();
	LeftButtonMesh = this->FindComponentByClass<UStaticMeshComponent>(); //CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	LeftButtonMesh->SetMaterial(0, OverOffMaterial);
	ScoreText = TextActor->FindComponentByClass<UTextRenderComponent>();
	ScoreText->SetTextRenderColor(FColor::Red);
}


void AButtonCounterActor::LeftButtonClickDown()
{
	LeftButtonMesh->SetMaterial(0, ClickMaterial);
	IsClicking = true;
}

void AButtonCounterActor::LeftButtonClickUp()
{
	if (IsOver)
	{
		LeftButtonMesh->SetMaterial(0, OverOnMaterial);
		Spinner->SetSpin();
		Count++;
	}
	else
		LeftButtonMesh->SetMaterial(0, OverOffMaterial);
	IsClicking = false;
}

void AButtonCounterActor::LeftButtonOverBegin()
{
	IsOver = true;
	if (!IsClicking)
	{
		LeftButtonMesh->SetMaterial(0, OverOnMaterial);
	}
	else
		LeftButtonMesh->SetMaterial(0, ClickMaterial);
}

void AButtonCounterActor::LeftButtonOverEnd()
{
	IsOver = false;
	if (!IsClicking)
	{
		LeftButtonMesh->SetMaterial(0, OverOffMaterial);
	}
	else
		LeftButtonMesh->SetMaterial(0, OverOnMaterial);
}

void AButtonCounterActor::OnHighLight()
{
	if (!IsClicking)
	{
		LeftButtonMesh->SetMaterial(0, OverOnMaterial);
	}
	else
		LeftButtonMesh->SetMaterial(0, ClickMaterial);
}

void AButtonCounterActor::OffHighLight()
{
	if (!IsClicking)
	{
		LeftButtonMesh->SetMaterial(0, OverOffMaterial);
	}
	else
		LeftButtonMesh->SetMaterial(0, OverOnMaterial);
}

void AButtonCounterActor::SetText(int8 num)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(num)));
}

void AButtonCounterActor::ResetVal()
{
	IsOver = IsClicking = false;
	LeftButtonMesh->SetMaterial(0, OverOffMaterial);
	SetText(0);
}

