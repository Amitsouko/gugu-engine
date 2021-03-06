#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Utility/Types.h"
#include "Gugu/Utility/DeltaTime.h"
#include "Gugu/Misc/UDim.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>
#include <list>

////////////////////////////////////////////////////////////////
// Forward Declarations

namespace gugu
{
    struct RenderPass;
    class Action;
}

namespace pugi
{
    class xml_node;
}

////////////////////////////////////////////////////////////////
// File Declarations

namespace gugu {

namespace EInteraction
{
    enum Type
    {
        None        = 0x0000,
        
        Disabled    = 0x0001,   // Disable Events on self
        Absorb      = 0x0002,   // Disable Events on children
        
        RawSFEvent  = 0x0004,

        Selection   = 0x0010,
        Focus       = 0x0020,
        Click       = 0x0040,
        Scroll      = 0x0080,
        Drag        = 0x0100,
    };
}

class ElementInteractions
{
public:

    ElementInteractions();
    virtual ~ElementInteractions();
    
    void    SetInteractionFlags     (int _iFlags);
    void    AddInteractionFlag      (EInteraction::Type _eFlag);
    void    RemoveInteractionFlag   (EInteraction::Type _eFlag);

    int     GetInteractionFlags     () const;
    bool    HasInteractionFlags     () const;   //Return true if Interaction flags are set besides Disabled and Absorb
    bool    HasInteractionFlag      (EInteraction::Type _eFlag) const;

    void    AddCallback         (EInteraction::Type _eFlag, Action* _pCallback);
    void    RemoveCallbacks     (EInteraction::Type _eFlag);
    void    RemoveCallbacks     ();
    
    void    FireCallbacks       (EInteraction::Type _eFlag);

private:

    struct CallbackInfos
    {
        EInteraction::Type interactionFlag;
        Action* action;
    };
    
    int m_interactionFlags;
    std::vector<CallbackInfos> m_callbacks;
};

class Element
{
public:

    Element();
    virtual ~Element();

    template<typename T>
    T* AddChild()
    {
        T* pNewChild = new T;
        AddChild( pNewChild );
        return pNewChild;
    }

            void            AddChild                (Element* _pNewChild);
            void            RemoveChild             (Element* _pChild);
            void            DeleteAllChildren       ();
            void            SetParent               (Element* _pNewParent, bool _bUpdateParents = true);
            
            Element*        GetParent               () const;
            Element*        GetTopParent            () const;
            
            int                             GetChildCount    () const;
            const std::vector<Element*>&    GetChildren     () const;

            sf::Vector2f    TransformToLocalFull    (const sf::Vector2f& _oPoint) const;
            sf::Vector2f    TransformToGlobalFull   (const sf::Vector2f& _oPoint) const;  //TODO: Check this works !

            void            SetVisible              (bool _bIsVisible);
            bool            IsVisible               (bool _bCheckParent = true) const;

    virtual void            Step                    (const DeltaTime& dt); //TODO: Remove ? let Actors handle step related stuff ?
    virtual void            Update                  (const DeltaTime& dt); //TODO: Call this from Render instead of additional loop ?

            void            Render                  (RenderPass& _kRenderPass, const sf::Transform& _kTransformParent);

            void            SetUnifiedOrigin            (UDim2 _oNewDimOrigin);
            void            SetUnifiedPosition          (UDim2 _oNewDimPos);
            void            SetUnifiedSize              (UDim2 _oNewDimSize);

            UDim2           GetUnifiedOrigin            () const;
            UDim2           GetUnifiedPosition          () const;
            UDim2           GetUnifiedSize              () const;

            void            OnParentResized             (sf::Vector2f _kOldSize, sf::Vector2f _kNewSize);
            void            ComputeUnifiedOrigin        ();
            void            ComputeUnifiedDimensions    ();

            void                SetPositionX            (float _fPosX);
            void                SetPositionY            (float _fPosY);
            void                SetPosition             (float _fPosX, float _fPosY);
            void                SetPosition             (const sf::Vector2f& _kPosition);
            void                Move                    (float _fOffsetX, float _fOffsetY);
            void                Move                    (const sf::Vector2f& _kOffset);

            const sf::Vector2f& GetPosition             () const;

            void                SetRotation             (float _fAngle);
            void                Rotate                  (float _fAngle);

            float               GetRotation             () const;

            void                SetScaleX               (float _fScaleX);
            void                SetScaleY               (float _fScaleY);
            void                SetScale                (float _fScale);
            void                SetScale                (float _fScaleX, float _fScaleY);
            void                SetScale                (const sf::Vector2f& _kScale);
            void                Scale                   (float _fScaleX, float _fScaleY);
            void                Scale                   (const sf::Vector2f& _kScale);

            sf::Vector2f        GetScale                () const;

            void                SetOriginX              (float _fOriginX);
            void                SetOriginY              (float _fOriginY);
            void                SetOrigin               (float _fOriginX, float _fOriginY);
            void                SetOrigin               (const sf::Vector2f& _kOrigin);

            const sf::Vector2f& GetOrigin               () const;

            const sf::Transform& GetTransform           () const;
            const sf::Transform& GetInverseTransform    () const;

            void                SetSizeX                (float _fNewSizeX);
            void                SetSizeY                (float _fNewSizeY);
            void                SetSize                 (float _fNewSizeX, float _fNewSizeY);
            void                SetSize                 (sf::Vector2f _kNewSize);

            const sf::Vector2f& GetSize                 () const;     //Get Element Size
            sf::Vector2f        GetSizeScaled           () const;     //Get Element Size, with its scale applied (TODO: Useless ?)
            sf::Vector2f        GetSizeOnScreen         () const;     //Get Element Size, with all its upper hierarchy's scales applied (TODO: Useless ?)
            
            void                SetFlipX                (bool _bFlip);  //Flip Top-Bottom
            void                SetFlipY                (bool _bFlip);  //Flip Left-Right
            void                SetFlip                 (bool _bFlipX, bool _bFlipY);

            bool                GetFlipX                () const;
            bool                GetFlipY                () const;

            void            SetZIndex               (int32 _iZIndex);
            int32           GetZIndex               () const;

            void            SortOnZIndex            ();   //recursive

            void            SetRenderPass           (int _iPass);
            void            AddRenderPass           (int _iPass);
            void            RemoveRenderPass        (int _iPass);

            //TODO: Handle shaders properly
            //> Need to share shaders between objects ?
            //> Where/how do I manage/load/delete them ?
            //void          SetShader               (sf::Shader* _pShader);

            void    SetInteractionFlags     (int _iFlags);
            void    AddInteractionFlag      (EInteraction::Type _eFlag);
            void    RemoveInteractionFlag   (EInteraction::Type _eFlag);

            int     GetInteractionFlags     () const;
            bool    HasInteractionFlags     () const;   //Return true if Interaction flags are set besides Disabled and Absorb
            bool    HasInteractionFlag      (EInteraction::Type _eFlag) const;

            virtual void    GetPropagationList  (std::vector<Element*>& _vecPropagationList) {} //Return Elements that are not Children but should have Interactions (like Items)

            void                    InitInteractions    ();
            ElementInteractions*    GetInteractions     () const;

    virtual bool IsPicked           (const sf::Vector2f& _kGlobalCoords) const;

    virtual void OnMouseEnter       () {}
    virtual void OnMouseLeave       () {}

    virtual bool OnMousePressed     () { return true; }
    virtual bool OnMouseReleased    () { return true; }

    virtual bool OnMouseSelected    () { return true; }
    virtual bool OnMouseDeselected  () { return true; }
    
    virtual void OnMouseDragStart   () {}
    virtual void OnMouseDragStop    () {}
    virtual void OnMouseDragMove    () {}

    virtual void OnMouseScrolled    (int _iDelta) {}

    virtual bool OnSFEvent          (const sf::Event& _oSFEvent) { return true; }     //Return true : allow event to be propagated.

    virtual bool LoadFromXml        (const pugi::xml_node& _oNodeElement);

protected:

    virtual void DrawSelf           (RenderPass& _kRenderPass, const sf::Transform& _kTransformSelf) {}
    virtual void OnPreDraw          (RenderPass& _kRenderPass) {}
    virtual void OnPostDraw         (RenderPass& _kRenderPass) {}

    virtual void SetSizeImpl        (sf::Vector2f _kOldSize);

    static  bool CompareZIndex      (Element* _pLeft, Element* _pRight);

protected:

    //Hierarchy
    Element* m_parent;
    std::vector<Element*> m_children;
    
    //Render
    sf::Transformable   m_transform;
    sf::Vector2f        m_size;
    bool                m_flipX;
    bool                m_flipY;

    int                 m_renderPass;
    bool                m_isVisible;
    int32               m_zIndex;

    //sf::Shader*       m_pShader;

    //Interactions
    ElementInteractions*    m_interactions;

    //UI
    bool        m_useDimOrigin;
    UDim2       m_dimOrigin;
    bool        m_useDimPosition;
    UDim2       m_dimPosition;
    bool        m_useDimSize;
    UDim2       m_dimSize;
};

}   // namespace gugu
