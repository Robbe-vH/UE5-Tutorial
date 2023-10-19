// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DefaultPawn.h"

#include "MyCollectableActor.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJumpTriggerSignature, AActor*, OtherActor, UPrimitiveComponent*, OtherComponent);

UCLASS()
class NEWCPPTUTORIAL_API AMyCollectableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCollectableActor();

	UFUNCTION(BlueprintCallable)
	void Jump(float velocity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// call when another actor collides
	UFUNCTION()
	void OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	UClass* TriggerClass = ADefaultPawn::StaticClass();

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float Lifetime = 3.0f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float Velocity = 5.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;


	UPROPERTY(BlueprintAssignable)
	FOnJumpTriggerSignature OnJumpTrigger;

	bool IsLaunched = false;
};
