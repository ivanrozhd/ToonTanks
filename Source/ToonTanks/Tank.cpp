// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	Balive = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerTankController = Cast<APlayerController>(GetController());
	
}
// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerTankController)
	{
		FHitResult HitResult;
		bool Result = PlayerTankController->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
	
		if (Result)
		{
			RotateTurret(HitResult.Location);	
		}
		
	}

}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ATank::Fire);
}



void ATank::Move(float Value)
{
	

		FVector DeltaLocation = FVector::ZeroVector;
		DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
		AddActorLocalOffset(DeltaLocation, true); 

	
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation,true);
}


