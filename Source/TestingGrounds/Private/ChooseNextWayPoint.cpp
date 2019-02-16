// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h" // TODO: remove coupling.
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto AIController = OwnerComp.GetAIOwner();
	if (!AIController) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not found."));
		return EBTNodeResult::Succeeded;
	}
	
	auto ControlledPawn = AIController->GetPawn();

	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	
	// Get Patrol Points
	PatrolPoints = PatrolRoute->GetPatrolPoints();

	// Set Next Way Point
	BlackboardComp->SetValueAsObject(NextWayPointkey.SelectedKeyName, PatrolPoints[index]);

	// Cycle Index
	index = (index+1)%PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, index);


	UE_LOG(LogTemp, Warning, TEXT("Waypoint index:%i"), index);



	return EBTNodeResult::Succeeded;
}

