#include "vsplugin.h"

VSPlugin::VSPlugin()
{
}

VSPlugin::~VSPlugin()
{
}

std::string VSPlugin::getMapTypeName() const
{
    return "Visual Studio map list";
}

bool VSPlugin::supportsCaching() const
{
	// We do not want Cartograph Maps to cache the generated tiles in this example.
    return false;
}

bool VSPlugin::closeMap()
{
    m_tileBuffer.clear();
	return true;
}

std::string VSPlugin::getLastErrorMessage()
{
    return "";
}

std::string VSPlugin::getMapName()
{
    return m_mapName;
}

std::string VSPlugin::getMapDescription()
{
    return std::string();
}

std::string VSPlugin::getMapCopyright()
{
    return std::string();
}

int VSPlugin::getSupportedTileSize()
{
    return 0;
}

CartographMapInterface::BoundingBox VSPlugin::getMapBoundingBox()
{
	// The map covers the whole world
    return BoundingBox(90.0, -180.0, -90.0, 180.0);
}

CartographMapInterface::ImageFormat VSPlugin::getOutputImageFormat() const
{
    return ImageFormat::RGBA;
}

const uint8_t *VSPlugin::getTileAt(Tile &tile, CalcTool *helper, int * outDataSize)
{
    const size_t tileBufferSize = static_cast<size_t>(4) * tile.tileSize * tile.tileSize;
    if (m_tileBuffer.size() < tileBufferSize)
    {
        m_tileBuffer.resize(tileBufferSize);
    }

    for (size_t i = 0; i < tileBufferSize; )
    {
        m_tileBuffer[i++] = m_red;
        m_tileBuffer[i++] = m_green;
        m_tileBuffer[i++] = m_blue;
        m_tileBuffer[i++] = 255; // alpha
    }

    *outDataSize = tileBufferSize;
    return (const uint8_t*)&m_tileBuffer[0];
}

std::vector<VSPlugin::MapListEntry> VSPlugin::getMaps()
{
    std::vector<MapListEntry> maps;
    maps.push_back(MapListEntry("red", "Red map", "A solid red map"));
    maps.push_back(MapListEntry("green", "Green map", "A solid green map"));
    maps.push_back(MapListEntry("blue", "Blue map", "A solid blue map"));
    return maps;
}

bool VSPlugin::openMap(const std::string& key)
{
    const auto maps = getMaps();
    for (const auto& e : maps)
    {
        if (strcmp(e.key.c_str(), "red") == 0 && key == e.key)
        {
            setMapColor(255, 0, 0);
            m_mapName = e.name;
            return true;
        }
        else if (strcmp(e.key.c_str(), "green") == 0 && key == e.key)
        {
            setMapColor(0, 255, 0);
            m_mapName = e.name;
            return true;
        }
        else if (strcmp(e.key.c_str(), "blue") == 0 && key == e.key)
        {
            setMapColor(0, 0, 255);
            m_mapName = e.name;
            return true;
        }
    }
    return false;
}

void VSPlugin::setMapColor(uint8_t r, uint8_t g, uint8_t b)
{
    m_red = r;
    m_green = g;
    m_blue = b;
}
