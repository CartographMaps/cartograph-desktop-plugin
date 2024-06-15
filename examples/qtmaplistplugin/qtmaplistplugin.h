#ifndef QtMapListPlugin_H
#define QtMapListPlugin_H

#include "../../api/cartographplugin.h"

#include <QByteArray>

/*
 * This example downloads tiles from OpenStreetMap.org servers.
 */

class QtMapListPlugin : public CartographPluginInterface, public CartographMapListInterface
{
public:
    QtMapListPlugin();
    ~QtMapListPlugin() override;

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
    QByteArray m_tileBuffer;
    bool m_downloadError = false;

};

/**
 * Create an instance of the plugin.
 */
extern "C" CARTOGRAPH_API CartographPluginInterface *createInstance()
{
    return new QtMapListPlugin();
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
    return "qt_maplist_example_plugin";
}


#endif // QtMapListPlugin_H
