// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Dodge.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AIController.h"
#include "AICharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyActionComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UMyBTTask_Dodge::UMyBTTask_Dodge() {
	NodeName = "Dodge";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UMyBTTask_Dodge, BlackboardKey), AActor::StaticClass());
}


EBTNodeResult::Type UMyBTTask_Dodge::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIController* controller = Cast<AAIController>(owner_comp.GetAIOwner());
	AAICharacter* Enemy = static_cast<AAICharacter*>(controller->GetPawn());
	MyBlackboard = owner_comp.GetBlackboardComponent();

	if (Enemy != nullptr) {
		UMyActionComponent* ActionComp = Enemy->GetActionComponent();

		float x = FMath::FRand();
		if (x > 0.5f) {
			ActionComp->StartActionByName(Enemy, "DodgeL");

			LatentInfo.Linkage = 0;
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = "ClearBBK";
			UKismetSystemLibrary::Delay(this, 0.7f, LatentInfo);

			ActionComp->StopActionByName(Enemy, "DodgeL");
		}
		else {
			ActionComp->StartActionByName(Enemy, "DodgeR");

			LatentInfo.Linkage = 0;
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = "ClearBBK";
			UKismetSystemLibrary::Delay(this, 0.7f, LatentInfo);

			ActionComp->StopActionByName(Enemy, "DodgeR");
		}
	
		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
}


void UMyBTTask_Dodge::ClearBBK()
{
	MyBlackboard->ClearValue(BlackboardKey.SelectedKeyName);
}

