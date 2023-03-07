// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Bullet.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"

// Sets default values
ASpaceShipPawn::ASpaceShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	RootComponent = ShipMesh;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);

	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// static ConstructorHelpers::FObjectFinder<UStaticMesh> Model3D(TEXT("/Game/Assets/Models/MainShip.MainShip"));
	//
	// if (Model3D.Succeeded())
	// {
	// 	ShipMesh->SetStaticMesh(Model3D.Object);
	// }
	
	Ammo = 15;
	MaxAmmo = 15;
	MovementSpeed = 1000;
	Health = 5;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ASpaceShipPawn::BeginPlay()
{
	Super::BeginPlay();
	

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if(subsystem)
		{
			subsystem->AddMappingContext(IMC, 0);
		}
	}
}

// Called every frame
void ASpaceShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);

	if ((Controller != nullptr) && (XInput != 0.f))
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;

		// Gets the local forward vector - normalized
		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		SetActorLocation(GetActorLocation() + (Direction * XInput * MovementSpeed * DeltaTime));

		SetActorRotation(Rotation);
	}

	if ((Controller != nullptr) && (YInput != 0.f))
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;

		// Gets the local forward vector - normalized
		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
		SetActorLocation(GetActorLocation() + (Direction * YInput * MovementSpeed * DeltaTime));

		SetActorRotation(Rotation);
	}
}

// Called to bind functionality to input
void ASpaceShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhanceInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhanceInputCom->BindAction(IA_Forwardbackward, ETriggerEvent::Triggered, this, &ASpaceShipPawn::VerticalMovement);
		EnhanceInputCom->BindAction(IA_Forwardbackward, ETriggerEvent::Completed, this, &ASpaceShipPawn::VerticalMovement);
		EnhanceInputCom->BindAction(IA_LeftRight, ETriggerEvent::Triggered, this, &ASpaceShipPawn::HorizontalMovement);
		EnhanceInputCom->BindAction(IA_LeftRight, ETriggerEvent::Completed, this, &ASpaceShipPawn::HorizontalMovement);

		/* Input for look movement */
		EnhanceInputCom->BindAction(IA_LookAround, ETriggerEvent::Started, this, &ASpaceShipPawn::LookAround);
		EnhanceInputCom->BindAction(IA_LookAround, ETriggerEvent::Triggered, this, &ASpaceShipPawn::LookAround);
		EnhanceInputCom->BindAction(IA_LookAround, ETriggerEvent::Completed, this, &ASpaceShipPawn::LookAround);
		EnhanceInputCom->BindAction(IA_LookUp, ETriggerEvent::Started, this, &ASpaceShipPawn::LookUp);
		EnhanceInputCom->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &ASpaceShipPawn::LookUp);
		EnhanceInputCom->BindAction(IA_LookUp, ETriggerEvent::Completed, this, &ASpaceShipPawn::LookUp);


		EnhanceInputCom->BindAction(IA_Shoot, ETriggerEvent::Started, this, &ASpaceShipPawn::Shoot);
		EnhanceInputCom->BindAction(IA_Reload, ETriggerEvent::Started, this, &ASpaceShipPawn::Reload);
		EnhanceInputCom->BindAction(IA_ResetGame, ETriggerEvent::Started, this, &ASpaceShipPawn::ResetGame);
	}
}

void ASpaceShipPawn::VerticalMovement(const FInputActionValue& input)
{
	XInput = input.Get<float>();
}

void ASpaceShipPawn::HorizontalMovement(const FInputActionValue& input)
{
	YInput = input.Get<float>();
}

void ASpaceShipPawn::LookAround(const FInputActionValue& input)
{
	Yaw = input.Get<float>();
}

void ASpaceShipPawn::LookUp(const FInputActionValue& input)
{
	Pitch = input.Get<float>();
}


void ASpaceShipPawn::Damage()
{
	Health--;
	if (Health <= 0)
	{
		// Adding Game over
	}
}



void ASpaceShipPawn::Shoot(const FInputActionValue& input)
{
	if (Ammo > 0)
	{
		/*const FRotator*/
		
		if(Controller != nullptr)
		{
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Pitch = 0.f;
			Rotation.Roll = 0.f;

		// Gets the local forward vector - normalized
		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
			GetWorld()->SpawnActor<AActor>(BP_Bullet,							// What to spawn
										GetActorLocation() + (Direction * 50.f), // Location
										Rotation);
			Ammo--;
		}

					// Rotation
	}
}

void ASpaceShipPawn::Reload(const FInputActionValue& input)
{
	Ammo = MaxAmmo;
}

void ASpaceShipPawn::ResetGame(const FInputActionValue& val)
{
}

