// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.generated.h"

class UDestructibleComponent;
class USphereComponent;

UCLASS()
class TEST_PINGLESTUDIO_API AEnemyCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


private:

	UDestructibleComponent* DestructibleMeshComponent;
	USphereComponent* CollisionSphereComponent;
	USphereComponent* CollisionOffsetSphereComponent;

	FTimerHandle DeathHandle;

	bool isPendingDestruction=false;
	
	//Only valid for existed Enemy Destructible Mesh with 0.8 scale 
	const float DefaultOffsetRadius = 140.0f;
	const FVector DefaultMeshScale{0.8f,0.8f,0.8f};

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsActorPendingDestruction(){return isPendingDestruction;};
	void SetOffsetRadius(float input);
	void SetMeshScale(float input);
	void DestroyMesh();

};
