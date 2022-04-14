#include "Plane.h"
#include "MeshComponent.h"
#include "Assets.h"

Plane::Plane() : Actor()
{
	setScale(10.0f);
	MeshComponent* meshComp = new MeshComponent(this);
	meshComp->setMesh(Assets::getMesh("Mesh_Plane"));
}