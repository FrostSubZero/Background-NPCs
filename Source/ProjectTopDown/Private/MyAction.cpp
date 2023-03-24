// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAction.h"
#include "MyActionComponent.h"


bool UMyAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning()) {
		return false;
	}

	UMyActionComponent* comp = GetOwningComponent();
	if (comp->ActiveGameplayTags.HasAny(BlockedTags)) {
		return false;
	}

	return true;
}


void UMyAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this))

	UMyActionComponent* comp = GetOwningComponent();
	comp->ActiveGameplayTags.AppendTags(GrantsTags);

	BIsRunning = true;
}


void UMyAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this))

	ensureAlways(BIsRunning);

	UMyActionComponent* comp = GetOwningComponent();
	comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	BIsRunning = false;
}


UWorld* UMyAction::GetWorld() const
{
	// Outer is set when creating action via NewObject<T>
	UActorComponent* Comp = static_cast<UActorComponent*>(GetOuter());
	if (Comp) {
		return Comp->GetWorld();
	}
	return nullptr;
}


UMyActionComponent* UMyAction::GetOwningComponent() const
{
	return static_cast<UMyActionComponent*>(GetOuter());
}


bool UMyAction::IsRunning() const
{
	return BIsRunning;
}