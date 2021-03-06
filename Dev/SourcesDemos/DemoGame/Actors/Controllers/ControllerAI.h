#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/World/Actor.h"

#include <SFML/System/Vector2.hpp>

////////////////////////////////////////////////////////////////
// Forward Declarations

namespace demoproject
{
    class Character;
}

////////////////////////////////////////////////////////////////
// File Declarations

namespace demoproject {

class ControllerAI : public gugu::Actor
{
public:

    ControllerAI();
    virtual ~ControllerAI();
    
    virtual void Step(const gugu::DeltaTime& dt) override;

public:

    Character* m_character;

    sf::Vector2f m_direction;
    int m_delay;
};

}   //namespace demoproject
