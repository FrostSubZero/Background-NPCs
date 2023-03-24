// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_RandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_RandomLocation::UMyBTTask_RandomLocation(){
	NodeName = "FindRandomLocation";
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UMyBTTask_RandomLocation, BlackboardKey));
}


EBTNodeResult::Type UMyBTTask_RandomLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) {
	// Get AI controller and its NPC
	AAIController* controller = Cast<AAIController>(owner_comp.GetAIOwner());
	UBlackboardComponent* MyBlackboard = owner_comp.GetBlackboardComponent();

	// FVector KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());

	auto const npc = controller->GetPawn();

	// Obtain npc location to use as an origin location
	FVector const origin = npc->GetActorLocation();
	FNavLocation location;

	// Get the navigation system and generate a random location
	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radiu, location, nullptr)) {
		MyBlackboard->SetValueAsVector(BlackboardKey.SelectedKeyName, location.Location);
	}

	//FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}


