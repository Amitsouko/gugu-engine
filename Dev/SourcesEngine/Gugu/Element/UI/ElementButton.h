#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Element/Element.h"

////////////////////////////////////////////////////////////////
// Forward Declarations

namespace gugu
{
    class ElementSprite;
    class ElementText;
    class Texture;
    class Action;
}

////////////////////////////////////////////////////////////////
// File Declarations

namespace gugu {
    
namespace ETextAlignment {
    enum Type
    {
        Center,
        Left,
        Right,
        Top,
        Bottom,
    };
}

class ElementButton : public Element
{
public:

    ElementButton();
    virtual ~ElementButton();

    void SetTexture(const std::string& _strTexturePathIdle, const std::string& _strTexturePathFocus);
    void SetTexture(Texture* _pTextureIdle, Texture* _pTextureFocused);

    void SetTextureDisabled(const std::string& _strTexture);
    void SetButtonDisabled(bool _bDisabled);

    void SetOnMousePressed(Action* _pActionOnPressed);
    void SetOnMouseReleased(Action* _pActionOnReleased);

    void SetText(const std::string& _strText);

    virtual bool OnMousePressed() override;
    virtual bool OnMouseReleased() override;
    virtual void OnMouseEnter() override;
    virtual void OnMouseLeave() override;

    void SetTextAlignment(ETextAlignment::Type _eAlignX = ETextAlignment::Center, float _fOffsetX = 0.f, ETextAlignment::Type _eAlignY = ETextAlignment::Top, float _fOffsetY = 0.f);

    ElementText* GetElementText() const;
    ElementSprite* GetElementSprite() const;
    
protected:

    virtual void DrawSelf(RenderPass& _kRenderPass, const sf::Transform& _kTransformSelf) override;
    virtual void SetSizeImpl(sf::Vector2f _kOldSize) override;
    
protected:

    ElementSprite* m_sprite;
    Texture* m_textureIdle;
    Texture* m_textureFocused;
    Texture* m_textureDisabled;

    ElementText* m_text;

    Action* m_actionOnPressed;
    Action* m_actionOnReleased;

    bool m_isButtonDisabled;
};

}   // namespace gugu
