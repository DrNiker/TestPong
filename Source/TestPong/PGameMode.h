// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PBall.h"
#include "GameFramework/GameModeBase.h"
#include "PGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTPONG_API APGameMode : public AGameModeBase
{
	GENERATED_BODY()

	APGameMode();

	UFUNCTION(Server, Reliable)
	void StartMatchServer();

	UFUNCTION(Server, Reliable)
	void ScoreGoalServer(int32 PlayerID);
	
	UFUNCTION(NetMulticast, Reliable)
	void ScoreGoalMulticast();

	UFUNCTION(Server, Reliable)
	void CheckPlayersServer();
	
	UPROPERTY()
	FTimerHandle WaitForStartHandle;
	
	bool WaitForStart = true;
	
	UPROPERTY()
	int32 FirstPlayerScore = 0;
	UPROPERTY()
	int32 SecondPlayerScore = 0;
	
	UPROPERTY()
	APBall* Ball;

	virtual void StartPlay() override;
};
