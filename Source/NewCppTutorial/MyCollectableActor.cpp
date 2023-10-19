// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCollectableActor.h"

// Sets default values
AMyCollectableActor::AMyCollectableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	// Create the box collider
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

void AMyCollectableActor::Jump(float velocity)
{
	// launch only once
	if (!IsLaunched) {
		SetActorTickEnabled(true);

		// execute jump with physics system
		StaticMesh->AddImpulse({ 0.0f, 0.0f, velocity * 500.0f });

		// initiate object destruction
		IsLaunched = true;
	}
}

// Called when the game starts or when spawned
void AMyCollectableActor::BeginPlay()
{
	Super::BeginPlay();

	// Setup per instance OnComponentOverlap event
	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnComponentBeginOverlap");
	BoxCollision->OnComponentBeginOverlap.Add(DelegateSubscriber);

	// Ticking is only needed when jumping
	SetActorTickEnabled(false);	
}

void AMyCollectableActor::OnComponentBeginOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsLaunched && OtherActor->IsA(TriggerClass)) {
		OnJumpTrigger.Broadcast(OtherActor, Component);
	}
}


// Called every frame
void AMyCollectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLaunched) {
		Lifetime -= DeltaTime;

		if (Lifetime <= 0.0f) {
			Destroy();
		}
	}

}

