#ifndef CARTOGRAPHMAPFILEINTERFACE_H
#define CARTOGRAPHMAPFILEINTERFACE_H

#include "cartographmapinterface.h"

/**
 * @brief The CartographMapFileInterface class provides methods for generating map tiles from file-based maps.
 */

class CartographMapFileInterface : public CartographMapInterface
{
public:

    /**
     * @brief canOpenMap checks if the given map can be opened.
     * @param filename The map filename.
     * @param fHandle The file handle (with "READ" access). **Not implement!**
     * @return true if the map can be opened.
     */
    virtual bool canOpenMap(const std::string &filename, int fHandle) = 0;

    /**
     * @brief openMap
     * @param filename The map filename.
     * @param fHandle The file handle (with "READ" access). **Not implement!**
     * @return true on success.
     */
    virtual bool openMap(const std::string &filename, int fHandle) = 0;

    // Return true if the map consists of multiple files.
    virtual bool usesDirectory() const = 0;

};

#endif // CARTOGRAPHMAPFILEINTERFACE_H
