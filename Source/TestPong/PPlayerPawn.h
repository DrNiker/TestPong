// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PPlayerPawn.generated.h"

UCLASS()
class TESTPONG_API APPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APPlayerPawn();

	UPROPERTY()
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Bounds = 300.f;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void MoveServer(float Input);

	UFUNCTION(NetMulticast, Reliable)
	void MoveMulticast(FVector Location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
