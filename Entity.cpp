#include "Entity.h"
#include <iostream>

double Entity::getDistance(Food& food)
{
	double res;
	double xDist, yDist;
	xDist = std::abs(food.getX() - x);
	yDist = std::abs(food.getY() - y);
	res = std::sqrt(xDist * xDist + yDist * yDist);
	return res;
}

double Entity::getDistance(SDL_Point& point)
{
	double res;
	double xDist, yDist;
	xDist = std::abs(point.x - x);
	yDist = std::abs(point.y - y);
	res = std::sqrt(xDist * xDist + yDist * yDist);
	return res;
}

void Entity::SetCons()
{
	energyCons = 0.05;
	energyCons += pow(0.4 * speed, 2);
	energyCons += pow(viewRange / 300.0, 2);
}

double Entity::GetDirAngle(Food& food)
{
	double xDist, yDist;
	xDist = std::abs(x - food.getX());
	yDist = std::abs(y - food.getY());
	return std::atan(yDist / xDist);
}

double Entity::GetDirAngle(const SDL_Point& point)
{
	double xDist, yDist;
	xDist = std::abs(x - point.x);
	yDist = std::abs(y - point.y);
	return std::atan(yDist / xDist);
}

Entity::Entity()
{
	RepDec = 1.0;
	base.h = 20;
	base.w = 20;
	x = y = 0;
	minX = minY = maxX = maxY = 0;
	energy = 0;
	speed = 0;
	viewRange = 0;
	SetCons();
}

Entity::Entity(const Entity& entity, double mutVal)
{
	*this = entity;
	if (rand() % 2)
	{
		speed += ((rand() % ((int)(mutVal * 100)))) / 100.0;
	}
	else
	{
		speed -= (rand() % ((int)(mutVal * 100))) / 100.0;
	}

	if (rand() % 2)
	{
		viewRange += (rand() % ((int)(mutVal * 100)));
	}
	else
	{
		viewRange -= (rand() % ((int)(mutVal * 100)));
	}
	haveToChange = true;
	SetCons();
	energy = maxEnergy / 2;
}

Entity::Entity(int minX, int maxX, int minY, int maxY, double repK)
{
	RepDec = 1.0 - repK;
	switch (rand() % 4)
	{
	case 0:
		x = minX;
		y = (double)minY + rand() % (maxY - minY);
		break;
	case 1:
		x = maxX;
		y = (double)minY + rand() % (maxY - minY);
		break;
	case 2:
		y = minY;
		x = (double)minX + rand() % (maxX - minX);
		break;
	case 3:
		y = maxY;
		x = (double)minX + rand() % (maxX - minX);
		break;
	}
	this->minX = minX;
	this->minY = minY;
	this->maxX = maxX;
	this->maxY = maxY;
	base.h = 20;
	base.w = 20;
	maxEnergy = 100;
	energy = 100.0;
	speed = 1;
	viewRange = 50;
	SetCons();
	haveToChange = true;
}

void Entity::Draw(SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_Rect en;
	SDL_Rect view;
	SDL_Rect sp;
	base.x = (int)(x + 0.5) - base.w / 2;
	base.y = (int)(y + 0.5) - base.h / 2;
	en.x = base.x + 1;
	en.y = base.y + 1;
	en.h = base.h - 2;
	en.w = base.w - 2;
	view.x = (int)(x + 0.5);
	view.y = (int)(y + 0.5) - base.h / 4;
	view.h = base.h / 2;
	view.w = base.w / 4;
	sp = view;
	sp.x = view.x - view.w;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	
	SDL_RenderDrawLine(renderer, target.x, target.y, (int)(x + 0.5), (int)(y + 0.5));
	SDL_RenderFillRect(renderer, &base);
	int color = (int)((energy / maxEnergy) * 255 + 0.5);
	SDL_SetRenderDrawColor(renderer, color, color, color, 255);
	SDL_RenderFillRect(renderer, &en);
}

int Entity::Update(std::vector<Food>& food, double envHar)
{
	if (food.size())
	{
		double minDist = getDistance(food[0]);
		int minInd = 0;
		double buf;
		for (unsigned int i = 1; i < food.size(); i++)
		{
			buf = getDistance(food[i]);
			if (buf < minDist)
			{
				minInd = i;
				minDist = buf;
			}
		}
		if (minDist <= viewRange)
		{
			haveToChange = true;
			target.x = food[minInd].getX();
			target.y = food[minInd].getY();
			if (minDist < speed)
			{
				x = food[minInd].getX();
				y = food[minInd].getY();
				energy += food[minInd].getEnergy();
				food.erase(food.begin() + minInd);				
			}
			else
			{
				double dx = food[minInd].getX() - x;
				double dy = food[minInd].getY() - y;
				y += speed * dy / minDist;
				x += speed * dx / minDist;
			}
		}
		else
		{			
			if (haveToChange)
			{
				target.x = minX + rand() % (maxX - minX);
				target.y = minY + rand() % (maxY - minY);
				haveToChange = false;
			}
			double dist = getDistance(target);
			if (dist < speed)
			{
				x = target.x;
				y = target.y;
				haveToChange = true;
			}
			else
			{
				double dx = target.x - x;
				double dy = target.y - y;
				y += speed * dy / dist;
				x += speed * dx / dist;
			}
		}		
	}
	else
	{
		if (haveToChange)
		{
			target.x = minX + rand() % (maxX - minX);
			target.y = minY + rand() % (maxY - minY);
			haveToChange = false;
		}
		double dist = getDistance(target);
		if (dist < speed)
		{
			x = target.x;
			y = target.y;
			haveToChange = true;
		}
		else
		{
			double dx = target.x - x;
			double dy = target.y - y;
			y += speed * dy / dist;
			x += speed * dx / dist;
		}
	}
	energy -= energyCons * (1.0 - envHar);
	if (energy <= 0)
		return 1;

	if (energy >= maxEnergy)
	{
		energy = maxEnergy;
		energy = maxEnergy * RepDec;
		return 2;
	}
	return 0;
}

double Entity::GetSpeed()
{
	return speed;
}

double Entity::GetView()
{
	return viewRange;
}
