#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "Vector2.h"
#include "Shader.h"

#include <vector>

class RendererOGL :
    public IRenderer
{
public:
    RendererOGL();
    virtual ~RendererOGL();
	RendererOGL(const RendererOGL* sprite);
	RendererOGL& operator=(const RendererOGL&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void draw();
	void endDraw();

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;

	void close();
	IRenderer::Type type() { return Type::OGL; }

private:
	void drawSprites();

	Shader* shader;
	Window* window;
	VertexArray* vertexArray;
	SDL_GLContext context;
	Matrix4 viewProj;
	std::vector<class SpriteComponent*> sprites;
};