// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeverActor.generated.h"

UCLASS()
class CODETEST_API ALeverActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class AActor* TextActor;
	UPROPERTY(EditAnywhere)
		class ASpinActor* Spinner;
	UPROPERTY(EditAnywhere)
		FQuat RotOff;
	UPROPERTY(EditAnywhere)
		FQuat RotOn;
private:
	class UTextRenderComponent* ScoreText;
	float MouseXPos;
	float Timer = 0.0f;
	float TimerLength = 5.0f;
	bool FlipUp = false;
public:
	// Sets default values for this actor's properties
	ALeverActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LeverClickDown(float MouseX);
	bool LeverClickUp(float MouseX);
	void ResetVal();
	void SetText(int8 num);
};
