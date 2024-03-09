// Fill out your copyright notice in the Description page of Project Settings.


#include "PGameMode.h"

#include "Async/ParkingLot.h"
#include "Kismet/GameplayStatics.h"

APGameMode::APGameMode()
{
}

void APGameMode::CheckPlayersServer_Implementation()
{
	if(GetNumPlayers()>=2)
	{
		WaitForStart = false;
		StartMatchServer();
		GetWorld()->GetTimerManager().ClearTimer(WaitForStartHandle);
	}
}

void APGameMode::StartPlay()
{
	Super::StartPlay();
;
	Ball = Cast<APBall>(UGameplayStatics::GetActorOfClass(GetWorld(), APBall::StaticClass()));
	if(HasAuthority()){
		GetWorld()->GetTimerManager().SetTimer(WaitForStartHandle, this, &APGameMode::CheckPlayersServer,
			0.1f, true);
	}
}

void APGameMode::StartMatchServer_Implementation()
{
	if(!Ball) Ball = Cast<APBall>(UGameplayStatics::GetActorOfClass(GetWorld(), APBall::StaticClass()));
	Ball->Active = true; 
}

void APGameMode::ScoreGoalMulticast_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("Score! %d : %d"),FirstPlayerScore,SecondPlayerScore));
}

void APGameMode::ScoreGoalServer_Implementation(int32 PlayerID)
{
	Ball->ResetBallServer();
	switch (PlayerID) 
	{
		case 0:
			FirstPlayerScore++;
			break;
		case 1:
			SecondPlayerScore++;
			break;
		default:break;
	}
	ScoreGoalMulticast();
}


