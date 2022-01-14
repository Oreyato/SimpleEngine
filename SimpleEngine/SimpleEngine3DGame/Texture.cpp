#include "Texture.h"
#include "Log.h"
#include <SDL_image.h>
#include <sstream>

Texture::Texture() : filename(""), width(0), height(0), SDLTexture(nullptr)
{
}

Texture::~Texture()
{
}

bool Texture::loadSDL(RendererSDL& rendererP, const string& filenameP)
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

bool Texture::loadOGL(RendererOGL& rendererP, const string& filenameP)
{
	filename = filenameP;
	// Load from file
	SDL_Surface* surf = IMG_Load(filename.c_str());
	if (!surf)
	{
		Log::error(LogCategory::Application, "Failed to load texture file " + filename);
		return false;
	}
	width = surf->w;
	height = surf->h;
	int format = 0;

	if (surf->format->format == SDL_PIXELFORMAT_RGB24)
	{
		format = GL_RGB;
	}
	else if (surf->format->format == SDL_PIXELFORMAT_RGBA32)
	{
		format = GL_RGBA;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, surf->pixels);
	SDL_FreeSurface(surf);

	Log::info("Loaded texture " + filename);
	// Enable bilinear filtering 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


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

void Texture::setActive() const
{
}
