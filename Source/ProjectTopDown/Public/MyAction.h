// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "MyAction.generated.h"

class UWorld;
/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTTOPDOWN_API UMyAction : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const;

	UWorld* GetWorld() const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	UFUNCTION(BlueprintCallable, Category = "Action")
	UMyActionComponent* GetOwningComponent() const;

	bool BIsRunning;
};
