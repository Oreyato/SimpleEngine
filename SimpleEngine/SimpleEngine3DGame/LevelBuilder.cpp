#include "LevelBuilder.h"
#include "Log.h"
#include "Plane.h"
#include "Cube.h"

#include <iostream>
#include <fstream>

using std::string;
using std::ifstream;
using std::fstream;
using std::getline;

LevelBuilder::LevelBuilder(std::string levelNameP, const Vector3 originP) :
	levelName{levelNameP},
	origin{originP},
	wallScale{200.0f},
	floorScale{wallScale}
{
}

void LevelBuilder::buildLevel()
{
	string line;
	// Look for the right file and try to open it
	std::ifstream  levelFile{ "Res\\Levels\\" + levelName + ".txt"};

	// If it fails to open, log an info
	if (!levelFile.is_open()) {
		Log::info("Couldn't open file " + levelName + ".txt");
	}
	// else, create the level
	else {
		// Prepare line iterator
		int lineNumber = 0;

		// Iterate line by line
		while (getline(levelFile, line))
		{
			// Iterate through each character of each line
			for (int i = 0; i < line.length(); i++)
			{
				// Create a wall when needed
				if (line[i] == 'x') {
					Cube* cube = new Cube;
					cube->setScale(wallScale);
					cube->setPosition(Vector3(origin.x + i * wallScale, origin.y + lineNumber * wallScale, origin.z));
				}
				else {
					// Create the floor
					Plane* plane = new Plane;
					plane->setScale(floorScale / 100.0f);
					plane->setPosition(Vector3(origin.x + i * floorScale, origin.y + lineNumber * floorScale, origin.z - 100.0f));
				}
			}

			lineNumber += 1;
		}
		levelFile.close();
	}
}
