// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController/PlayerCharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"


APlayerCharacterController::APlayerCharacterController()
{
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Look);
	}
}
void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APlayerCharacterController::Move(const FInputActionValue& Value)
{
	FVector2D MoveAxisVector = Value.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn())
	{
		const FRotator YawRotation(0, GetControlRotation().Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		ControlledPawn->AddMovementInput(ForwardDirection, MoveAxisVector.X);
		ControlledPawn->AddMovementInput(RightDirection, MoveAxisVector.Y);
	}
}

void APlayerCharacterController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}
