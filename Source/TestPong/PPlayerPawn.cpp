// Fill out your copyright notice in the Description page of Project Settings.


#include "PPlayerPawn.h"

// Sets default values
APPlayerPawn::APPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
}

void APPlayerPawn::MoveServer_Implementation(float Input)
{
	if (abs(Input) < 0.1f) return;
	
	const float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	if(Input>0)
	{
		if(Input * Speed * DeltaSeconds + GetActorLocation().Y > SpawnLocation.Y + Bounds)
		{
			SetActorLocation(FVector(SpawnLocation.X,SpawnLocation.Y + Bounds, SpawnLocation.Z));
		} else
		{
			AddActorWorldOffset(FVector(0,Input * Speed, 0));
		}
	} else
	{
		if(Input * Speed * DeltaSeconds + GetActorLocation().Y < SpawnLocation.Y - Bounds)
		{
			SetActorLocation(FVector(SpawnLocation.X,SpawnLocation.Y - Bounds, SpawnLocation.Z));
		} else
		{
			AddActorWorldOffset(FVector(0,Input * Speed, 0));
		}
	}

	MoveMulticast(GetActorLocation());
}

void APPlayerPawn::MoveMulticast_Implementation(FVector Location)
{
	SetActorLocation(Location);
}

// Called when the game starts or when spawned
void APPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	SpawnLocation = GetActorLocation();
}

// Called every frame
void APPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

