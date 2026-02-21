// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class LISTENSERVERTUTORIAL_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	APlayerCharacterController();
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
};
