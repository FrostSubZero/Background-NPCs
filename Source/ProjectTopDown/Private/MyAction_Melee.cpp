// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAction_Melee.h"
#include "..\Public\MyAction_Melee.h"
#include "GameFramework/Character.h"


UMyAction_Melee::UMyAction_Melee()
{
	AttackAnimDelay = 0.2f;
}


void UMyAction_Melee::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* character = static_cast<ACharacter*>(Instigator);
	if (character) {
		character->PlayAnimMontage(AttackAnim, PlayRate);
	}
}


void UMyAction_Melee::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
}
