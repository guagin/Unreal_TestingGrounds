// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto AIController = OwnerComp.GetAIOwner();
	if (!AIController) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not found."));
		return EBTNodeResult::Succeeded;
	}
	
	auto PatrollingGuard = Cast<APatrollingGuard>(AIController->GetPawn());
	if(!PatrollingGuard) {
		UE_LOG(LogTemp, Warning, TEXT("PatrollingGuard not found."));
		return EBTNodeResult::Succeeded;
	}
	// Get Patrol Points
	PatrolPoints = PatrollingGuard->GetPatrolPoints();

	// Set Next Way Point
	BlackboardComp->SetValueAsObject(NextWayPointkey.SelectedKeyName, PatrolPoints[index]);

	// Cycle Index
	index = (index+1)%PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, index);


	UE_LOG(LogTemp, Warning, TEXT("Waypoint index:%i"), index);



	return EBTNodeResult::Succeeded;
}