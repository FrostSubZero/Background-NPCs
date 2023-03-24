// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "AICharacter.h"
#include "MyActionComponent.h"
#include "MyBTTask_Parry.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTOPDOWN_API UMyBTTask_Parry : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_Parry();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory);
	
private:
	UBlackboardComponent* MyBlackboard;

	AAICharacter* Enemy;

	UMyActionComponent* ActionComp;

	UFUNCTION()
	void ClearBBK();

	FLatentActionInfo LatentInfo;
};
