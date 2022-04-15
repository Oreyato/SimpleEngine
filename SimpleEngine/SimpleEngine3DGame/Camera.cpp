#include "Camera.h"
#include "MoveComponent.h"
#include "Game.h"
#include "SoundEvent.h"

Camera::Camera() : 
	Actor{},
	moveComponent{ nullptr },
	audioComponent{ nullptr },
	lastFootStep{ 0.0f }
{
	moveComponent = new MoveComponent(this);
	audioComponent = new AudioComponent(this);
	footstep = audioComponent->playEvent("event:/Footstep");
	footstep.setPaused(true);
}

void Camera::updateActor(float deltaTime)
{
	Actor::updateActor(deltaTime);

	// Play the footsteps if we're moving, and it has been a while since the last time we played the sound
	lastFootStep -= deltaTime;
	if (!Maths::nearZero(moveComponent->getForwardSpeed()) && lastFootStep <= 0.0f) {
		footstep.setPaused(false);
		footstep.restart();
		// Launching the "timer" again
		lastFootStep = 0.5f;
	}

	// Compute new camera from this actor
	Vector3 cameraPos = getPosition();
	Vector3 target = getPosition() + getForward() * 100.0f;
	Vector3 up = Vector3::unitZ;

	Matrix4 view = Matrix4::createLookAt(cameraPos, target, up);
	getGame().getRenderer().setViewMatrix(view);
	getGame().getAudioSystem().setListener(view);
}

void Camera::actorInput(const Uint8* keys)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 300.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 300.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		angularSpeed -= Maths::twoPi;
	}
	if (keys[SDL_SCANCODE_D])
	{
		angularSpeed += Maths::twoPi;
	}

	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setAngularSpeed(angularSpeed);
}

void Camera::setFootstepSurface(float value)
{
	// Pause here because of the way the parameters are set in FMOD,
	// changing it will play a footstep and we don't want it
	footstep.setPaused(true);
	footstep.setParameter("Surface", value);
}
