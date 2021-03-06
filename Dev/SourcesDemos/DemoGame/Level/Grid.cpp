////////////////////////////////////////////////////////////////
// Header

#include "Gugu/Common.h"
#include "Level/Grid.h"

////////////////////////////////////////////////////////////////
// Includes

#include "Level/Cell.h"

#include "Gugu/Element/Element.h"
#include "Gugu/Element/2D/ElementSprite.h"
#include "Gugu/Element/2D/ElementTileMap.h"
#include "Gugu/World/Level.h"
#include "Gugu/Utility/Random.h"

using namespace gugu;

////////////////////////////////////////////////////////////////
// File Implementation

namespace demoproject {

Grid::Grid()
{
}

Grid::~Grid()
{
}

void Grid::InitGrid(Level* _pLevel, int _iWidth, int _iHeight, float _fCellWidth, float _fCellHeight)
{
    SquareGrid::InitSquareGrid(_iWidth, _iHeight, _fCellWidth, _fCellHeight);
    
    Element* pRoot = _pLevel->GetRootNode()->AddChild<Element>();
    pRoot->SetInteractionFlags(EInteraction::Absorb | EInteraction::Disabled);  //TODO: default on Level nodes ?
    //pRoot->Rotate(45);

    ElementTileMap* pTileMap = pRoot->AddChild<ElementTileMap>();
    pTileMap->SetTexture("LevelFloor.png");
    pTileMap->SetTileCount(m_width, m_height);
    pTileMap->SetTileSize(sf::Vector2f(m_cellWidth, m_cellHeight));

    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            //Cell* pCell = (Cell*)m_aGrid[x][y];     //TODO: I will need a nicier GetCell. Template BaseClass ?

            pTileMap->SetTile(x, y, GetRandom(100) > 5 ? sf::IntRect(0, 0, 16, 16) : sf::IntRect(16, 0, 16, 16));
        }
    }
}

GridCell* Grid::InstantiateCell()
{
    return new Cell;
}

}   //namespace demoproject
