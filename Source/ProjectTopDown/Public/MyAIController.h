// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UAIPerceptionComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTTOPDOWN_API AMyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	class UBlackboardComponent* blackboard;

	UPROPERTY(BlueprintReadWrite, Category = "components")
	class UAIPerceptionComponent* perception_comp;

	class UAISenseConfig_Sight* sight_config;
	
	UPROPERTY(BlueprintReadWrite, Category = "components")
	FName Key_TargetCharacter = FName(TEXT("TargetCharacter"));

	UPROPERTY(BlueprintReadWrite, Category = "components")
	FName Key_SoundSource = FName(TEXT("SoundSource"));

	UPROPERTY(BlueprintReadWrite, Category = "components")
	FName Key_TargetPoint = FName(TEXT("TargetPoint"));

	UPROPERTY(BlueprintReadWrite, Category = "components")
	FName Key_Bullet = FName(TEXT("Bullet"));

	UPROPERTY(BlueprintReadWrite, Category = "components")
	FName Key_Gunner = FName(TEXT("Gunner"));

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* updated_actors, FAIStimulus Stimulus);

	UFUNCTION()
	void setup_perception_system();

public:
	AMyAIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
};
