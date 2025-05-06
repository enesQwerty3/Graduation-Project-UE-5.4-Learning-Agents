// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpectatorCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class ALearningAgentProjectCharacter;

UCLASS()
class LEARNINGAGENTPROJECT_API ASpectatorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpectatorCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "NN Run Training")
	bool runTraining = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NN Run Inference")
	bool runInference = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NN Reset Total Training Time")
	bool resetTotalTrainingTime = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:
	UPROPERTY(EditAnywhere, Category = "INPUT MAPPING CONTEXT")
	UInputMappingContext* InputMappingContext = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* Camera = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "INPUT ACTION")
	UInputAction* EnableCursorAction = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "INPUT ACTION")
	UInputAction* SelectObjectAction = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "INPUT ACTION")
	UInputAction* PlaceObjectAction = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "INPUT ACTION")
	UInputAction* LookAction = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "INPUT ACTION")
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, Category = "INPUT ACTION")
	UInputAction* RunTrainingAction = nullptr;

	UPROPERTY(EditAnywhere, Category = "INPUT ACTION")
	UInputAction* RunInferenceAction = nullptr;

	UPROPERTY(EditAnywhere, Category = "INPUT ACTION")
	UInputAction* ResetTotalTrainingTimeAction = nullptr;

	bool cursorEnabled = false;
	
	bool possesed = false;

	APlayerController* PlayerController = nullptr;

	UPROPERTY(EditAnywhere, Category = "BPThirdPersonCharacter")
	ALearningAgentProjectCharacter* BPThirdPersonCharacter = nullptr;
	
	UFUNCTION()
	void EnableCursor(const FInputActionValue& value);
	UFUNCTION()
	void SelectObjectWithCursor(const FInputActionValue& value);
	UFUNCTION()
	void PlaceObject(const FInputActionValue& value);
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	
	UFUNCTION()
	void RunTraining(const FInputActionValue& value);

	UFUNCTION()
	void RunInference(const FInputActionValue& value);

	UFUNCTION()
	void ResetTotalTrainingTime(const FInputActionValue& value);
};
