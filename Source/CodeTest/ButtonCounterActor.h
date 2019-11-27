// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonCounterActor.generated.h"

UCLASS()
class CODETEST_API AButtonCounterActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	class AActor* TextActor;

	UPROPERTY(EditAnywhere)
		class ASpinActor* Spinner;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* LeftButtonMesh;

	UPROPERTY(EditAnywhere)
		class  UMaterialInterface* OverOnMaterial;

	UPROPERTY(EditAnywhere)
		class  UMaterialInterface* OverOffMaterial;

	UPROPERTY(EditAnywhere)
		class UMaterialInterface* ClickMaterial;

	class UTextRenderComponent* ScoreText;
	bool IsOver = false;
	bool IsClicking = false;
	int Count = 0;

public:	
	// Sets default values for this actor's properties
	AButtonCounterActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void LeftButtonClickDown();
	void LeftButtonClickUp();
	void LeftButtonOverBegin();
	void LeftButtonOverEnd();
	void OnHighLight();
	void OffHighLight();
	void SetText(int8 num);
	void ResetVal();
};
