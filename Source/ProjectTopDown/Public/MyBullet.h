// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayTagContainer.h"
#include "MyBullet.generated.h"

class UBoxComponent;

UCLASS()
class PROJECTTOPDOWN_API AMyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBullet();

	UPROPERTY(BlueprintReadWrite, Category = "components")
	bool EnemyBullet;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "components")
	UStaticMeshComponent* BulletComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "components")
	UBoxComponent* BoxComp;

	UPROPERTY(BlueprintReadWrite, Category = "components")
	class UAIPerceptionStimuliSourceComponent* stimulus;

	UPROPERTY(EditDefaultsOnly, Category = "components")
	FGameplayTag ParryTag;

	void setup_stimulus();

	UPROPERTY(BlueprintReadWrite, Category = "components")
	UProjectileMovementComponent* MoveComp;

	UFUNCTION(BlueprintCallable, Category = "components")
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromsweep, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
