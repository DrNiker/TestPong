// Fill out your copyright notice in the Description page of Project Settings.


#include "PBall.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
APBall::APBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
}

void APBall::MoveServer_Implementation(float DeltaTime)
{
	AddActorWorldOffset(MovementDirection*DeltaTime*Speed, true);
	MoveMulticast(GetActorLocation());
}

void APBall::MoveMulticast_Implementation(FVector Location)
{
	SetActorLocation(Location);
}

void APBall::OnCompHitServer_Implementation(const FHitResult& Hit)
{
	if(UKismetMathLibrary::Abs(Hit.ImpactNormal.X)>0.2) MovementDirection.X*=-1;
	if(UKismetMathLibrary::Abs(Hit.ImpactNormal.Y)>0.2) MovementDirection.Y*=-1;
}

void APBall::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	OnCompHitServer(Hit);
}

void APBall::ResetBallServer_Implementation()
{
	Active = false;
	
	SetActorLocation(InitPosition);
	MoveMulticast(InitPosition);
	
	float Dir = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	MovementDirection = FVector( Dir,1-Dir,0.f);
	
	Active = true;
}

// Called when the game starts or when spawned
void APBall::BeginPlay()
{
	Super::BeginPlay();
	
	if(HasAuthority())
	{
		InitPosition = GetActorLocation();
		StaticMesh->OnComponentHit.AddDynamic(this, &APBall::OnCompHit);
		
		float Dir = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		MovementDirection = FVector( Dir,1-Dir,0.f);
	}
}

// Called every frame
void APBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(HasAuthority()&& Active)
	{
		MoveServer(DeltaTime);
	}
}

