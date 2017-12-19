#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer(GLFWwindow& window)
{
	this->window = &window;

	
}



//Rendering Cycle
void Renderer::renderScene(Scene& scene)
{
	while (!glfwWindowShouldClose(this->window))
	{
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		renderSkyBox(scene);

		//glClear(GL_DEPTH_BUFFER_BIT);

		renderObjects(scene);
		
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->window);
	}
}


void Renderer::renderSkyBox(Scene& scene)
{
	
	glDepthFunc(GL_LEQUAL);
	int shaderKey = scene.getSkyBox()->getShaderKey();
	scene.changeShader(shaderKey);
	
	GLuint textureID = scene.getSkyBox()->getTextureKey();
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	


	scene.getShader()->setModelMatrix(scene.getSkyBox()->getModelMatrix());
	glBindVertexArray(scene.getSkyBox()->getVAO());
	int indicesCount = scene.getSkyBox()->getIndicesCount();

	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
	
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
	

}

//Renders objects
void Renderer::renderObjects(Scene& scene)
{
	int shaderKey = -1;
	int indicesCount = 0;
	glm::mat4 modelMatrix;
	



	for (int i = 0; i < scene.getObjects()->size(); i++)
	{
		if (!scene.getObjects()->at(i)->isRendered())
		{
			return;
		}

		shaderKey = scene.getObjects()->at(i)->getShaderKey();

		scene.changeShader(shaderKey);

		
			
		
		modelMatrix = scene.getObjects()->at(i)->getModelMatrix();




		scene.getShader()->setModelMatrix(modelMatrix);
		scene.getShader()->setObjectColor(scene.getObjects()->at(i)->getColour());

		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scene.getObjects()->at(i)->getTextureID());
		scene.getShader()->setTexture();*/
		activateObjectTexture(scene, i);

		glStencilFunc(GL_ALWAYS, scene.getObjects()->at(i)->getID(), 0xFF);

		glBindVertexArray(scene.getObjects()->at(i)->getVAO());
		

		indicesCount = scene.getObjects()->at(i)->getIndicesCount();
		
		if (indicesCount > 0)
		{
			glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, scene.getObjects()->at(i)->getVerticesCount());
		}
		
		glBindVertexArray(0);
		
	}
}

void Renderer::activateObjectTexture(Scene& scene, int objectArrayPosition)
{

	if (scene.getObjects()->at(objectArrayPosition)->getTextureKey() < 0)
	{
		return;
	}

	int objectTextureID = scene.getObjects()->at(objectArrayPosition)->getTextureKey();

	GLuint textureID = Application::getInstance()->getTextureID(objectTextureID);

	glActiveTexture(GL_TEXTURE0 + textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	scene.getShader()->setTexture(textureID);

	GLuint normalMapTextureID = Application::getInstance()->getNormalMapTextureID(objectTextureID);
	if (normalMapTextureID  == UINT_MAX)
	{
		return;
	}
	glActiveTexture(GL_TEXTURE0 + normalMapTextureID);
	glBindTexture(GL_TEXTURE_2D, normalMapTextureID);
	scene.getShader()->setNormalMapTexture(normalMapTextureID);



}
