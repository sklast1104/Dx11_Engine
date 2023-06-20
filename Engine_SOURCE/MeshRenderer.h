#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"

namespace Jun {

	class MeshRenderer : public Component
	{
	public :
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMesh(Mesh* mesh) { mMesh = mesh; }
		void SetMaterial(Material* material) { mMaterial = material; }

	private :
		Mesh* mMesh;
		Material* mMaterial;
	};
}



