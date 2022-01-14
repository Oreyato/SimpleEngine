#pragma once

#include <vector>

#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "IRenderer.h"
#include "Vector2.h"
#include "Astroid.h"
#include "RendererOGL.h"

using std::vector;

/// CTRL+D -> dupliquer une ligne
/// SHIFT+Suppr -> supprimer une ligne

class Game
{
public:
	static Game& instance()
	{
		static Game inst;

		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() :
		isRunning(true),
		isUpdatingActors(false)
	{}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	RendererOGL& getRenderer() { return renderer; }

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	RendererOGL renderer;

	bool isUpdatingActors; // Serves as a lock to avoid adding actors when it isn't relevant
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	//v Game specifics ===============================================
public:
	vector<Astroid*>& getAstroids();
	void addAstroid(Astroid* astroid);
	void removeAstroid(Astroid* astroid);

private:
	vector<Astroid*> astroids;
	//^ Game specifics ===============================================
};

