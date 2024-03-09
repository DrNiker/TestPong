// Fill out your copyright notice in the Description page of Project Settings.


#include "PGoal.h"

// Sets default values
APGoal::APGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
}

void APGoal::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(HasAuthority()) GameMode->ScoreGoalServer_Implementation(PlayerID);
}

// Called when the game starts or when spawned
void APGoal::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<APGameMode>(GetWorld()->GetAuthGameMode());
	StaticMesh->OnComponentHit.AddDynamic(this, &APGoal::OnCompHit);
}

