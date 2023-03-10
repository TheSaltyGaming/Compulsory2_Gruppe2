// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Bullet.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASpaceShipPawn::ASpaceShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	SetRootComponent(ShipMesh);
	ShipMesh->SetRelativeLocation(FVector(0, 0, 0));
	ShipMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);
	Collider->InitBoxExtent(FVector(10,10,10));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASpaceShipPawn::OnOverlap);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
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
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("You died. GAME OVER"));
		UGameplayStatics::SetGamePaused(GetWorld(),true);
	}
}

void ASpaceShipPawn::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	if (!OtherActor->IsA<ABullet>())
	{
		Damage();
	}
}



void ASpaceShipPawn::Shoot(const FInputActionValue& input)
{
	if (Ammo > 0)
	{
		/*const FRotator*/
		
		if(Controller != nullptr)
		{
			UE_LOG(LogTemp,Warning,TEXT("Controller != nullpointer"))
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Pitch = 0.f;
			Rotation.Roll = 0.f;

		// Gets the local forward vector - normalized
		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
			GetWorld()->SpawnActor<AActor>(BP_Bullet,							// What to spawn
										GetActorLocation() + (Direction * 80.f), // Location
										Rotation);
			UE_LOG(LogTemp,Warning,TEXT("Spawned bullet"));
			Ammo--;
		}

					// Rotation
	}
}

void ASpaceShipPawn::Reload(const FInputActionValue& input)
{
	Ammo = MaxAmmo;
}

