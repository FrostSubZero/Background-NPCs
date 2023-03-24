// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActionComponent.h"
#include "MyAction.h"


// Sets default values for this component's properties
UMyActionComponent::UMyActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UMyAction> ActionClass : DefaultActions) {
		AddAction(ActionClass);
	}
	
}


// Called every frame
void UMyActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UMyActionComponent::AddAction(TSubclassOf<UMyAction> ActionClass)
{
	if (!ensure(ActionClass)) {
		return;
	}

	UMyAction* NewAction = NewObject<UMyAction>(this, ActionClass);
	if (ensure(NewAction)) {
		Actions.Add(NewAction);
	}
}


bool UMyActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UMyAction* Action : Actions) {
		if (Action && Action->ActionName == ActionName) {
			if (!Action->CanStart(Instigator)) {
				continue;
			}

			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}


bool UMyActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UMyAction* Action : Actions) {
		if (Action && Action->ActionName == ActionName) {
			if (Action->IsRunning()) {
				Action->StopAction(Instigator);
				return true;
			}			
		}
	}
	return false;
}
