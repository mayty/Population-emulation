#pragma once
#include "Drawable.h"
#include "Food.h"
#include <vector>
#include <cmath>
class Entity : public Drawable
{
private:
	int minX, minY;
	int maxX, maxY;
	double x, y;
	double energy;
	double maxEnergy;
	double speed;
	double viewRange;
	SDL_Rect base;
	double energyCons;
	double RepDec;

	SDL_Point target;
	bool haveToChange;

	double getDistance(Food& food);
	double getDistance(SDL_Point& point);
	void SetCons();
	double GetDirAngle(Food& food);
	double GetDirAngle(const SDL_Point& point);
public:
	Entity();
	Entity(const Entity& entity, double mutVal);
	Entity(int minX, int maxX, int minY, int maxY, double repK);
	void Draw(SDL_Renderer* renderer, TTF_Font* font = nullptr);
	int Update(std::vector<Food>& food, double envHar);
	double GetSpeed();
	double GetView();
};

