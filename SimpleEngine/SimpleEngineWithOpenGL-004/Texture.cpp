#include "Texture.h"
#include "Log.h"
#include <SDL_image.h>

Texture::Texture() : filename(""), width(0), height(0), SDLTexture(nullptr)
{
}

Texture::~Texture()
{
}

bool Texture::load(Renderer& rendererP, const string& filenameP)
{
	filename = filenameP;

	// Load from file
	SDL_Surface* surf = IMG_Load(filename.c_str()); // SDL load a surface, which is an array of pixel color, ...

	if (!surf) {
		Log::error(LogCategory::Application, "Failed to load texture file " + filename);

		return false;
	}

	width = surf->w;
	height = surf->h;

	// Create texture from the surface
	SDLTexture = SDL_CreateTextureFromSurface(rendererP.toSDLRenderer(), surf); // ..., then convert it to a GPU-optimized texture
	SDL_FreeSurface(surf); // Once converted, we don't need the surface anymore

	if (!SDLTexture) {
		Log::error(LogCategory::Render, "Failed to convert surface to texture for " + filename);

		return false;
	}
	Log::info("Loaded texture " + filename);

	return true;
}

void Texture::unload()
{
	if (SDLTexture) {
		SDL_DestroyTexture(SDLTexture);
	}
}

void Texture::updateInfo(int& widthOut, int& heightOut)
{
	widthOut = width;
	heightOut = height;
}
