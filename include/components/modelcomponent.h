#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include <gl/GL.h>

#include "components/gameobjectcomponent.h"
#include "shaders/texture.h"

namespace gamo {
	class ModelComponent : public GameObjectComponent<VertexP3N3T2> {
	private:
		class MaterialInfo {
		public:
			std::string name;
			gamo::Texture* texture = nullptr;
			gamo::Texture* bumpMap = nullptr;

			MaterialInfo() { };
			inline bool hasTexture() { return texture != nullptr; };
		};

		class GroupInfo {
		public:
			std::string name;
			int start = -1;
			int end = -1;
			int materialIndex = -1;

			GroupInfo() { };
		};

		std::string filename;
		float scale;
		std::vector<GroupInfo*> groups;
		std::vector<MaterialInfo*> materials;
		GLuint _vertexArray;

	public:
		ModelComponent(std::string filename, float scale = 1.0);
		~ModelComponent();

		void onBuild(std::vector<VertexP3N3T2>& vertices) override;
		void onDraw(Shader<VertexP3N3T2>* shader, const glm::mat4& transform) override;

		void loadMaterialFile(std::string fileName, std::string dirName);
	};
}