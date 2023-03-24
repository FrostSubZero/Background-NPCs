// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAction.h"
#include "MyAction_Melee.generated.h"



/**
 * 
 */
UCLASS()
class PROJECTTOPDOWN_API UMyAction_Melee : public UMyAction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float PlayRate;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UAnimMontage* AttackAnim;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

public:
	virtual void StartAction_Implementation(AActor* Instigator) override;

	UMyAction_Melee();
	
};
