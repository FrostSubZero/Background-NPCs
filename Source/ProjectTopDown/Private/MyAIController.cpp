// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "MyBullet.h"
#include "AICharacter.h"

AMyAIController::AMyAIController(FObjectInitializer const& object_initializer)
{
	perception_comp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	setup_perception_system();
}


void AMyAIController::OnTargetPerceptionUpdated(AActor* updated_actors, FAIStimulus Stimulus)
{
	if (Stimulus.IsValid()) {
		AMyBullet* mybullet = static_cast<AMyBullet*>(updated_actors);
		if (mybullet != nullptr && mybullet->EnemyBullet == false) {
			UBlackboardComponent* MyBlackboard = GetBlackboardComponent();
			MyBlackboard->SetValueAsObject(Key_Bullet, updated_actors);
		}
	}
	/*
	if (!(Stimulus.IsValid())) {
		UBlackboardComponent* MyBlackboard = GetBlackboardComponent();
		MyBlackboard->ClearValue(Key_Bullet);
	}
	*/
}


void AMyAIController::setup_perception_system() {
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	sight_config->SightRadius = 500.0f;
	sight_config->LoseSightRadius = 600.0f;
	sight_config->PeripheralVisionAngleDegrees = 75.0f;
	sight_config->SetMaxAge(5.0f);
	sight_config->AutoSuccessRangeFromLastSeenLocation = 800.0f;
	sight_config->DetectionByAffiliation.bDetectEnemies = true;
	sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	sight_config->DetectionByAffiliation.bDetectNeutrals = true;

	perception_comp->SetDominantSense(*sight_config->GetSenseImplementation());
	perception_comp->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTargetPerceptionUpdated);
	perception_comp->ConfigureSense(*sight_config);
}
