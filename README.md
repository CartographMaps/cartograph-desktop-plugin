# cartograph-desktop-plugin
This project provides an interface for Cartograph Maps plugins (*macOS* and *Windows* desktop version) for adding *custom map tile providers*.

Plugins can provide map tiles in two ways:
1. By taking a map file name as input: The managing of maps is done in Cartograph Maps.
2. By providing a list of maps: The managing of maps is done by the plugin. The plugin offers Cartograph Maps a list of maps.

**Note:** Plugins work only with Cartograph Maps 3.6.0 (and newer) on macOS and Windows because iOS and Android do not support plugins due to security restrictions which prevent loading of external dynamic libraries.
 
# Instructions
The *example directory* contains examples how to create your own plugin.

The basic steps are as follows:

First, you have to include the *plugin header* in your project:
```
#include <cartographplugin.h>
```

Then create the implementation of your plugin:
```
class MyMapPlugin : public CartographPluginInterface, public CartographMapFileInterface
```

Then create the *implementations* of the interface's pure virtual *methods*:
```
public:
	std::string getMapTypeName() const override;
	...
```

Then add the following which initiates the plugin:
```
extern "C" CARTOGRAPH_API CartographPluginInterface *createInstance()
{
    return new MyMapPlugin();
}
extern "C" CARTOGRAPH_API int supportedTypes()
{
    return static_cast<int>(CartographPluginInterface::PluginType::MapFile);
}
```

Finally add a method which returns a unique identifier of the plugin:
```
extern "C" CARTOGRAPH_API const char* uniqueIdentifier()
{
    return "HERE COMES YOUR UNIQUE IDENTIFIER, e.g. com.mydomain.mypluginname";
}
```
It is important that the identifier is unique, else maps will eventually get mixed up in Cartograph Maps.


Then compile your project into a .dll or .dylib and copy the generated file to the Cartograph Maps plugin directory as described below.

**Note:** If you are using Qt libraries in your plugin then make sure that your Qt version is compatible with the version used in Cartograph Maps. At the moment Cartograph Maps uses Qt 6.5.x.

# Installation of your plugin

## Windows
Copy your generated .dll plugin to "C:\Program Files\Cartograph Maps 3\plugins". If the directory "plugins" does not exist, then you can manually create it.

## macOS
Copy your generated .dylib plugin to "/Applications/Cartograph Maps 3/plugins/cartograph". If the directory "cartograph" does not exist, then you can manually create it.

**Note:** The .dylib file has to be code signed else it will not work due to macOS security restrictions.