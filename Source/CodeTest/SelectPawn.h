// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SelectPawn.generated.h"

UCLASS()
class CODETEST_API ASelectPawn : public APawn
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere)
	APlayerController* PC;
	AActor* PrevDetection;

	UPROPERTY(EditAnywhere)
		class AButtonCounterActor* LeftButton;
	UPROPERTY(EditAnywhere)
		class ALeverActor* Lever;
	UPROPERTY(EditAnywhere)
		class ASpinActor* Spiner;

	bool Clicking = false;

	// Sets default values for this pawn's properties
	ASelectPawn();


protected:
	int8 LeftButtonCount = 0;
	int8 LeverCount = 0;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void CursorCheckOver();
	void CheckClickDown();
	void CheckClickUp();
	void GetMousePostion(FVector& Start, FVector& End);
	bool DoCursorCheck(FHitResult& HitResult);
	void ResetControls();
};
