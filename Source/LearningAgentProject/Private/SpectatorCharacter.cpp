// Fill out your copyright notice in the Description page of Project Settings.
#include "SpectatorCharacter.h"

//EnhancedInput
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

//Camera and SpringArm component
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

//UCharacterMovementComponent
#include "GameFramework/CharacterMovementComponent.h"	 

//UCapsuleComponent
#include "Components/CapsuleComponent.h"

//GameplayStatics
#include "Kismet/GameplayStatics.h"

#include "LearningAgentProject//LearningAgentProjectCharacter.h"

// Sets default values
ASpectatorCharacter::ASpectatorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//controller rotation
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	
	//movement speed
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void ASpectatorCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Set player controller
	if (!GetController()) {
		SpawnDefaultController();
	}

	PlayerController = CastChecked<APlayerController>(GetController());

	if (PlayerController) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(InputMappingContext, 0);	//add InputMappingContext field to enhanced input player subsystem
		}
	}
	//set actor movement mode to flying
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;
	if (UGameplayStatics::GetActorOfClass(GetWorld(), ALearningAgentProjectCharacter::StaticClass())) {
		BPThirdPersonCharacter = CastChecked<ALearningAgentProjectCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ALearningAgentProjectCharacter::StaticClass()));
	}
}


// Called every frame
void ASpectatorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (cursorEnabled) {
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);
		FVector hitLocation = HitResult.Location;
		DrawDebugSphere(GetWorld(), hitLocation, 50.f, 24, FColor::Emerald);
	}
}

// Called to bind functionality to input
void ASpectatorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInput->BindAction(SelectObjectAction, ETriggerEvent::Triggered, this, &ASpectatorCharacter::SelectObjectWithCursor);
		EnhancedInput->BindAction(EnableCursorAction, ETriggerEvent::Triggered, this, &ASpectatorCharacter::EnableCursor);
		EnhancedInput->BindAction(PlaceObjectAction, ETriggerEvent::Triggered, this, &ASpectatorCharacter::PlaceObject);
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpectatorCharacter::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASpectatorCharacter::Look);
		EnhancedInput->BindAction(RunTrainingAction, ETriggerEvent::Triggered, this, &ASpectatorCharacter::RunTraining);
		EnhancedInput->BindAction(RunInferenceAction, ETriggerEvent::Triggered, this, &ASpectatorCharacter::RunInference);
		EnhancedInput->BindAction(ResetTotalTrainingTimeAction, ETriggerEvent::Triggered, this, &ASpectatorCharacter::ResetTotalTrainingTime);
		EnhancedInput->BindAction(ResetTotalTrainingTimeAction, ETriggerEvent::Completed, this, &ASpectatorCharacter::ResetTotalTrainingTime);
	}
}


void ASpectatorCharacter::Move(const FInputActionValue& value) {
	if (GetController() && !cursorEnabled) {
		FVector2D MovementInput = value.Get<FInputActionValue::Axis2D>();
		AddMovementInput(GetActorForwardVector(), MovementInput.Y);
		AddMovementInput(GetActorRightVector(), MovementInput.X);
		
	}
}

void ASpectatorCharacter::Look(const FInputActionValue& value)
{
	if (GetController()) {
		FVector2D MouseMovement = value.Get<FInputActionValue::Axis2D>();
		AddControllerYawInput(MouseMovement.X);
		AddControllerPitchInput(MouseMovement.Y);
	}
}

void ASpectatorCharacter::EnableCursor(const FInputActionValue& value)
{
	if (value.Get<bool>()) {
		if (cursorEnabled) {
			PlayerController->SetShowMouseCursor(false);
			PlayerController->SetInputMode(FInputModeGameOnly());
			cursorEnabled = false;
		}

		else {
			PlayerController->SetShowMouseCursor(true);
			PlayerController->SetInputMode(FInputModeGameAndUI());
			cursorEnabled = true;
		}
	}
}

void ASpectatorCharacter::SelectObjectWithCursor(const FInputActionValue& value)
{

}

void ASpectatorCharacter::PlaceObject(const FInputActionValue& value)
{
	if (GetController() && cursorEnabled) {
		FHitResult HitResult = FHitResult();
		PlayerController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);
		FVector hitLocation = HitResult.Location;
		if (BPThirdPersonCharacter) {
			BPThirdPersonCharacter->SetActorLocation(hitLocation);
		}
	}
}


void ASpectatorCharacter::RunTraining(const FInputActionValue& value)
{
	if (GetController()) {
		if(runTraining)
			runTraining = false;
		else
			runTraining = true;
		runInference = false;
	}
}

void ASpectatorCharacter::RunInference(const FInputActionValue& value)
{
	if (GetController()) {
		if(runInference)
			runInference = false;
		else
			runInference = true;
		runTraining = false;
	}
}

void ASpectatorCharacter::ResetTotalTrainingTime(const FInputActionValue& value)
{
	if (GetController()) {
		if (value.Get<bool>()) {
			resetTotalTrainingTime = true;
		}

		else {
			resetTotalTrainingTime = false;
		}
	}
}