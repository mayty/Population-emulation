#pragma once

class StartData
{
private:
	double Env;
	int StartNumber;
	int FoodCount;
	double RepCost;
public:
	StartData();
	void IncEnv();
	void DecEnv();

	void IncStartNumber();
	void FastIncStartNumber();
	void DecStartNumber();
	void FastDecStartNumber();

	void IncFoodCount();
	void FastIncFoodCount();
	void DecFoodCount();
	void FastDecFoodCount();
	
	void IncRepCost();
	void DecRepCost();

	double GetEnv();
	double GetRepCost();
	int GetStartNumber();
	int GetFoodCount();
};