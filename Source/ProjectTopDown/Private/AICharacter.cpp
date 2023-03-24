// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "MyActionComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActionComp = CreateDefaultSubobject<UMyActionComponent>("ActionComp");
}


UMyActionComponent* AAICharacter::GetActionComponent() const
{
	return ActionComp;
}


// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void AAICharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}


void AAICharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}


// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

