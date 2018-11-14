#include "Terrain.h"

#include <Logger.h>
#include<tinyxml2.h>

#include "../Renderer/Renderer.h"

Terrain::Terrain(const FilePath & filePath)
{
    Load(filePath);
}

void Terrain::Draw(Renderer* pRenderer, const Rect& drawRect)
{
    pRenderer->RenderImage(m_pImage.get(), drawRect);
}

bool Terrain::IsTravelable(Actor * pUnit)
{
    const std::vector<Actor::Tag> unitTags = pUnit->GetTags();
    for (size_t i = 0; i < unitTags.size(); ++i)
    {
        for (size_t j = 0; j < m_preventedUnitTagList.size(); ++j)
        {
            if (unitTags[i] == m_preventedUnitTagList[j])
                return false;
        }
    }
    LOG(Todo, "Optimize unit tag comparison");
    return true;
}

bool Terrain::Load(const FilePath & filePath)
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLElement;

    //Load the file
    XMLDocument toLoad;
    toLoad.LoadFile(filePath.GetFullPath().c_str());

    if (toLoad.Error())
    {
        LOG(Warning, "Failed to load %s", filePath.GetFullPath().c_str());
        return false;
    }

    //Start reading the data
    XMLElement* pRoot = toLoad.RootElement();

    if (pRoot == nullptr || std::string(pRoot->Name()) != "Terrain")
    {
        LOG(Warning, "Invalid root name");
        return false;
    }

    //Image
    XMLElement* pImage = pRoot->FirstChildElement("Image");
    FilePath imageFilePath = filePath;
    imageFilePath.ChangePath(pImage->FirstChild()->Value());
    m_pImage = ResourceCache<Image>::Get(imageFilePath);

    //Prevent Unit
    XMLElement* pPreventedUnit = pRoot->FirstChildElement("PreventedUnit");

    //For every tag detected
    if (pPreventedUnit)
    {
        for (auto pTag = pPreventedUnit->FirstChildElement(); pTag; pTag = pTag->NextSiblingElement())
        {
            //Check validation
            if (std::string(pTag->Value()) != "Tag")
            {
                LOG(Warning, "Invalid Prevented unit child element: %s, only Tag is allowed",
                    pTag->Value());
                continue;
            }

            m_preventedUnitTagList.emplace_back(pTag->FirstChild()->Value());
        }
    }

    return true;
}