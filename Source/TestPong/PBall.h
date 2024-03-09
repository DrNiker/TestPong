// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PBall.generated.h"

UCLASS()
class TESTPONG_API APBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APBall();

	UPROPERTY(EditAnywhere)
	FVector MovementDirection;
	
	UPROPERTY()
	FVector InitPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 150.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Active = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;
	
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void MoveServer(float DeltaTime);

	UFUNCTION(NetMulticast, Reliable)
	void MoveMulticast(FVector Location);
	
	UFUNCTION(Server, Reliable)
	void OnCompHitServer(const FHitResult& Hit);

	UFUNCTION()
	void OnCompHit (UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION(Server, Reliable)
	void ResetBallServer();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
