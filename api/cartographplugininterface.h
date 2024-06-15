#ifndef CARTOGRAPH_PLUGIN_INTERFACE_H
#define CARTOGRAPH_PLUGIN_INTERFACE_H


/**
 * @brief The CartographPluginInterface class is the main interface for Cartograph plugins.
 */

class CartographPluginInterface
{
public:
    // The supported plugin types. Supports bitwise chaining.
    enum class PluginType: int {
        MapFile     = 1 << 0, // The plugin provides map tiles by implementing @CartographMapFileInterface.
        MapList     = 2 << 0  // The plugin provides its own map management by implementing @CartographMapListInterface.
    };

public:
    virtual ~CartographPluginInterface() = default;

};

#endif // CARTOGRAPH_PLUGIN_INTERFACE_H
