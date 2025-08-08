#include <Cabrankengine/Renderer/Renderer.h>

#include <Cabrankengine/Renderer/OrthographicCamera.h>
#include <Cabrankengine/Renderer/Shader.h>
#include <Platform/OpenGL/OpenGLShader.h>

namespace cabrankengine {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::beginScene(OrthographicCamera& camera) {
		s_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer::endScene() {

	}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_viewProjection", s_SceneData->viewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_Transform", transform);
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}
