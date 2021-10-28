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

  BeginGame();
} //Initialize

/// Load the specific images needed for this game. This is where `eSprite`
/// values from `GameDefines.h` get tied to the names of sprite tags in
/// `gamesettings.xml`. Those sprite tags contain the name of the corresponding
/// image file. If the image tag or the image file are missing, then the game
/// should abort from deeper in the Engine code leaving you with an error
/// message in a dialog box.

void CGame::LoadImages(){  
  m_pRenderer->BeginResourceUpload();

  m_pRenderer->Load(eSprite::Tile,    "tile");
  m_pRenderer->Load(eSprite::BlueTile,"BlueTile");
  m_pRenderer->Load(eSprite::Player,  "player");
  m_pRenderer->Load(eSprite::Bullet,  "bullet");
  m_pRenderer->Load(eSprite::Bullet2, "bullet2");
  m_pRenderer->Load(eSprite::Smoke,   "smoke");
  m_pRenderer->Load(eSprite::Spark,   "spark");
  m_pRenderer->Load(eSprite::Turret,  "turret");
  m_pRenderer->Load(eSprite::Line,    "greenline"); 

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

/// Call this function to start a new game. This should be re-entrant so that
/// you can restart a new game without having to shut down and restart the
/// program. Clear the particle engine to get rid of any existing particles,
/// delete any old objects out of the object manager and create some new ones.

void CGame::BeginGame(){  
  m_pParticleEngine->clear(); //clear old particles

  pMap->createNewMap();
  m_pTileManager->LoadMap(pMap->getTileMap());

  // just so I could see the path coords
  ofstream file("mapOutput.txt");
  streambuf* buf = cout.rdbuf();
  cout.rdbuf(file.rdbuf());

  pMap->printPath();
  
  m_pObjectManager->clear(); //clear old objects
  CreateObjects(); //create new objects (must be after map is loaded) 
  m_pAudio->stop(); //stop all currently playing sounds
  m_pAudio->play(eSound::Start); //play start-of-game sound
  m_eGameState = eGameState::Playing; //now playing
  //DrawVariablesToScreen();
  m_bScreenText = true;

  pair<int, int> startLocation = pMap->getStartPoint();

  auto startPoint = pMap->getStartPoint();
  //m_pEnemy = new CEnemy(CEnemy::GetPos(startPoint));
  enemies.push_back(new CEnemy(CEnemy::GetPos(startPoint)));

} //BeginGame

/// Poll the keyboard state and respond to the key presses that happened since
/// the last frame.

void CGame::KeyboardHandler(){
  m_pKeyboard->GetState(); //get current keyboard state
  if (m_pKeyboard->TriggerDown(VK_RETURN)) {
	  m_nNextLevel = (m_nNextLevel + 1) % 4;
	  BeginGame();
  } //if
  
  if (m_pKeyboard->TriggerDown(VK_SPACE)) {
	  m_pPlayer->RemoveCurrency(5);
	  m_bGodMode = !m_bGodMode;
  }

  if(m_pKeyboard->TriggerDown(VK_F1)) //help
    ShellExecute(0, 0, "https://larc.unt.edu/code/topdown/", 0, 0, SW_SHOW);
  
  if(m_pKeyboard->TriggerDown(VK_F2)) //toggle frame rate
    m_bDrawFrameRate = !m_bDrawFrameRate;
  
  if(m_pKeyboard->TriggerDown(VK_F3)) //toggle AABB drawing
    m_bDrawAABBs = !m_bDrawAABBs; 

  //-----------------------------------------------------------------------------------------
  //Player controls to move from tile to tile
  //Move Player Right
  if (m_pKeyboard->TriggerDown('D'))
	m_pPlayer->MoveRight();
    m_pPlayer->move();
    m_pPlayer->StopRight();
	
  if (m_pKeyboard->TriggerDown(VK_RIGHT))
	m_pPlayer->MoveRight();
	m_pPlayer->move();
	m_pPlayer->StopRight();
  
  //Move Player Left
  if (m_pKeyboard->TriggerDown('A'))
	m_pPlayer->MoveLeft();
    m_pPlayer->move();
    m_pPlayer->StopLeft();

  if (m_pKeyboard->TriggerDown(VK_LEFT))
	m_pPlayer->MoveLeft();
	m_pPlayer->move();
	m_pPlayer->StopLeft();

  //Move Player Down
  if (m_pKeyboard->TriggerDown('W'))
	m_pPlayer->MoveDown();
    m_pPlayer->move();
    m_pPlayer->StopDown();

  if (m_pKeyboard->TriggerDown(VK_UP))
	m_pPlayer->MoveDown();
	m_pPlayer->move();
	m_pPlayer->StopDown();

  //Move Player Up
  if (m_pKeyboard->TriggerDown('S'))
	m_pPlayer->MoveUp();
    m_pPlayer->move();
    m_pPlayer->StopUp();

  if (m_pKeyboard->TriggerDown(VK_DOWN))
	m_pPlayer->MoveUp();
	m_pPlayer->move();
	m_pPlayer->StopUp();


  //Controls for the player to place tower
  if (m_pKeyboard->TriggerDown('1'))
	  if (CheckTile()) {
		  m_pPlayer->PlaceTower(1);
	  }


  if(m_pKeyboard->TriggerDown(VK_BACK)) //start game
    BeginGame();

  if (m_pKeyboard->TriggerDown('E'))
  {
      eCounter = 0;
      auto startPoint = pMap->getStartPoint();
      //m_pEnemy = new CEnemy(CEnemy::GetPos(startPoint));
      for (int i = 0; i <= 0; i++)
      {
          enemies.push_back(new CEnemy(CEnemy::GetPos(startPoint)));
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
  m_pRenderer->DrawScreenText(s.c_str(), pos); //draw to screen
} //DrawFrameRateText

/// Draw the god mode text to a hard-coded position in the window using the
/// font specified in `gamesettings.xml`.

void CGame::DrawGodModeText(){
  const Vector2 pos(32.0f, 10.0f); //hard-coded position
  //const Vector2 pos2(32.0f, 20.0f); //hard-coded position

  m_pRenderer->DrawScreenText("God Mode", pos); //draw to screen
  //m_pRenderer->DrawScreenText(m_pPlayer->GetCurrency().c_str(), pos2);
  //m_pRenderer->DrawScreenText(m_pPlayer->GetPlayerPosition().c_str(), pos3);
} //DrawGodModeText

/// Ask the object manager to draw the game objects. The renderer is notified of
/// the start and end of the frame so that it can let Direct3D do its
/// pipelining jiggery-pokery.

void CGame::RenderFrame(){
  m_pRenderer->BeginFrame(); //required before rendering

  m_pObjectManager->draw(); //draw objects
  m_pParticleEngine->Draw(); //draw particles
  if(m_bDrawFrameRate)DrawFrameRateText(); //draw frame rate, if required
  if(m_bGodMode)DrawGodModeText(); //draw god mode text, if required
  if(m_bScreenText)DrawVariablesToScreen();

  for (int i = 0; i < enemies.size(); i++)
  {
      if (enemies[i] != NULL)
          enemies[i]->draw();
  }

  m_pRenderer->EndFrame(); //required after rendering
} //RenderFrame

/// Make the camera follow the player, but don't let it get too close to the
/// edge unless the world is smaller than the window, in which case we just
/// center everything.

void CGame::FollowCamera(){
  if(m_pPlayer == nullptr)return; //safety

  Vector3 vCameraPos(m_pPlayer->GetPos()); //player position

  vCameraPos.x = m_vWorldSize.x / 2.0f; // center camera horizontally
  vCameraPos.y = m_vWorldSize.y / 2.0f; // center camera vertically
  
										
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
  
  m_pTimer->Tick([&](){ //all time-dependent function calls should go here
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
            delete enemies[i];
            enemies[i] = NULL;
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
      //IF LIVES == 0
      if(m_pPlayer == nullptr || m_pObjectManager->GetNumTurrets() == 0){
        m_eGameState = eGameState::Waiting; //now waiting
        t = m_pTimer->GetTime(); //start wait timer
      } //if
      break;

    //KICK BACK TO MAIN MENU OR DEATH SCREEN TO DECIDE TO RESTART OR END GAME.
    case eGameState::Waiting:
      if(m_pTimer->GetTime() - t > 3.0f){ //3 seconds has elapsed since level end
        if(m_pObjectManager->GetNumTurrets() == 0) //player won
          m_nNextLevel = (m_nNextLevel + 1)%4; //advance next level
        //BeginGame(); //restart game
      } //if
      break;
  } //switch
} //CheckForEndOfGame

void CGame::DrawVariablesToScreen() {
	const Vector2 PlayerPosition(500.0f, 5.0f);
	const Vector2 CurrentCurrency(700.0f, 5.0f);
	const Vector2 Lives(900.0f, 5.0f);

	m_pRenderer->DrawScreenText(m_pPlayer->GetPlayerPosition().c_str(), PlayerPosition);
	m_pRenderer->DrawScreenText(m_pPlayer->GetCurrency().c_str(), CurrentCurrency);
	m_pRenderer->DrawScreenText(m_pPlayer->GetLives().c_str(), Lives);
}

bool CGame::CheckTile() {
	if (m_pTileManager->GetTile(m_pPlayer->GetXPos(), m_pPlayer->GetYPos() == 'T')) {
		return true;
	}
	else {
		return true;
	}
}
