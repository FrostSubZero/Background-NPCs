// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBullet.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Components/BoxComponent.h"
#include "MyActionComponent.h"

// Sets default values
AMyBullet::AMyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BulletComp = CreateDefaultSubobject<UStaticMeshComponent>("BulletComp");
	//RootComponent = BulletComp;

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovecomp");
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 3000;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetupAttachment(RootComponent);

	setup_stimulus();
}


// Called when the game starts or when spawned
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AMyBullet::OnActorOverlap);
}


void AMyBullet::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromsweep, const FHitResult& Hit)
{
	
	if (otherActor && otherActor != GetInstigator()) {
		UMyActionComponent* ActionComp = Cast<UMyActionComponent>(otherActor->GetComponentByClass(UMyActionComponent::StaticClass()));
		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag)) {
			MoveComp->Velocity = -MoveComp->Velocity;

			this->SetOwner(otherActor);
			//SetInstigator(Cast<APawn>(otherActor));

			if (!this->EnemyBullet) {
				this->EnemyBullet = true;
			}
			else {
				this->EnemyBullet = false;
			}
			return;
		}
	}
}


void AMyBullet::setup_stimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	stimulus->RegisterForSense(UAISense_Sight::StaticClass());
	stimulus->RegisterWithPerceptionSystem();
}


// Called every frame
void AMyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

