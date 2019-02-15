// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrollingGuard.h"

TArray<AActor*> APatrollingGuard::GetPatrolPoints() const{
	UE_LOG(LogTemp, Warning, TEXT("PatrolPoints size:%d"), PatrolPoints.Num());
	return PatrolPoints;
}