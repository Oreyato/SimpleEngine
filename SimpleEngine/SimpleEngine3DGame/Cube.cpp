#include "Cube.h"
#include "MeshComponent.h"
#include "Assets.h"

Cube::Cube() : Actor()
{
	MeshComponent* meshComp = new MeshComponent(this);
	meshComp->setMesh(Assets::getMesh("Mesh_Cube"));
}
