// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Test_PingleStudioProjectile.h"
#include "DefaultGameplayMode.h"
#include "Kismet/GameplayStatics.h"

#include "Components/SphereComponent.h" 
#include "DestructibleComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CollisionOffsetSphereComponent = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));
	CollisionSphereComponent = Cast<USphereComponent>(CollisionOffsetSphereComponent->GetChildComponent(0));
	DestructibleMeshComponent = Cast<UDestructibleComponent>(GetComponentByClass(UDestructibleComponent::StaticClass()));

	if (!IsValid(CollisionOffsetSphereComponent) || !IsValid(CollisionSphereComponent) || !IsValid(DestructibleMeshComponent))
	{
		return;
	}

	ADefaultGameplayMode* MyMode = Cast<ADefaultGameplayMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	if (!IsValid(MyMode))
	{
		return;
	}

	//��������� ������ - ������ ����. NewRadius ��������� ����� ����� � ��������� ������. ������ �������� ��������� ����� ������ ������� �� 2 � ����������� � ���������� �������
	float NewRadius = DefaultOffsetRadius + (MyMode->GetEnemyToEnemySpawnDistance()) / 2;
	CollisionOffsetSphereComponent->SetSphereRadius(NewRadius);
	
	float ScaleStep = MyMode->GetEnemyRadiusScaleDecrease();
	FVector NewScale = DefaultMeshScale; 
	NewScale -= FVector(ScaleStep);
	DestructibleMeshComponent->SetRelativeScale3D(NewScale);

	//������� ���� ����������� ������ ����� ������� � ����������� ������� ����. �������� ������ ������������ ����������, �� � �������� �����������
	float NewCollisionRadiusDecrease = (ScaleStep / 0.05f) * 10;
	CollisionSphereComponent->SetSphereRadius(DefaultOffsetRadius - NewCollisionRadiusDecrease);

	CollisionSphereComponent->OnComponentHit.AddDynamic(this, &AEnemyCharacter::OnHit);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<ATest_PingleStudioProjectile>(OtherActor))
	{
		ADefaultGameplayMode* MyMode = Cast<ADefaultGameplayMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (MyMode)
		{
			MyMode->DecrementEnemyLeftToNextWave();
		}

		OtherActor->Destroy();
		DestroyMesh();
	}
}

void AEnemyCharacter::SetOffsetRadius(float input)
{
	CollisionSphereComponent->SetSphereRadius(DefaultOffsetRadius+ input/2);
}

void AEnemyCharacter::SetMeshScale(float input)
{
	DestructibleMeshComponent->SetRelativeScale3D(DefaultMeshScale-input);
}

void AEnemyCharacter::DestroyMesh()
{
	DestructibleMeshComponent->ApplyDamage(100.0f, this->GetActorLocation(), { 0.f,0.f,1.f }, 25000.0f);

	isPendingDestruction = true;

	//��� �������������� ��������� ��������, ���� ������ ��� ��������� �� ����� 
	CollisionSphereComponent->SetSphereRadius(1.f, false);
	
	//��� �� �� ����� �������� ����� ������ 
	CollisionOffsetSphereComponent->SetSphereRadius(1.f, false);

	GetWorld()->GetTimerManager().SetTimer(DeathHandle,
		FTimerDelegate::CreateWeakLambda(this, [this]
	{
		Destroy();
	}), 5.0f, false);
}
