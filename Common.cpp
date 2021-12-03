/// \file Common.cpp
/// \brief Code for the class CCommon.
///
/// This file contains declarations and initial values
/// for CCommon's static member variables.

#include "Common.h"

LSpriteRenderer* CCommon::m_pRenderer = nullptr;
CObjectManager* CCommon::m_pObjectManager = nullptr;
LParticleEngine2D* CCommon::m_pParticleEngine = nullptr;
CTileManager* CCommon::m_pTileManager = nullptr; 

bool CCommon::m_bDrawAABBs = false;
bool CCommon::m_bGodMode = false;
bool CCommon::m_bScreenText = false;
bool CCommon::m_bNormalAssets = true;
bool CCommon::m_bGunSound = true;

WaveManager* CCommon::pWave = nullptr;
mapGen* CCommon::pMap = nullptr;
Vector2 CCommon::m_vWorldSize = Vector2::Zero;
CPlayer* CCommon::m_pPlayer = nullptr;
std::vector<CTower*> CCommon::baseTowers {};
