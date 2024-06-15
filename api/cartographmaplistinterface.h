#ifndef CARTOGRAPHMAPLISTINTERFACE_H
#define CARTOGRAPHMAPLISTINTERFACE_H

#include "cartographmapinterface.h"

#include <vector>

/**
 * @brief The CartographMapListInterface class is the basis for maps which are completely managed by the plugin.
 */

class CartographMapListInterface : public CartographMapInterface
{
public:
	class MapListEntry {
	public:
		MapListEntry(const std::string& key, const std::string& name, const std::string& description)
			: key(key), name(name), description(description) {}
		std::string key;			// A key which identifies the map in the plugin. The key is only used for referencing the map.
		std::string name;			// The map name.
		std::string description;	// The map description.
	};
public:
	// A list of maps offered by the plugin.
	virtual std::vector<MapListEntry> getMaps() = 0;

	/**
	 * @brief openMap Open the map with the given key (see @getMaps).
	 * @param key The key which identifies the map (see @MapListEntry).
	 * @return true on success.
	 */
	virtual bool openMap(const std::string& key) = 0;

};

#endif // CARTOGRAPHMAPLISTINTERFACE_H
