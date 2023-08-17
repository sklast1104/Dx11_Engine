#include "AudioListener.h"
#include "Transform.h"
#include "GameObject.h"
#include "Fmod.h"

namespace Jun
{
	AudioListener::AudioListener()
		: Component(eComponentType::AudioListener)
	{

	}

	AudioListener::~AudioListener()
	{

	}

	void AudioListener::Initialize()
	{

	}

	void AudioListener::Update()
	{

	}

	void AudioListener::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 foward = tr->Foward();
		Vector3 up = tr->Up();

		Vector3 vel = { 0.0f, 0.0f, 0.0f };
		Fmod::Set3DListenerAttributes(&pos, &vel, &foward, &up);
	}

	void AudioListener::Render()
	{

	}
}