/// \file Game.cpp
/// \brief Code for the game class CGame.

#include "Game.h"

#include "GameDefines.h"
#include "SpriteRenderer.h"
#include "ComponentIncludes.h"
#include "ParticleEngine.h"
#include "TileManager.h"
#include "shellapi.h"
#include <fstream>
#include <iostream>

/// Delete the renderer, the object manager, and the tile manager. The renderer
/// needs to be deleted before this destructor runs so it will be done elsewhere.

CGame::~CGame(){
  delete m_pParticleEngine;
  delete m_pObjectManager;
  delete m_pTileManager;
  delete pMap;
} //destructor

/// Initialize the renderer, the tile manager and the object manager, load 
/// images and sounds, and begin the game.

void CGame::Initialize(){
  m_pRenderer = new LSpriteRenderer(eSpriteMode::Batched2D); 
  m_pRenderer->Initialize(eSprite::Size); 
  LoadImages(); //load images from xml file list
  
  m_pTileManager = new CTileManager((size_t)m_pRenderer->GetWidth(eSprite::BlueTile) * .5f);
  //m_pTileManager = new CTileManager();
  m_pObjectManager = new CObjectManager; //set up the object manager 
  LoadSounds(); //load the sounds for this game

  m_pParticleEngine = new LParticleEngine2D(m_pRenderer);

  pMap = new mapGen();
  pWave = new WaveManager();

  for (int i = 0; i < 17; i++) {
	  TowerGUIS.push_back(i);
  }

  TowerDesc.m_nSpriteIndex = (UINT)eSprite::Tower;

  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2);

  Menus[0] = true;
  Menus[1] = false;
  Menus[2] = false;
  Menus[3] = false;

  MenuButtonNums[0] = 0;
  MenuButtonNums[1] = 0;
  MenuButtonNums[2] = 0;
  MenuButtonNums[3] = 0;

  m_pAudio->stop();
  m_pAudio->loop(eSound::MenuMusic);

  MainMenu();
} //Initialize

/// Load the specific images needed for this game. This is where `eSprite`
/// values from `GameDefines.h` get tied to the names of sprite tags in
/// `gamesettings.xml`. Those sprite tags contain the name of the corresponding
/// image file. If the image tag or the image file are missing, then the game
/// should abort from deeper in the Engine code leaving you with an error
/// message in a dialog box.

void CGame::LoadImages(){  
  m_pRenderer->BeginResourceUpload();

  m_pRenderer->Load(eSprite::Background, "Background");
  m_pRenderer->Load(eSprite::Background2, "Background2");
  m_pRenderer->Load(eSprite::BlueTile, "BlueTile");
  m_pRenderer->Load(eSprite::BrownTile, "BrownTile");
  m_pRenderer->Load(eSprite::GrayTile, "GrayTile");
  m_pRenderer->Load(eSprite::RedTile, "RedTile");
  m_pRenderer->Load(eSprite::Tselect, "Tselect");
  m_pRenderer->Load(eSprite::Tunselect, "Tunselect");
  m_pRenderer->Load(eSprite::MenuUButton, "MenuUButton");
  m_pRenderer->Load(eSprite::MenuPButton, "MenuPButton");
  m_pRenderer->Load(eSprite::MenuCursor, "MenuCursor");
  m_pRenderer->Load(eSprite::Player,  "player");
  m_pRenderer->Load(eSprite::Bullet,  "bullet");
  m_pRenderer->Load(eSprite::Bullet2, "bullet2");
  m_pRenderer->Load(eSprite::Smoke,   "smoke");
  m_pRenderer->Load(eSprite::Spark,   "spark");
  m_pRenderer->Load(eSprite::Turret,  "turret");
  m_pRenderer->Load(eSprite::Line,    "greenline"); 
  m_pRenderer->Load(eSprite::Tower,   "Tower");


  m_pRenderer->EndResourceUpload();
} //LoadImages

/// Initialize the audio player and load game sounds.

void CGame::LoadSounds(){
  m_pAudio->Initialize(eSound::Size);

  m_pAudio->Load(eSound::Grunt, "grunt");
  m_pAudio->Load(eSound::Clang, "clang");
  m_pAudio->Load(eSound::Gun, "gun");
  m_pAudio->Load(eSound::Ricochet, "ricochet");
  m_pAudio->Load(eSound::Start, "start");
  m_pAudio->Load(eSound::Boom, "boom");
  m_pAudio->Load(eSound::MenuMusic, "MenuMusic");
  m_pAudio->Load(eSound::BossWave, "BossWave");
} //LoadSounds

/// Release all of the DirectX12 objects by deleting the renderer.

void CGame::Release(){
  delete m_pRenderer;
  m_pRenderer = nullptr; //for safety
} //Release

/// Ask the object manager to create a player object and turrets specified by
/// the tile manager.

void CGame::CreateObjects(){
  std::vector<Vector2> turretpos; //vector of turret positions
  Vector2 playerpos; //player positions
  m_pTileManager->GetObjects(turretpos, playerpos); //get positions
  
  m_pPlayer = (CPlayer*)m_pObjectManager->create(eSprite::Player, playerpos);

  for(const Vector2& pos: turretpos)
    m_pObjectManager->create(eSprite::Turret, pos);
} //CreateObjects

void CGame::MainMenu() {
	pWave->resetWaveManager();
    m_pParticleEngine->clear(); //clear old particles
    m_pObjectManager->clear(); //clear old objects
    m_bScreenText = false;

    pMap->createBlankMap();
    m_pTileManager->LoadEmptyMap(pMap->getTileMap());

    for (int i = enemies.size() - 1; i >= 0; i--) {
        delete enemies[i];
    }
    enemies.clear();
    for (int i = baseTowers.size() - 1; i >= 0; i--) {
        delete baseTowers[i];
    }
    baseTowers.clear();

    m_eGameState = eGameState::Waiting;
}

void CGame::LevelMenu() {
    m_pParticleEngine->clear(); //clear old particles
    m_pObjectManager->clear(); //clear old objects


}

void CGame::Settings() {
    m_pParticleEngine->clear(); //clear old particles
    m_pObjectManager->clear(); //clear old objects


}

void CGame::Help() {
    m_pParticleEngine->clear(); //clear old particles
    m_pObjectManager->clear(); //clear old objects


}

/// Call this function to start a new game. This should be re-entrant so that
/// you can restart a new game without having to shut down and restart the
/// program. Clear the particle engine to get rid of any existing particles,
/// delete any old objects out of the object manager and create some new ones.

void CGame::BeginGame(){  
  m_pParticleEngine->clear(); //clear old particles
  FirstTowerSet = true;
//just something to commit
  for (int i = enemies.size() - 1; i >= 0; i--) {
      delete enemies[i];
  }
  enemies.clear();

  for (int i = baseTowers.size() - 1; i >= 0; i--) {
	  delete baseTowers[i];
  }
  baseTowers.clear();

  pMap->createNewMap();
  m_pTileManager->LoadMap(pMap->getTileMap());

  // just so I could see the path coords
  ofstream file("mapOutput.txt");
  streambuf* buf = cout.rdbuf();
  cout.rdbuf(file.rdbuf());

  pMap->printPath();
  
  m_pObjectManager->clear(); //clear old objects
  CreateObjects(); //create new objects (must be after map is loaded) 
  m_pAudio->stop();
  m_pAudio->loop(eSound::BossWave);
  //m_pAudio->stop(); //stop all currently playing sounds
  //m_pAudio->play(eSound::Start); //play start-of-game sound
  m_eGameState = eGameState::Playing; //now playing
  //DrawVariablesToScreen();
  m_bScreenText = true;

  pair<int, int> startLocation = pMap->getStartPoint();

  auto startPoint = pMap->getStartPoint();
  //m_pEnemy = new CEnemy(CEnemy::GetPos(startPoint));
  //enemies.push_back(new CEnemy(CEnemy::GetPos(startPoint)));

} //BeginGame

/// Poll the keyboard state and respond to the key presses that happened since
/// the last frame.

void CGame::KeyboardHandler(){
  m_pKeyboard->GetState(); //get current keyboard state
  if (m_eGameState == eGameState::Waiting) {
	  if (Menus[0]) {
		  if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[0] == 0) { //Level menu
			  //m_nNextLevel = (m_nNextLevel + 1) % 4;
			  MenuButtonNums[0] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[1]));
			  Menus[0] = false;
			  //Menus[1] = true;
			  BeginGame();
		  } //if
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[0] == 1) { //settings menu
			  //m_nNextLevel = (m_nNextLevel + 1) % 4;
			  MenuButtonNums[0] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[2]));
			  Menus[0] = false;
			  Menus[2] = true;
		  } //if
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[0] == 2) { //help screen
			  //m_nNextLevel = (m_nNextLevel + 1) % 4;
			  MenuButtonNums[0] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[3]));
			  Menus[0] = false;
			  Menus[3] = true;
		  } //if

		  if ((m_pKeyboard->TriggerDown('W') || m_pKeyboard->TriggerDown(VK_UP)) && MenuButtonNums[0] != 0) {
			  MenuButtonNums[0] -= 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[0]));
		  }
		  if ((m_pKeyboard->TriggerDown('S') || m_pKeyboard->TriggerDown(VK_DOWN)) && MenuButtonNums[0] != 2) {
			  MenuButtonNums[0] += 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[0]));
		  }
	  }
	  else if (Menus[1]) {
		  if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[1] == 0) {
			  //m_nNextLevel = (m_nNextLevel + 1) % 4;
			  MenuButtonNums[1] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[0]));
			  Menus[1] = false;
			  BeginGame();
		  } //if
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[1] == 2) {
			  MenuButtonNums[1] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[0]));
			  Menus[0] = true;
			  Menus[1] = false;
		  }

		  if ((m_pKeyboard->TriggerDown('W') || m_pKeyboard->TriggerDown(VK_UP)) && MenuButtonNums[1] != 0) {
			  MenuButtonNums[1] -= 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[1]));
		  }
		  if ((m_pKeyboard->TriggerDown('S') || m_pKeyboard->TriggerDown(VK_DOWN)) && MenuButtonNums[1] != 2) {
			  MenuButtonNums[1] += 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[1]));
		  }
	  }
	  else if (Menus[2]) {
		  if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[2] == 0) {
			  //m_nNextLevel = (m_nNextLevel + 1) % 4;
		  } //if
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[2] == 2) {
			  //m_nNextLevel = (m_nNextLevel + 1) % 4;
			  MenuButtonNums[2] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[0]));
			  Menus[0] = true;
			  Menus[2] = false;
		  } //if

		  if ((m_pKeyboard->TriggerDown('W') || m_pKeyboard->TriggerDown(VK_UP)) && MenuButtonNums[2] != 0) {
			  MenuButtonNums[2] -= 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[2]));
		  }
		  if ((m_pKeyboard->TriggerDown('S') || m_pKeyboard->TriggerDown(VK_DOWN)) && MenuButtonNums[2] != 2) {
			  MenuButtonNums[2] += 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[2]));
		  }
	  }
	  else if (Menus[3]) {
		  if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[3] == 0) {
			  //m_nNextLevel = (m_nNextLevel + 1) % 4;
		  } //if
		  else if (m_pKeyboard->TriggerDown(VK_RETURN) && MenuButtonNums[3] == 2) {
			  //m_nNextLevel = (m_nNextLevel + 1) % 4;
			  MenuButtonNums[3] = 0;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[0]));
			  Menus[0] = true;
			  Menus[3] = false;
		  } //if

		  if ((m_pKeyboard->TriggerDown('W') || m_pKeyboard->TriggerDown(VK_UP)) && MenuButtonNums[3] != 0) {
			  MenuButtonNums[3] -= 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[3]));
		  }
		  if ((m_pKeyboard->TriggerDown('S') || m_pKeyboard->TriggerDown(VK_DOWN)) && MenuButtonNums[3] != 2) {
			  MenuButtonNums[3] += 1;
			  cursorPos = Vector2(m_nWinWidth / 2 - 200, m_nWinHeight / 2 - (125 * MenuButtonNums[3]));
		  }
	  }
  }
  else if (m_eGameState == eGameState::Playing) {
	  if (m_pKeyboard->TriggerDown(VK_RETURN) && m_bGodMode) {
		  //m_nNextLevel = (m_nNextLevel + 1) % 4;
		  pWave->resetWaveManager();
		  BeginGame();
	  } //if
	  if (m_pKeyboard->TriggerDown(VK_SPACE)) {
		  m_pPlayer->AddCurrency(1000);
		  m_bGodMode = !m_bGodMode;
	  }
	  //Kill Switch... I Got Tired Of Waiting To Die
	  if (m_pKeyboard->Down(VK_CONTROL) && m_pKeyboard->Down('K') && m_bGodMode) {
		  m_pPlayer->RemoveLives(1000);
		  m_bGodMode = !m_bGodMode;
	  }

	  if (m_pKeyboard->TriggerDown(VK_F1)) //help
		  ShellExecute(0, 0, "https://larc.unt.edu/code/topdown/", 0, 0, SW_SHOW);

	  if (m_pKeyboard->TriggerDown(VK_F2)) //toggle frame rate
		  m_bDrawFrameRate = !m_bDrawFrameRate;

	  if (m_pKeyboard->TriggerDown(VK_F3)) //toggle AABB drawing
		  m_bDrawAABBs = !m_bDrawAABBs;

	  //-----------------------------------------------------------------------------------------
	  //Player controls to move from tile to tile
	  //Move Player Right
	  if (m_pKeyboard->TriggerDown('D')) {
		  m_pPlayer->MoveRight();
		  m_pPlayer->move();
		  m_pPlayer->StopRight();
	  }
	  if (m_pKeyboard->TriggerDown(VK_RIGHT)) {
		  m_pPlayer->MoveRight();
		  m_pPlayer->move();
		  m_pPlayer->StopRight();
	  }
	  //Move Player Left
	  if (m_pKeyboard->TriggerDown('A')) {
		  m_pPlayer->MoveLeft();
		  m_pPlayer->move();
		  m_pPlayer->StopLeft();
	  }
	  if (m_pKeyboard->TriggerDown(VK_LEFT)) {
		  m_pPlayer->MoveLeft();
		  m_pPlayer->move();
		  m_pPlayer->StopLeft();
	  }
	  //Move Player Down
	  if (m_pKeyboard->TriggerDown('W')) {
		  m_pPlayer->MoveDown();
		  m_pPlayer->move();
		  m_pPlayer->StopDown();
	  }
	  if (m_pKeyboard->TriggerDown(VK_UP)) {
		  m_pPlayer->MoveDown();
		  m_pPlayer->move();
		  m_pPlayer->StopDown();
	  }
	  //Move Player Up
	  if (m_pKeyboard->TriggerDown('S')) {
		  m_pPlayer->MoveUp();
		  m_pPlayer->move();
		  m_pPlayer->StopUp();
	  }
	  if (m_pKeyboard->TriggerDown(VK_DOWN)) {
		  m_pPlayer->MoveUp();
		  m_pPlayer->move();
		  m_pPlayer->StopUp();
	  }
	  //-----------------------------------------------------------------------------------------
	  //Controls for the player to place tower
	  //Tower 1/9 Placement
	  if (m_pKeyboard->TriggerDown('1'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(1) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(15);
					  }
					  baseTowers.push_back(new CTower(1, i, j, m_pPlayer->m_vPos));
				  }
				  else if (m_pPlayer->PlaceTower(9) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(275);
					  }
					  baseTowers.push_back(new CTower(9, i, j, m_pPlayer->m_vPos));
				  }
			  }
			  
		  }
	  //Tower 2/10 Placement
	  if (m_pKeyboard->TriggerDown('2'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(2) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(25);
					  }
					  baseTowers.push_back(new CTower(2, i, j, m_pPlayer->m_vPos));
				  }
				  else if (m_pPlayer->PlaceTower(10) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(345);
					  }
					  baseTowers.push_back(new CTower(10, i, j, m_pPlayer->m_vPos));
				  }
			  }
		  }
	  //Tower 3/11 Placement
	  if (m_pKeyboard->TriggerDown('3'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(3) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(40);
					  }
					  baseTowers.push_back(new CTower(3, i, j, m_pPlayer->m_vPos));
				  }
				  else if (m_pPlayer->PlaceTower(11) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(400);
					  }
					  baseTowers.push_back(new CTower(11, i, j, m_pPlayer->m_vPos));
				  }
			  }
		  }
	  //Tower 4/12 Placement
	  if (m_pKeyboard->TriggerDown('4'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(4) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(60);
					  }
					  baseTowers.push_back(new CTower(4, i, j, m_pPlayer->m_vPos));
				  }
				  else if (m_pPlayer->PlaceTower(12) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(475);
					  }
					  baseTowers.push_back(new CTower(12, i, j, m_pPlayer->m_vPos));
				  }
			  }
		  }
	  //Tower 5/13 Placement
	  if (m_pKeyboard->TriggerDown('5'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(5) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(75);
					  }
					  baseTowers.push_back(new CTower(5, i, j, m_pPlayer->m_vPos));
				  }
				  else if (m_pPlayer->PlaceTower(13) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(555);
					  }
					  baseTowers.push_back(new CTower(13, i, j, m_pPlayer->m_vPos));
				  }
			  }
		  }
	  //Tower 6/14 Placement
	  if (m_pKeyboard->TriggerDown('6'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(6) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(100);
					  }
					  baseTowers.push_back(new CTower(6, i, j, m_pPlayer->m_vPos));
				  }
				  else if (m_pPlayer->PlaceTower(14) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(645);
					  }
					  baseTowers.push_back(new CTower(14, i, j, m_pPlayer->m_vPos));
				  }
			  }
		  }
	  //Tower 7/15 Placement
	  if (m_pKeyboard->TriggerDown('7'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(7) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(150);
					  }
					  baseTowers.push_back(new CTower(7, i, j, m_pPlayer->m_vPos));
				  }
				  else if (m_pPlayer->PlaceTower(15) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(750);
					  }
					  baseTowers.push_back(new CTower(15, i, j, m_pPlayer->m_vPos));
				  }
			  }
		  }
	  //Tower 8/16 Placement
	  if (m_pKeyboard->TriggerDown('8'))
		  if (CheckTile()) {
			  int i = 0;
			  int j = 0;
			  i = m_pPlayer->GetXPos();
			  j = m_pPlayer->GetYPos();
			  if (CheckExistingTower(i, j) == false) {
				  if (m_pPlayer->PlaceTower(8) && FirstTowerSet == true) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(200);
					  }
					  baseTowers.push_back(new CTower(8, i, j, m_pPlayer->m_vPos));
				  }
				  else if (m_pPlayer->PlaceTower(16) && FirstTowerSet == false) {
					  if (m_bGodMode == false) {
						  m_pPlayer->RemoveCurrency(850);
					  }
					  baseTowers.push_back(new CTower(16, i, j, m_pPlayer->m_vPos));
				  }
			  }
		  }
	  //Tower Switch Button
	  if (m_pKeyboard->TriggerDown('0')) {
		  if (FirstTowerSet != true) FirstTowerSet = true;
		  else {
			  FirstTowerSet = false;
		  }
	  }

	  //-----------------------------------------------------------------------------------------
	  //Debug Controls
	  if (m_pKeyboard->TriggerDown(VK_F1)) //help
		  ShellExecute(0, 0, "https://larc.unt.edu/code/topdown/", 0, 0, SW_SHOW);

	  if (m_pKeyboard->TriggerDown(VK_F2)) //toggle frame rate
		  m_bDrawFrameRate = !m_bDrawFrameRate;

	  if (m_pKeyboard->TriggerDown(VK_F3)) //toggle AABB drawing
		  m_bDrawAABBs = !m_bDrawAABBs;

	  //-----------------------------------------------------------------------------------------
	  if (m_pKeyboard->TriggerDown(VK_BACK)) //start game
		  BeginGame();

	  if (m_pKeyboard->TriggerDown('E')) {
		  //eCounter = 0;
		  //auto startPoint = pMap->getStartPoint();
		  pWave->nextWave(pMap->getStartPoint());
		  //m_pEnemy = new CEnemy(CEnemy::GetPos(startPoint));
		  //for (int i = 0; i <= 0; i++) {
			  //eCounter = 0;
			  //auto startPoint = pMap->getStartPoint();
			  //m_pEnemy = new CEnemy(CEnemy::GetPos(startPoint));
			  //for (int i = 0; i <= 0; i++) {
				  //enemies.push_back(new CEnemy(CEnemy::GetPos(startPoint)));
			  //}
		  //}
	  }
  }
} //KeyboardHandler

/// Poll the XBox controller state and respond to the controls there.

void CGame::ControllerHandler(){
  if(!m_pController->IsConnected())return;

  m_pController->GetState(); //get state of controller's controls 
} //ControllerHandler

/// Draw the current frame rate to a hard-coded position in the window.
/// The frame rate will be drawn in a hard-coded position using the font
/// specified in `gamesettings.xml`.

void CGame::DrawFrameRateText(){
  const std::string s = std::to_string(m_pTimer->GetFPS()) + " fps"; //frame rate
  const Vector2 pos(m_nWinWidth - 128.0f, 30.0f); //hard-coded position
  m_pRenderer->DrawScreenText(s.c_str(), pos, Colors::White); //draw to screen
} //DrawFrameRateText

/// Draw the god mode text to a hard-coded position in the window using the
/// font specified in `gamesettings.xml`.

void CGame::DrawGodModeText(){
  const Vector2 pos(32.0f, 5.0f); //hard-coded position
  m_pRenderer->DrawScreenText("God Mode", pos, Colors::Red); //draw to screen
} //DrawGodModeText

/// Ask the object manager to draw the game objects. The renderer is notified of
/// the start and end of the frame so that it can let Direct3D do its
/// pipelining jiggery-pokery.

void CGame::RenderFrame(){
  m_pRenderer->BeginFrame(); //required before rendering

  if (m_eGameState == eGameState::Waiting) {
	  m_pRenderer->Draw(eSprite::Background, m_vWinCenter); //draw background
	  m_pRenderer->Draw(eSprite::Background2, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 15)); //draw background  
  }
  else {
	  m_pRenderer->Draw(eSprite::Background, Vector2(m_vWorldSize.x / 2.0f, m_vWorldSize.y / 2.0f)); //draw background
  }

  if (Menus[0]) { //Main Menu
      m_pRenderer->Draw(eSprite::MenuCursor, cursorPos);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2));
      m_pRenderer->DrawScreenText("Start Game", Vector2(m_nWinWidth / 2 - 80, m_nWinHeight / 2 - 20), Colors::Azure);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 125));
      m_pRenderer->DrawScreenText("Settings", Vector2(m_nWinWidth / 2 - 57, m_nWinHeight / 2 + 105), Colors::Azure);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 250));
      m_pRenderer->DrawScreenText("Help", Vector2(m_nWinWidth / 2 - 35, m_nWinHeight / 2 + 230), Colors::Azure);
  }
  else if (Menus[1]) { //Level Menu
      m_pRenderer->Draw(eSprite::MenuCursor, cursorPos);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2));
      m_pRenderer->DrawScreenText("Start Game", Vector2(m_nWinWidth / 2 - 80, m_nWinHeight / 2 - 20), Colors::Azure);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 250));
      m_pRenderer->DrawScreenText("Back", Vector2(m_nWinWidth / 2 - 40, m_nWinHeight / 2 + 230), Colors::Azure);
  }
  else if (Menus[2]) { //Settings
      m_pRenderer->Draw(eSprite::MenuCursor, cursorPos);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 250));
      m_pRenderer->DrawScreenText("Back", Vector2(m_nWinWidth / 2 - 40, m_nWinHeight / 2 + 230), Colors::Azure);
  }
  else if (Menus[3]) { //Help
      m_pRenderer->Draw(eSprite::MenuCursor, cursorPos);
      m_pRenderer->Draw(eSprite::MenuUButton, Vector2(m_nWinWidth / 2, m_nWinHeight / 2 - 250));
      m_pRenderer->DrawScreenText("Back", Vector2(m_nWinWidth / 2 - 40, m_nWinHeight / 2 + 230), Colors::Azure);
  }

  m_pObjectManager->draw(pMap->getTileColor()); //draw objects
  m_pParticleEngine->Draw(); //draw particles
  if(m_bDrawFrameRate)DrawFrameRateText(); //draw frame rate, if required
  if(m_bGodMode)DrawGodModeText(); //draw god mode text, if required
  if(m_bScreenText)DrawVariablesToScreen(); //draw player variables

  for (int i = 0; i < enemies.size(); i++)
  {
      if (enemies[i] != NULL)
          enemies[i]->draw();
  }

  for (int i = 0; i < baseTowers.size(); i++) {
      if (baseTowers[i] != NULL) {
          baseTowers[i]->draw();
      }
  }
  if (m_eGameState == eGameState::Playing) {
	  if (FirstTowerSet) {
		  m_pRenderer->Draw(eSprite::Tselect, Vector2(-31, m_vWorldSize.y / 2.0f));
		  m_pRenderer->Draw(eSprite::Tunselect, Vector2(m_vWorldSize.x + 31, m_vWorldSize.y / 2.0f));
	  }
	  else {
		  m_pRenderer->Draw(eSprite::Tunselect, Vector2(-31, m_vWorldSize.y / 2.0f));
		  m_pRenderer->Draw(eSprite::Tselect, Vector2(m_vWorldSize.x + 31, m_vWorldSize.y / 2.0f));
	  }
	  for (int i = 0; i < 16; i++) {
		  TowerDesc.m_nCurrentFrame = i;
		  if (i < 8) {
			  TowerDesc.m_vPos = Vector2(-30, (m_vWorldSize.y - 30) - (62 * i));
		  }
		  else{
			  TowerDesc.m_vPos = Vector2((m_vWorldSize.x + 30), (m_vWorldSize.y - 30) - (62 * (i - 8)));
		  }

		  if (FirstTowerSet) {
			  m_pRenderer->Draw(eSprite::MenuCursor, Vector2(-30, m_vWorldSize.y - 528));
		  }
		  else {
			  m_pRenderer->Draw(eSprite::MenuCursor, Vector2((m_vWorldSize.x + 30), m_vWorldSize.y - 528));
		  }

		  m_pRenderer->Draw(&TowerDesc);
	  }
  }

  m_pRenderer->EndFrame(); //required after rendering
} //RenderFrame

/// Make the camera follow the player, but don't let it get too close to the
/// edge unless the world is smaller than the window, in which case we just
/// center everything.

void CGame::FollowCamera(){
  if(m_pPlayer == nullptr)return; //safety

  Vector3 vCameraPos(m_pPlayer->GetPos()); //player position

  if (Menus[0] || Menus[1] || Menus[2] || Menus[3]) {
      vCameraPos.x = m_nWinWidth / 2.0f; // center camera horizontally
      vCameraPos.y = m_nWinHeight / 2.0f; // center camera vertically
  }
  else {
      vCameraPos.x = m_vWorldSize.x / 2.0f; // center camera horizontally
      vCameraPos.y = m_vWorldSize.y / 2.0f; // center camera vertically
  }
  								
  m_pRenderer->SetCameraPos(vCameraPos); //camera to player
} //FollowCamera

/// This function will be called regularly to process and render a frame
/// of animation, which involves the following. Handle keyboard input.
/// Notify the audio player at the start of each frame so that it can prevent
/// multiple copies of a sound from starting on the same frame.  
/// Move the game objects. Render a frame of animation. 

void CGame::ProcessFrame(){
  KeyboardHandler(); //handle keyboard input
  ControllerHandler(); //handle controller input
  m_pAudio->BeginFrame(); //notify audio player that frame has begun
  
  m_pTimer->Tick([&]() { //all time-dependent function calls should go here
	m_pObjectManager->move(); //move all objects
	FollowCamera(); //make camera follow player

    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i] != NULL) //&& eMove == 60)
        {
            //eMove = 0;
            enemies[i]->move();
        }
        //else
            //eMove = eMove + 1;

        if (enemies[i] != NULL && enemies[i]->getIsDead() == true)
        {
			enemyCounter--;
			enemies[i] = NULL;
            delete enemies[i];
        }
    }

	int Esize = enemies.size();
	if (Esize > 0) {
		for (int i = 0; i < Esize; i++) {
			if (enemies[i] == NULL) {
				enemies.erase(enemies.begin() + i);
				Esize = enemies.size();
			}
		}
	}

	for (int i = 0; i < baseTowers.size(); i++) {
		if (enemies.size() > 0) {
			baseTowers[i]->move();
		}
	}

	

    m_pParticleEngine->step(); //advance particle animation
  });

  RenderFrame(); //render a frame of animation
  ProcessGameState(); //check for end of game
} //ProcessFrame

/// Take action appropriate to the current game state. If the game is currently
/// playing, then if the player has been killed or all turrets have been
/// killed, then enter the wait state. If the game has been in the wait
/// state for longer than 3 seconds, then restart the game.

void CGame::ProcessGameState(){
  static float t = 0; //time at start of game

  //SET THIS UP TO WORK WITH LIVES
  switch(m_eGameState){
    case eGameState::Playing:
		delayCounter++;
		if(delayCounter == spawnDelay){
			pWave->spawnWave();
			delayCounter = 0;
		}
      //IF LIVES == 0
      if(m_pPlayer == nullptr || stoi(m_pPlayer->GetLives()) <= 0){
        //m_eGameState = eGameState::Waiting; //now waiting
        t = m_pTimer->GetTime(); //start wait timer
		m_pAudio->stop();
		m_pAudio->loop(eSound::MenuMusic);
        MainMenu();
        Menus[0] = true;
      } //if
      break;

    //KICK BACK TO MAIN MENU OR DEATH SCREEN TO DECIDE TO RESTART OR END GAME.
    case eGameState::Waiting:
      //if(m_pTimer->GetTime() - t > 3.0f){ //3 seconds has elapsed since level end
        //if(m_pObjectManager->GetNumTurrets() == 0) //player won
          //m_nNextLevel = (m_nNextLevel + 1)%4; //advance next level
        //BeginGame(); //restart game
      //} //if
      break;
  } //switch
} //CheckForEndOfGame

void CGame::DrawVariablesToScreen() {
	const Vector2 PlayerPosition(500.0f, 5.0f);
	const Vector2 CurrentCurrency(700.0f, 5.0f);
	const Vector2 Lives(900.0f, 5.0f);
    const Vector2 tAmount(250.0f, 5.0f);
	const Vector2 eAmount(200.0f, 5.0f);
	int enemyNum = enemies.size();
	std::string enemyAmount = to_string(enemyNum);

	m_pRenderer->DrawScreenText(m_pPlayer->GetPlayerPosition().c_str(), PlayerPosition, Colors::Azure);
	m_pRenderer->DrawScreenText(m_pPlayer->GetCurrency().c_str(), CurrentCurrency, Colors::Gold);
	m_pRenderer->DrawScreenText(m_pPlayer->GetLives().c_str(), Lives, Colors::Crimson);
	m_pRenderer->DrawScreenText(m_pPlayer->GetTAmount(baseTowers).c_str(), tAmount, Colors::DarkSeaGreen);
	m_pRenderer->DrawScreenText(enemyAmount.c_str(), eAmount, Colors::Maroon);
}

bool CGame::CheckTile() {
	if (m_pTileManager->GetTile(m_pPlayer->GetXPos(), m_pPlayer->GetYPos()) == 'T') {
		return true;
	}
	else {
		return false;
	}
}

bool CGame::CheckExistingTower(int x, int y) {
	for (int i = 0; i < baseTowers.size(); i++) {
		if (baseTowers[i]->GetXPos() == x && baseTowers[i]->GetYPos() == y) {
			return true;
		}
	}
	return false;
}
