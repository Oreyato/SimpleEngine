#pragma once
#include "Vector3.h"
#include <string>

class LevelBuilder
{
public:
	LevelBuilder(std::string levelNameP, const Vector3 originP);

	void buildLevel();

private:
	std::string levelName;

	const Vector3 origin;
	
	const float wallScale;
	const float floorScale;
};

