// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "ButtonCounterActor.h"
#include "Components/TextRenderComponent.h"
#include "LeverActor.h"
#include "Misc/MessageDialog.h"
#include "SpinActor.h"
#include "EngineUtils.h"
// Sets default values
ASelectPawn::ASelectPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASelectPawn::BeginPlay()
{
	Super::BeginPlay();
	PrevDetection = nullptr;

	PC = Cast<APlayerController>(GetController());
	
	for (TActorIterator<AButtonCounterActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName() == "Button")
		{
			LeftButton = *ActorItr;
			break;
		}
	}
	for (TActorIterator<ALeverActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName() == "Lever")
		{
			Lever = *ActorItr;
			break;
		}
	}
	for (TActorIterator<ASpinActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName() == "Spinner")
		{
			Spiner = *ActorItr;
			break;
		}
	}
	//ScoreText = CreateDefaultSubobject<UTextRenderComponent>(FName("ScoreText0"));
	//ScoreText->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	//ScoreText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	//ScoreText->SetText(FText::AsNumber(0));
	//ScoreText->SetupAttachment(this);

}

// Called every frame
void ASelectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CursorCheckOver();

}

// Called to bind functionality to input
void ASelectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ASelectPawn::CheckClickDown);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ASelectPawn::CheckClickUp);
}

void ASelectPawn::CheckClickUp()
{
	Clicking = false;
	if (AButtonCounterActor* Ui = Cast<AButtonCounterActor>(PrevDetection))
	{


		Ui->LeftButtonClickUp();
		Ui->SetText(++LeftButtonCount);
	}
	else if (ALeverActor* Lever = Cast<ALeverActor>(PrevDetection))
	{
		float Mousex, Mousey;
		PC->GetMousePosition(Mousex, Mousey);
		if (Lever->LeverClickUp(Mousex))
			Lever->SetText(++LeverCount);
	}
	if (LeftButtonCount + LeverCount >= 10)
	{
		FMessageDialog F;
		//EAppMsgType::Type MessageType, EAppReturnType::Type DefaultValue, const FText& Message, const FText* OptTitle = nullptr
		FText t = FText::FromString(("Continue?"));
		EAppReturnType::Type val = F.Open(EAppMsgType::Type::YesNo, EAppReturnType::Yes, t, nullptr);
		if (val == EAppReturnType::Yes)
		{
			ResetControls();
		}
	}
}
void ASelectPawn::CheckClickDown()
{

	FHitResult HitResult;
	if (DoCursorCheck(HitResult))
	{
		Clicking = true;
		if (AButtonCounterActor* Ui = Cast<AButtonCounterActor>(PrevDetection))
		{
			Ui->LeftButtonClickDown();
		}
		else if (ALeverActor* Lev = Cast<ALeverActor>(PrevDetection))
		{
			UE_LOG(LogTemp, Warning, TEXT("Lever"));
			float Mousex, Mousey;
			PC->GetMousePosition(Mousex, Mousey);
			Lev->LeverClickDown(Mousex);
		}
	}
}
void ASelectPawn::CursorCheckOver()
{

	FHitResult HitResult;
	if (DoCursorCheck(HitResult))
	{
		// If Somthing is Hit
		if (HitResult.Actor.IsValid())
		{
			if (PrevDetection != Cast<AActor>(HitResult.Actor.Get()))
			{
				if (AButtonCounterActor* Ui = Cast<AButtonCounterActor>(HitResult.Actor.Get()))
				{
					Ui->LeftButtonOverBegin();
				}
				PrevDetection = Cast<AActor>(HitResult.Actor.Get());
			}
			else
			{
				if (AButtonCounterActor* Ui = Cast<AButtonCounterActor>(PrevDetection))
				{
					Ui->OnHighLight();
				}
			}


		}


	}
	else if (PrevDetection != nullptr)
	{
		if (AButtonCounterActor* Ui = Cast<AButtonCounterActor>(PrevDetection))
		{
			if (!Clicking)
			{
				PrevDetection = nullptr;
				Ui->LeftButtonOverEnd();
			}
			else
				Ui->OffHighLight();

		}
	}


}
void ASelectPawn::GetMousePostion(FVector& Start, FVector& End)
{
	FVector Dir;
	PC->DeprojectMousePositionToWorld(Start, Dir);
	float Dis = 4000.0f;
	End = Start + (Dir * Dis);
}

bool  ASelectPawn::DoCursorCheck(FHitResult& HitResult)
{
	FVector Start, End;
	GetMousePostion(Start, End);
	return (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility));
}
void ASelectPawn::ResetControls()
{
	LeftButtonCount = LeverCount = 0;

	LeftButton->ResetVal();

	Lever->ResetVal();

	Spiner->ResetVal();

}