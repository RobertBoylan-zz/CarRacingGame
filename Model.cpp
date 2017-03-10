#include "Model.h"

Model::Model() :
	lightPos(0.0f, 5.0f, 0.0f),
	lightColour(1.0f, 1.0f, 1.0f)
{}

bool Model::LoadModel(const char* filePath, int modelID) {
	
	pointCount[modelID] = 0;
	const aiScene* scene = aiImportFile(filePath, aiProcess_Triangulate);

	if (!scene) {
		fprintf(stderr, "ERROR: reading mesh %s\n", filePath);
		return false;
	}

	printf("  %i materials\n", scene->mNumMaterials);
	printf("  %i meshes\n", scene->mNumMeshes);

	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {
		const aiMesh* mesh = scene->mMeshes[m_i];
		printf("    %i vertices in mesh\n", mesh->mNumVertices);
		pointCount[modelID] += mesh->mNumVertices;
		for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {
			if (mesh->HasPositions()) {
				const aiVector3D* vp = &(mesh->mVertices[v_i]);
				points[modelID].push_back(vp->x);
				points[modelID].push_back(vp->y);
				points[modelID].push_back(vp->z);
			}
			if (mesh->HasNormals()) {
				const aiVector3D* vn = &(mesh->mNormals[v_i]);
				normals[modelID].push_back(vn->x);
				normals[modelID].push_back(vn->y);
				normals[modelID].push_back(vn->z);
			}
			if (mesh->HasTextureCoords(0)) {
				const aiVector3D* vt = &(mesh->mTextureCoords[0][v_i]);
				textures[modelID].push_back(vt->x);
				textures[modelID].push_back(vt->y);
			}
		}
	}
	aiReleaseImport(scene);
	return true;
}

void Model::ObjectBuffer(const char* filePath, int modelID, GLuint shaderProgramID, bool textured) {

	LoadModel(filePath, modelID);

	int positionID = glGetAttribLocation(shaderProgramID, "vertex_position");
	int normalID = glGetAttribLocation(shaderProgramID, "vertex_normal");

	unsigned int vp_vbo = VAO[modelID];
	glGenBuffers(1, &vp_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glBufferData(GL_ARRAY_BUFFER, pointCount[modelID] * 3 * sizeof(float), &points[modelID][0], GL_STATIC_DRAW);
	unsigned int vn_vbo = VAO[modelID];
	glGenBuffers(1, &vn_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glBufferData(GL_ARRAY_BUFFER, pointCount[modelID] * 3 * sizeof(float), &normals[modelID][0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO[modelID]);
	glBindVertexArray(VAO[modelID]);

	glEnableVertexAttribArray(positionID);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(normalID);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	if (textured) {
		int textureID = glGetAttribLocation(shaderProgramID, "vertex_texture");

		unsigned int vt_vbo = VAO[modelID];
		glGenBuffers(1, &vt_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vt_vbo);
		glBufferData(GL_ARRAY_BUFFER, pointCount[modelID] * 2 * sizeof(float), &textures[modelID][0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(textureID);
		glBindBuffer(GL_ARRAY_BUFFER, vt_vbo);
		glVertexAttribPointer(textureID, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
}

void Model::BindTexture(GLenum textureUnit, int texNum) {

	texture[texNum].Bind(textureUnit, texNum);
}

void Model::LoadTexture(const char* fileName, int texNum) {

	if (!texture[texNum].Load(fileName, texNum)) {
		cout << "Could not load texture." << endl;
	}
}

void Model::DrawModel(int modelID, GLuint shaderProgramID, mat4 projection, mat4 view, vec3 camPosition, vec3 modelColour) {

	glUseProgram(shaderProgramID);
	matLocation = glGetUniformLocation(shaderProgramID, "model");
	viewLocation = glGetUniformLocation(shaderProgramID, "view");
	projLocation = glGetUniformLocation(shaderProgramID, "proj");
	viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	modelColourLocation = glGetUniformLocation(shaderProgramID, "modelColour");
	lightColourLocation = glGetUniformLocation(shaderProgramID, "lightColour");
	lightLocation = glGetUniformLocation(shaderProgramID, "lightPos");

	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, &model[modelID][0][0]);
	glBindVertexArray(VAO[modelID]);
	glDrawArrays(GL_TRIANGLES, 0, pointCount[modelID]);

	glUniform3f(viewPosLocation, camPosition.x, camPosition.y, camPosition.z); 
	glUniform3f(modelColourLocation, modelColour.x, modelColour.y, modelColour.z);
	glUniform3f(lightColourLocation, lightColour.x, lightColour.y, lightColour.z);
	glUniform3f(lightLocation, lightPos.x, lightPos.y, lightPos.z);
}

void Model::DrawTexturedModel(int modelID, GLuint shaderProgramID, int texNum, mat4 projection, mat4 view, vec3 camPosition) {

	glUseProgram(shaderProgramID);
	matLocation = glGetUniformLocation(shaderProgramID, "model");
	viewLocation = glGetUniformLocation(shaderProgramID, "view");
	projLocation = glGetUniformLocation(shaderProgramID, "proj");
	viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	lightColourLocation = glGetUniformLocation(shaderProgramID, "lightColour");
	lightLocation = glGetUniformLocation(shaderProgramID, "lightPos");

	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, &model[modelID][0][0]);
	glBindVertexArray(VAO[modelID]);
	BindTexture(GL_TEXTURE0, texNum);
	glDrawArrays(GL_TRIANGLES, 0, pointCount[modelID]);

	glUniform3f(viewPosLocation, camPosition.x, camPosition.y, camPosition.z);
	glUniform3f(lightColourLocation, lightColour.x, lightColour.y, lightColour.z);
	glUniform3f(lightLocation, lightPos.x, lightPos.y, lightPos.z);
}

void Model::DrawHierarchalModel(int modelID, mat4 parent, GLuint shaderProgramID, mat4 projection, mat4 view, vec3 camPosition, vec3 modelColour) {

	glUseProgram(shaderProgramID);
	matLocation = glGetUniformLocation(shaderProgramID, "model");
	viewLocation = glGetUniformLocation(shaderProgramID, "view");
	projLocation = glGetUniformLocation(shaderProgramID, "proj");
	viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	modelColourLocation = glGetUniformLocation(shaderProgramID, "modelColour");
	lightColourLocation = glGetUniformLocation(shaderProgramID, "lightColour");
	lightLocation = glGetUniformLocation(shaderProgramID, "lightPos");

	mat4 global = model[modelID] * parent;

	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, &global[0][0]);
	glBindVertexArray(VAO[modelID]);
	glDrawArrays(GL_TRIANGLES, 0, pointCount[modelID]);

	glUniform3f(viewPosLocation, camPosition.x, camPosition.y, camPosition.z);
	glUniform3f(modelColourLocation, modelColour.x, modelColour.y, modelColour.z);
	glUniform3f(lightColourLocation, lightColour.x, lightColour.y, lightColour.z);
	glUniform3f(lightLocation, lightPos.x, lightPos.y, lightPos.z);
}

void Model::DrawSkybox(int modelID, GLuint shaderProgramID, int texNum, mat4 projection, mat4 view) {

	glDepthMask(GL_FALSE);
	glUseProgram(shaderProgramID);
	matLocation = glGetUniformLocation(shaderProgramID, "model");
	viewLocation = glGetUniformLocation(shaderProgramID, "view");
	projLocation = glGetUniformLocation(shaderProgramID, "proj");

	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, &model[modelID][0][0]);
	glBindVertexArray(VAO[modelID]);
	BindTexture(GL_TEXTURE0, texNum);
	glDrawArrays(GL_TRIANGLES, 0, pointCount[modelID]);
	glDepthMask(GL_TRUE);
}

void Model::Translate1(int modelID, float x, float y, float z) {

	model[modelID] = glm::translate(model[modelID], vec3(x, y, z));
}

void Model::Translate2(int modelID, float x, float y, float z) {

	model[modelID] = glm::translate(mat4(), vec3(x, y, z));
}

void Model::Rotate1(int modelID, float degrees, float x, float y, float z) {

	model[modelID] = glm::rotate(model[modelID], degrees,vec3(x, y, z));
}

void Model::Rotate2(int modelID, float degrees, float x, float y, float z) {

	model[modelID] = glm::rotate(mat4(), degrees, vec3(x, y, z));
}

void Model::Scale1(int modelID, float scale) {
	
	model[modelID] = glm::scale(model[modelID], vec3(scale));
}

void Model::Scale2(int modelID, float scale) {
	
	model[modelID] = glm::scale(mat4(), vec3(scale));
}