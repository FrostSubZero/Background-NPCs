// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Parry.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UMyBTTask_Parry::UMyBTTask_Parry() {
	NodeName = "Parry";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UMyBTTask_Parry, BlackboardKey), AActor::StaticClass());
}


EBTNodeResult::Type UMyBTTask_Parry::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIController* controller = Cast<AAIController>(owner_comp.GetAIOwner());
	Enemy = static_cast<AAICharacter*>(controller->GetPawn());
	MyBlackboard = owner_comp.GetBlackboardComponent();

	if (Enemy != nullptr) {
		ActionComp = Enemy->GetActionComponent();

		ActionComp->StartActionByName(Enemy, "Parry");

		LatentInfo.Linkage = 0;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = "ClearBBK";
		UKismetSystemLibrary::Delay(this, 0.8f, LatentInfo);
		
		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
}


void UMyBTTask_Parry::ClearBBK()
{
	MyBlackboard->ClearValue(BlackboardKey.SelectedKeyName);
	ActionComp->StopActionByName(Enemy, "Parry");
}