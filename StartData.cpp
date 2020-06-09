#include "StartData.h"
#include <iostream>

StartData::StartData()
{
	Env = 0.5;
	RepCost = 0.5;
	StartNumber = 15;
	FoodCount = 15;
}

void StartData::IncEnv()
{
	Env += 0.1;
	if (Env > 0.9)
		Env = 0.9;
}

void StartData::DecEnv()
{
	Env -= 0.1;
	if (Env < 0.1)
		Env = 0.0;
}

void StartData::IncStartNumber()
{
	StartNumber += 1;
	if (StartNumber > 99)
		StartNumber = 99;
}

void StartData::FastIncStartNumber()
{
	StartNumber += 10;
	if (StartNumber > 99)
		StartNumber = 99;
}

void StartData::DecStartNumber()
{
	StartNumber -= 1;
	if (StartNumber < 1)
		StartNumber = 1;
}

void StartData::FastDecStartNumber()
{
	StartNumber -= 10;
	if (StartNumber < 1)
		StartNumber = 1;
}

void StartData::IncFoodCount()
{
	FoodCount += 1;
	if (FoodCount > 99)
		FoodCount = 99;
}

void StartData::FastIncFoodCount()
{
	FoodCount += 10;
	if (FoodCount > 99)
		FoodCount = 99;
}

void StartData::DecFoodCount()
{
	FoodCount -= 1;
	if (FoodCount < 1)
		FoodCount = 1;
}

void StartData::FastDecFoodCount()
{
	FoodCount -= 10;
	if (FoodCount < 1)
		FoodCount = 1;
}

void StartData::IncRepCost()
{
	RepCost += 0.1;
	if (RepCost > 1.0)
		RepCost = 1.0;
}

void StartData::DecRepCost()
{
	RepCost -= 0.1;
	if (RepCost < 0.1)
		RepCost = 0.1;
}

double StartData::GetEnv()
{
	return Env;
}

double StartData::GetRepCost()
{
	return RepCost;
}

int StartData::GetStartNumber()
{
	return StartNumber;
}

int StartData::GetFoodCount()
{
	return FoodCount;
}