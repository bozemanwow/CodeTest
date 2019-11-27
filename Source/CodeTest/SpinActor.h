// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpinActor.generated.h"

UCLASS()
class CODETEST_API ASpinActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)

		float IsReVersed = 1;
	bool IsSpinning = false;
	float Speed = 4.0f;
public:

	// Sets default values for this actor's properties
	ASpinActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetReVerse(bool val);
	void SetSpin();
	void ResetVal();
};
