#pragma once


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <random>


#include "components/simple_scene.h"


#include "homework_1/actors/actor.h"
#include "homework_1/actors/tank_actor.h"
#include "homework_1/actors/bullet_actor.h"
#include "homework_1/actors/spawn_actor.h"
#include "homework_1/scene/scene.h"
#include "homework_1/utils/transform2D.h"


namespace hw1
{
	// Used for float comparisons: if x - y <= epsilon, treat it as x == y
	static GLfloat epsilon = 0.01f;

	// Used for modifying the velocity of bullets
	static std::pair<GLfloat, GLfloat> gravity = { 0.0f, 10.0f };

	class Homework1 : public gfxc::SimpleScene
	{
	public:
		Homework1();
		~Homework1();

		void Init() override;

	private:
		// Frame rendering functions
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		// Input functions
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		// Menu functions - CLI menu with initial settings
		void PlayerConfig();
		scene::Scene* SelectLevel(std::string name);

		// Setup functions
		void SceneListSetup();
		void MaterialListSetup();
		void MeshSetup();
		void ActorSetup();
		void TrailSetup();

		// Render functions
		void RenderBullets();
		void RenderBullet1();
		void RenderBullet2();

		void RenderPlayers();
		void RenderPlayer1();
		void RenderPlayer2();

		void RenderSpawns();
		void RenderTrails();
		void RenderTrail1();
		void RenderTrail2();

		void RenderScene();
		void RenderLayerSlice(GLuint layerNumber, GLuint k);
		void RenderLayer(GLuint layerNumber);

		// Update functions
		void UpdateActors(GLfloat deltaTime);
		void UpdateTerrain(GLfloat deltaTime);
		void UpdateTerrainHeights(GLfloat deltaTime);
		void UpdateTerrainHit(GLfloat bulletID);

		// Helper functions
		GLfloat GetSceneHeight(GLfloat xPos);
		GLfloat GetSceneHeight(GLuint index);
		void SetSceneHeight(GLuint index, GLfloat newVal);
		GLfloat GetSceneAngle(GLfloat xPos);

		bool CheckForCollision(
			std::pair<GLfloat, GLfloat> aCenter,
			std::pair<GLfloat, GLfloat> bCenter,
			GLfloat aRad,
			GLfloat bRad
		);
		bool CheckForGround(
			std::pair<GLfloat, GLfloat> center,
			GLfloat radius,
			GLfloat height,
			GLfloat width
		);

		// Check if the game is still running
		bool playing;

		// Config variables
		GLuint levelID;
		bool debugMode;
		std::string levelName;
		actors::TankColor colorP1;
		actors::TankColor colorP2;
		GLfloat bulletDamage;
		GLfloat initialHealth;

		// Player variables
		bool renderPlayer1;
		bool renderPlayer2;
		bool renderBullet1;
		bool renderBullet2;
		bool grazePlayer1;
		bool grazePlayer2;

		// Scene variables
		std::vector<scene::Material> materialList; // A vector that holds all available materials
		std::map<scene::LevelType, scene::Scene> sceneList; // A map between level types and their corresponding scenes
		scene::Scene* currentScene; // The scene that is loaded and rendered

		// Actor variables
		std::map<std::string, actors::Actor> actorList; // A vector that holds all actors that will be required
		actors::TankActor* player1; // Player 1
		actors::TankActor* player2; // Player 2
		actors::SpawnActor* spawn1; // Player 1 bullet spawnpoint
		actors::SpawnActor* spawn2; // Player 2 bullet spawnpoint
		actors::BulletActor* bullet1; // Player 1 bullet
		actors::BulletActor* bullet2; // Player 2 bullet
	};
}


