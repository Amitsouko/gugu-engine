////////////////////////////////////////////////////////////////
// Header

#include "DatasheetBinding.h"

////////////////////////////////////////////////////////////////
// Includes

#include <Gugu/Manager/ManagerResources.h>
#include <Gugu/Utility/System.h>

namespace demoproject {

////////////////////////////////////////////////////////////////
namespace EWeaponType
{
    void Register()
    {
        gugu::DatasheetEnum* datasheetEnum = new gugu::DatasheetEnum;
        datasheetEnum->values.reserve(5);
        datasheetEnum->values.push_back("Unknown");
        datasheetEnum->values.push_back("Sword");
        datasheetEnum->values.push_back("Mace");
        datasheetEnum->values.push_back("Axe");
        datasheetEnum->values.push_back("Crossbow");

        gugu::GetResources()->RegisterDatasheetEnum("weaponType", datasheetEnum);
    }

    gugu::DatasheetEnum* GetDatasheetEnum()
    {
        return gugu::GetResources()->GetDatasheetEnum("weaponType");
    }

    void GetEnumValues(std::vector<EWeaponType::Type>& enumValues)
    {
        enumValues.reserve(5);
        enumValues.push_back(EWeaponType::Unknown);
        enumValues.push_back(EWeaponType::Sword);
        enumValues.push_back(EWeaponType::Mace);
        enumValues.push_back(EWeaponType::Axe);
        enumValues.push_back(EWeaponType::Crossbow);
    }

    size_t GetSize()
    {
        gugu::DatasheetEnum* datasheetEnum = gugu::GetResources()->GetDatasheetEnum("weaponType");
        if (datasheetEnum)
            return datasheetEnum->values.size();
        return 0;
    }
}

////////////////////////////////////////////////////////////////
DS_SpriteInfo::DS_SpriteInfo()
{
    m_imageSet = "";
    m_animSet = "";
}

DS_SpriteInfo::~DS_SpriteInfo()
{
}

void DS_SpriteInfo::ParseMembers(gugu::DatasheetParserContext& context)
{
    gugu::Datasheet::ParseMembers(context);

    ReadString(context, "imageset", m_imageSet);
    ReadString(context, "animset", m_animSet);
}

////////////////////////////////////////////////////////////////
DS_Entity::DS_Entity()
{
    m_name = "Plop";
    m_life = 0;
}

DS_Entity::~DS_Entity()
{
}

void DS_Entity::ParseMembers(gugu::DatasheetParserContext& context)
{
    gugu::Datasheet::ParseMembers(context);

    ReadString(context, "name", m_name);
    ReadInt(context, "life", m_life);
}

////////////////////////////////////////////////////////////////
DS_General::DS_General()
{
    m_speed = 0.f;
    m_isMonarch = false;
    m_faction = nullptr;
    m_sprite = nullptr;
    m_weapon = EWeaponType::Sword;
}

DS_General::~DS_General()
{
    m_faction = nullptr;
    SafeDelete(m_sprite);
    m_factions.clear();
    ClearStdVector(m_sprites);
}

void DS_General::ParseMembers(gugu::DatasheetParserContext& context)
{
    DS_Entity::ParseMembers(context);

    ReadFloat(context, "speed", m_speed);
    ReadBool(context, "is monarch", m_isMonarch);
    ReadReference(context, "faction", m_faction);
    ReadInstance(context, "sprite", "spriteInfo", m_sprite);
    ReadArrayString(context, "names list", m_names);
    ReadArrayInt(context, "stats list", m_stats);
    ReadArrayReference(context, "factions list", m_factions);
    ReadArrayInstance(context, "more sprites", "spriteInfo", m_sprites);
    ReadEnum(context, "weapon", "weaponType", m_weapon);
    ReadArrayEnum(context, "available weapons", "weaponType", m_availableWeapons);
}

////////////////////////////////////////////////////////////////
DS_Faction::DS_Faction()
{
    m_name = "";
    m_leader = nullptr;
}

DS_Faction::~DS_Faction()
{
    m_leader = nullptr;
}

void DS_Faction::ParseMembers(gugu::DatasheetParserContext& context)
{
    gugu::Datasheet::ParseMembers(context);

    ReadString(context, "name", m_name);
    ReadReference(context, "leader", m_leader);
}

////////////////////////////////////////////////////////////////
DS_Troop::DS_Troop()
{
    m_name = "";
}

DS_Troop::~DS_Troop()
{
}

void DS_Troop::ParseMembers(gugu::DatasheetParserContext& context)
{
    gugu::Datasheet::ParseMembers(context);

    ReadString(context, "name", m_name);
}

////////////////////////////////////////////////////////////////
DS_Restriction::DS_Restriction()
{
}

DS_Restriction::~DS_Restriction()
{
}

void DS_Restriction::ParseMembers(gugu::DatasheetParserContext& context)
{
    gugu::Datasheet::ParseMembers(context);

}

////////////////////////////////////////////////////////////////
DS_RestrictionFaction::DS_RestrictionFaction()
{
    m_faction = nullptr;
}

DS_RestrictionFaction::~DS_RestrictionFaction()
{
    m_faction = nullptr;
}

void DS_RestrictionFaction::ParseMembers(gugu::DatasheetParserContext& context)
{
    DS_Restriction::ParseMembers(context);

    ReadReference(context, "faction", m_faction);
}

////////////////////////////////////////////////////////////////
DS_RestrictionTroop::DS_RestrictionTroop()
{
    m_troop = nullptr;
}

DS_RestrictionTroop::~DS_RestrictionTroop()
{
    m_troop = nullptr;
}

void DS_RestrictionTroop::ParseMembers(gugu::DatasheetParserContext& context)
{
    DS_Restriction::ParseMembers(context);

    ReadReference(context, "troop", m_troop);
}

////////////////////////////////////////////////////////////////
DS_Skill::DS_Skill()
{
    m_name = "";
    m_emptyRestriction = nullptr;
    m_singleRestrictionBase = nullptr;
    m_singleRestrictionFaction = nullptr;
}

DS_Skill::~DS_Skill()
{
    SafeDelete(m_emptyRestriction);
    SafeDelete(m_singleRestrictionBase);
    SafeDelete(m_singleRestrictionFaction);
    ClearStdVector(m_restrictions);
}

void DS_Skill::ParseMembers(gugu::DatasheetParserContext& context)
{
    gugu::Datasheet::ParseMembers(context);

    ReadString(context, "name", m_name);
    ReadInstance(context, "empty restriction", "restriction", m_emptyRestriction);
    ReadInstance(context, "single restriction base", "restriction", m_singleRestrictionBase);
    ReadInstance(context, "single restriction faction", "restriction", m_singleRestrictionFaction);
    ReadArrayInstance(context, "restrictions", "restriction", m_restrictions);
}

////////////////////////////////////////////////////////////////
void DatasheetBinding_Register()
{
    EWeaponType::Register();

    gugu::GetResources()->RegisterDatasheetFactory(new gugu::DelegateStatic1P<const std::string&, gugu::Datasheet*>(&DatasheetBinding_InstanciateDatasheet));
}

////////////////////////////////////////////////////////////////
gugu::Datasheet* DatasheetBinding_InstanciateDatasheet(const std::string& classType)
{
    if (classType == "spriteInfo")
    {
        return new DS_SpriteInfo;
    }
    if (classType == "entity")
    {
        return new DS_Entity;
    }
    if (classType == "general")
    {
        return new DS_General;
    }
    if (classType == "faction")
    {
        return new DS_Faction;
    }
    if (classType == "troop")
    {
        return new DS_Troop;
    }
    if (classType == "restriction")
    {
        return new DS_Restriction;
    }
    if (classType == "restrictionFaction")
    {
        return new DS_RestrictionFaction;
    }
    if (classType == "restrictionTroop")
    {
        return new DS_RestrictionTroop;
    }
    if (classType == "skill")
    {
        return new DS_Skill;
    }
    return nullptr;
}

} // namespace demoproject
