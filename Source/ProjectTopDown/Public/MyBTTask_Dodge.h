// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "MyBTTask_Dodge.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTTOPDOWN_API UMyBTTask_Dodge : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyBTTask_Dodge();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	float catch_radiu = 300;

	UBlackboardComponent* MyBlackboard;

	UFUNCTION()
	void ClearBBK();

	FLatentActionInfo LatentInfo;
};
