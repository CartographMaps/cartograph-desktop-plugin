#include "vsplugin.h"

#include <sys/stat.h>

VSPlugin::VSPlugin()
{
}

VSPlugin::~VSPlugin()
{
}

std::vector<VSPlugin::Option*> VSPlugin::getOptions() const
{
    std::vector<VSPlugin::Option*> result;
    result.push_back(new IntOption("red", "Red", m_red, true, 0, 255));
    result.push_back(new IntOption("green", "Green", m_green, true, 0, 255));
    result.push_back(new IntOption("blue", "Blue", m_blue, true, 0, 255));
    return result;
}

void VSPlugin::setIntOption(const std::string& key, int value)
{
    if (strcmp(key.c_str(), "red") == 0)
    {
        m_red = value;
    }
	else if (strcmp(key.c_str(), "green") == 0)
    {
        m_green = value;
    }
	else if (strcmp(key.c_str(), "blue") == 0)
    {
        m_blue = value;
    }
}

std::string VSPlugin::getMapTypeName() const
{
    return "Visual Studio map file";
}

bool VSPlugin::supportsCaching() const
{
	// We do not want Cartograph Maps to cache the generated tiles in this example.
    return false;
}

bool VSPlugin::canOpenMap(const std::string &filename, int fHandle)
{
    // This example uses a dummy file named "vsmapfile.txt"
    return filename.ends_with("vsmapfile.txt");
}

bool VSPlugin::openMap(const std::string &filename, int fHandle)
{
    // In this example we just check if the file exists. For real maps you would open
    // the map file here (e.g., using "fopen").

    // See: https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

bool VSPlugin::closeMap()
{
	return true;
}

std::string VSPlugin::getLastErrorMessage()
{
    return "";
}

bool VSPlugin::usesDirectory() const
{
    return false;
}

std::string VSPlugin::getMapName()
{
    return "VS example mapfile";
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

const uint8_t *VSPlugin::getTileAt(Tile &tile, CalcTool *helper, int* outDataSize)
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
