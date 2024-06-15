#ifndef VSPLUGIN_H
#define VSPLUGIN_H

#include "../../api/cartographplugin.h"

/*
 * This example generates a one-colored map. 
 */

class VSPlugin : public CartographPluginInterface, public CartographMapListInterface
{
public:
    VSPlugin();
    ~VSPlugin() override;

    // CartographMapInterface interface
public:
    std::string getMapTypeName() const override;
    bool supportsCaching() const override;
    bool closeMap() override;
    std::string getLastErrorMessage() override;
    std::string getMapName() override;
    std::string getMapDescription() override;
    std::string getMapCopyright() override;
    int getSupportedTileSize() override;
    BoundingBox getMapBoundingBox() override;
    ImageFormat getOutputImageFormat() const override;
    const uint8_t *getTileAt(CartographMapInterface::Tile &tile, CalcTool *helper, int* outDataSize) override;

    std::vector<MapListEntry> getMaps() override;

    bool openMap(const std::string& key) override;


private:
    void setMapColor(uint8_t r, uint8_t g, uint8_t b);

private:
    std::vector<uint8_t> m_tileBuffer;
	uint8_t m_red = 255;
    uint8_t m_green = 0;
    uint8_t m_blue = 0;
    std::string m_mapName;

};

/**
 * Create an instance of the plugin.
 */
extern "C" CARTOGRAPH_API CartographPluginInterface *createInstance()
{
    return new VSPlugin();
}

// Supported types (bit wise combination is supported)
extern "C" CARTOGRAPH_API int supportedTypes()
{
    return static_cast<int>(CartographPluginInterface::PluginType::MapList);
}


// A unique (!) identifier for the plugin. This value is never shown to the user.
// If multiple plugins use the same identifier, then the behaviour is undefined.
extern "C" CARTOGRAPH_API const char* uniqueIdentifier()
{
    return "vs_maplist_example_plugin";
}


#endif // VSPLUGIN_H
