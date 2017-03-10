#include "Scene.h"

Scene::Scene() {

	texturedModelShader = NULL;
	skyboxShader = NULL;
}

void Scene::Load() {
	
	texturedModelShader = new Shader(LIGHT_VERTEX_SHADER2, LIGHT_FRAGMENT_SHADER2);
	texturedModelShaderProgramID = texturedModelShader->CompileShaders();

	skyboxShader = new Shader(SKYBOX_VERTEX_SHADER, SKYBOX_FRAGMENT_SHADER);
	skyboxShaderProgramID = skyboxShader->CompileShaders();

	terrain.ObjectBuffer(TERRAIN_MESH, TERRAIN_MODEL, texturedModelShaderProgramID, true);
	terrain.LoadTexture(TERRAIN_TEXTURE, TERRAIN_TEXT);

	road.ObjectBuffer(ROAD_MESH, ROAD_MODEL, texturedModelShaderProgramID, true);
	road.LoadTexture(ROAD_TEXTURE, ROAD_TEXT);
	
	finish.ObjectBuffer(FINISH_MESH, FINISH_MODEL, texturedModelShaderProgramID, true);
	finish.LoadTexture(FINISH_TEXTURE, FINISH_TEXT);

	treeTrunk.ObjectBuffer(TREE_TRUNK_MESH, TREE_TRUNK_MODEL, texturedModelShaderProgramID, true);
	treeTrunk.LoadTexture(BARK_TEXTURE, BARK_TEXT);

	treeLeaves.ObjectBuffer(TREE_LEAVES_MESH, TREE_LEAVES_MODEL, texturedModelShaderProgramID, true);
	treeLeaves.LoadTexture(LEAF_TEXTURE, LEAF_TEXT);
	
	rock.ObjectBuffer(ROCK_MESH, ROCK_MODEL, texturedModelShaderProgramID, true);
	rock.LoadTexture(ROCK_TEXTURE, ROCK_TEXT);

	skyboxFront.ObjectBuffer(SKYBOX_FRONT_MESH, SKYBOX_FRONT_MODEL, skyboxShaderProgramID, true);
	skyboxFront.LoadTexture(SKYBOX_TEXTURE, SKYBOX_TEXT);

	skyboxBack.ObjectBuffer(SKYBOX_BACK_MESH, SKYBOX_BACK_MODEL, skyboxShaderProgramID, true);
	skyboxBack.LoadTexture(SKYBOX_TEXTURE, SKYBOX_TEXT);

	skyboxLeft.ObjectBuffer(SKYBOX_LEFT_MESH, SKYBOX_LEFT_MODEL, skyboxShaderProgramID, true);
	skyboxLeft.LoadTexture(SKYBOX_TEXTURE, SKYBOX_TEXT);

	skyboxRight.ObjectBuffer(SKYBOX_RIGHT_MESH, SKYBOX_RIGHT_MODEL, skyboxShaderProgramID, true);
	skyboxRight.LoadTexture(SKYBOX_TEXTURE, SKYBOX_TEXT);

	skyboxTop.ObjectBuffer(SKYBOX_TOP_MESH, SKYBOX_TOP_MODEL, skyboxShaderProgramID, true);
	skyboxTop.LoadTexture(SKYBOX_TEXTURE, SKYBOX_TEXT);

	skyboxBottom.ObjectBuffer(SKYBOX_BOTTOM_MESH, SKYBOX_BOTTOM_MODEL, skyboxShaderProgramID, true);
	skyboxBottom.LoadTexture(TERRAIN_TEXTURE, TERRAIN_TEXT);

}

void Scene::Draw(mat4 projection, mat4 view, vec3 camPosition) {
	
	terrain.DrawTexturedModel(TERRAIN_MODEL, texturedModelShaderProgramID, TERRAIN_TEXT, projection, view, camPosition);

	road.DrawTexturedModel(ROAD_MODEL, texturedModelShaderProgramID, ROAD_TEXT, projection, view, camPosition);

	finish.DrawTexturedModel(FINISH_MODEL, texturedModelShaderProgramID, FINISH_TEXT, projection, view, camPosition);

	treeTrunk.Translate2(TREE_TRUNK_MODEL, -2.0f, -0.1f, 1.0f);
	treeTrunk.DrawTexturedModel(TREE_TRUNK_MODEL, texturedModelShaderProgramID, BARK_TEXT, projection, view, camPosition);
	treeTrunk.Translate2(TREE_TRUNK_MODEL, 3.5f, -0.1f, -2.0f);
	treeTrunk.DrawTexturedModel(TREE_TRUNK_MODEL, texturedModelShaderProgramID, BARK_TEXT, projection, view, camPosition);
	treeTrunk.Translate2(TREE_TRUNK_MODEL, 4.0f, -0.1f, 5.5f);
	treeTrunk.DrawTexturedModel(TREE_TRUNK_MODEL, texturedModelShaderProgramID, BARK_TEXT, projection, view, camPosition);
	treeTrunk.Translate2(TREE_TRUNK_MODEL, 0.0f, -0.1f, 5.0f);
	treeTrunk.DrawTexturedModel(TREE_TRUNK_MODEL, texturedModelShaderProgramID, BARK_TEXT, projection, view, camPosition);
	treeTrunk.Translate2(TREE_TRUNK_MODEL, -4.0f, -0.1f, -3.0f);
	treeTrunk.DrawTexturedModel(TREE_TRUNK_MODEL, texturedModelShaderProgramID, BARK_TEXT, projection, view, camPosition);
	treeTrunk.Translate2(TREE_TRUNK_MODEL, 0.5f, -0.1f, -2.0f);
	treeTrunk.DrawTexturedModel(TREE_TRUNK_MODEL, texturedModelShaderProgramID, BARK_TEXT, projection, view, camPosition);
	treeTrunk.Translate2(TREE_TRUNK_MODEL, 0.0f, -0.1f, -5.0f);
	treeTrunk.DrawTexturedModel(TREE_TRUNK_MODEL, texturedModelShaderProgramID, BARK_TEXT, projection, view, camPosition);
	treeTrunk.Translate2(TREE_TRUNK_MODEL, 6.3f, -0.1f, -1.6f);
	treeTrunk.DrawTexturedModel(TREE_TRUNK_MODEL, texturedModelShaderProgramID, BARK_TEXT, projection, view, camPosition);

	treeLeaves.Translate2(TREE_LEAVES_MODEL, -2.0f, -0.1f, 1.0f);
	treeLeaves.DrawTexturedModel(TREE_LEAVES_MODEL, texturedModelShaderProgramID, LEAF_TEXT, projection, view, camPosition);
	treeLeaves.Translate2(TREE_LEAVES_MODEL, 3.5f, -0.1f, -2.0f);
	treeLeaves.DrawTexturedModel(TREE_LEAVES_MODEL, texturedModelShaderProgramID, LEAF_TEXT, projection, view, camPosition);
	treeLeaves.Translate2(TREE_LEAVES_MODEL, 4.0f, -0.1f, 5.5f);
	treeLeaves.DrawTexturedModel(TREE_LEAVES_MODEL, texturedModelShaderProgramID, LEAF_TEXT, projection, view, camPosition);
	treeLeaves.Translate2(TREE_LEAVES_MODEL, 0.0f, -0.1f, 5.0f);
	treeLeaves.DrawTexturedModel(TREE_LEAVES_MODEL, texturedModelShaderProgramID, LEAF_TEXT, projection, view, camPosition);
	treeLeaves.Translate2(TREE_LEAVES_MODEL, -4.0f, -0.1f, -3.0f);
	treeLeaves.DrawTexturedModel(TREE_LEAVES_MODEL, texturedModelShaderProgramID, LEAF_TEXT, projection, view, camPosition);
	treeLeaves.Translate2(TREE_LEAVES_MODEL, 0.5f, -0.1f, -2.0f);
	treeLeaves.DrawTexturedModel(TREE_LEAVES_MODEL, texturedModelShaderProgramID, LEAF_TEXT, projection, view, camPosition);
	treeLeaves.Translate2(TREE_LEAVES_MODEL, 0.0f, -0.1f, -5.0f);
	treeLeaves.DrawTexturedModel(TREE_LEAVES_MODEL, texturedModelShaderProgramID, LEAF_TEXT, projection, view, camPosition);
	treeLeaves.Translate2(TREE_LEAVES_MODEL, 6.3f, -0.1f, -1.6f);
	treeLeaves.DrawTexturedModel(TREE_LEAVES_MODEL, texturedModelShaderProgramID, LEAF_TEXT, projection, view, camPosition);
	
	rock.Translate2(ROCK_MODEL, 0.0f, 0.0f, 0.0f);
	rock.DrawTexturedModel(ROCK_MODEL, texturedModelShaderProgramID, ROCK_TEXT, projection, view, camPosition);
	rock.Scale1(ROCK_MODEL, 0.4f);
	rock.Rotate1(ROCK_MODEL, 2.0f, 0.0f, 0.0f, 1.0f);
	rock.Translate1(ROCK_MODEL, 6.0f, 1.5f, 4.0f);
	rock.DrawTexturedModel(ROCK_MODEL, texturedModelShaderProgramID, ROCK_TEXT, projection, view, camPosition);

	skyboxFront.DrawSkybox(SKYBOX_FRONT_MODEL, skyboxShaderProgramID, SKYBOX_TEXT, projection, view);
	skyboxBack.DrawSkybox(SKYBOX_BACK_MODEL, skyboxShaderProgramID, SKYBOX_TEXT, projection, view);
	skyboxLeft.DrawSkybox(SKYBOX_LEFT_MODEL, skyboxShaderProgramID, SKYBOX_TEXT, projection, view);
	skyboxRight.DrawSkybox(SKYBOX_RIGHT_MODEL, skyboxShaderProgramID, SKYBOX_TEXT, projection, view);
	skyboxTop.DrawSkybox(SKYBOX_TOP_MODEL, skyboxShaderProgramID, SKYBOX_TEXT, projection, view);
	skyboxBottom.DrawSkybox(SKYBOX_BOTTOM_MODEL, skyboxShaderProgramID, TERRAIN_TEXT, projection, view);
}