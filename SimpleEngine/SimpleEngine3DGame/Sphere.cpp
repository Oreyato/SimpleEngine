#include "Sphere.h"
#include "MeshComponent.h"
#include "Assets.h"

Sphere::Sphere() : Actor()
{
	MeshComponent* meshComp = new MeshComponent(this);
	meshComp->setMesh(Assets::getMesh("Mesh_Sphere"));
}

