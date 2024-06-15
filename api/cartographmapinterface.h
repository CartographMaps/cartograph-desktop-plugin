#ifndef CARTOGRAPHMAPINTERFACE_H
#define CARTOGRAPHMAPINTERFACE_H

#include <string>

/**
 * @brief The CartographMapInterface class provides methods for generating map tiles.
 */

class CartographMapInterface
{
public:
    /**
     * @brief The ImageFormat enum defines the image format returned by the tile provider.
     */
    enum class ImageFormat : int {
        Raster = 0, // a buffer containing image data (bmp, png, jpg, etc).
        RGB    = 1, // a buffer containing RGB values. E.g., RGBRGBRGB...
        RGBA   = 2, // a buffer containing RGBA values. E.g., RGBARGBARGBA...
    };

public:

    /**
     * @brief The Rectangle class represents a simple rectangle defined by left/top/right/bottom
     * cooridinates.
     */
    class Rectangle {
    public:
        Rectangle(double left = 0, double top = 0, double right = 0, double bottom = 0) {
            this->left = left;
            this->top = top;
            this->right = right;
            this->bottom = bottom;
        }

        double bottom;
        double left;
        double right;
        double top;

        double getHeight() const {
            return this->bottom - this->top;
        }

        double getWidth() const {
            return this->right - this->left;
        }
    };

    /**
     * @brief The Point class represents a 2D point with x/y coordinates.
     */
    class Point {
    public:
        Point(double x = 0, double y = 0) : x(x), y(y) {}
        double x;
        double y;
    };

    /**
     * @brief The BoundingBox class represents a bounding box.
     */
    class BoundingBox
    {
    public:
        BoundingBox(double top = 0, double left = 0, double bottom = 0, double right = 0)
            : top(top), left(left), bottom(bottom), right(right) {}

        double top;
        double left;
        double bottom;
        double right;

    };

    /**
     * @brief The Tile class represents a map tile. A map tile is defined by its x/y coordinates,
     * and the zoom level.
     */
    class Tile
    {
    public:
        Tile(int64_t y = 0, int64_t x = 0, int zoomLevel = 0, int tileSize = 256)
            : x(x), y(y), zoomLevel(zoomLevel), tileSize(tileSize) {}

        int64_t x, y; // pixel coordinates
        int zoomLevel;
        int tileSize;
        BoundingBox boundingBox; // lat/lon coordinates
    };

    /**
     * @brief The CalcTool class offers means for calculating mappings between the
     * Cartograph tile location, and the local tile location.
     */
    class CalcTool
    {
    public:
        virtual ~CalcTool() = default;

        /**
         * @brief getPositionRelativeToTile calculates the pixel position of a bounding box (geo coordinates)
         * on the given tile.
         * This method is useful, if the plugin's map format does not provide tiles, or the tiles do not match the
         * standard slippy tile format.
         * For instance, if multiple plugin tiles are required to fill one slippy tile, then this method can be used
         * for calculating the projections for each plugin tile to the slippy tile.
         * @param bb A bounding box (in geo coordinates).
         * @param tile A tile.
         * @return The area (in pixel coordinates) of the tile which is covered by the bounding box.
         */
        virtual Rectangle getPositionRelativeToTile(const BoundingBox &bb, const Tile &tile) = 0;
    };

public:
    virtual ~CartographMapInterface() = default;

    // The UTF-8 formatted map type name (e.g., "OpenStreetMap online tile source")
    virtual std::string getMapTypeName() const = 0;

    // Return true if the tiles may be cached by the app.
    virtual bool supportsCaching() const {return true;};

    // Close the map. If using "fHandle" from @openMap then do not close the file handle because this is done automatically by the app.
    virtual bool closeMap() = 0;

    /**
     * @brief getLastErrorMessage
     * @return The last error message generated.
     */
    virtual std::string getLastErrorMessage() = 0;

    // The UTF-8 encoded map name (e.g., "Map of Austria")
    virtual std::string getMapName() = 0;

    // The UTF-8 encoded map description.
    virtual std::string getMapDescription() = 0;

    // The UTF-8 encoded map copyright notice.
    virtual std::string getMapCopyright() = 0;

    // Get the tile size supported by this map. Return "-1" if custom tile sizes are supported.
    virtual int getSupportedTileSize() = 0;

    // Get the bounding box of the map.
    virtual BoundingBox getMapBoundingBox() = 0;

    // The image format of the tile data.
    virtual ImageFormat getOutputImageFormat() const = 0;

    /**
     * @brief getTileAt Get the tile at a specific location (slippy tile format y/x/zoom).
     * @param tile
     * @param helper Provides methods for tile transformations.
     * @parem outDataSize The size of the returned buffer.
     * @return A pointer to the data.
     */
    virtual const uint8_t* getTileAt(CartographMapInterface::Tile &tile, CalcTool *helper, int* outDateSize) = 0;

};

#endif // CARTOGRAPHMAPINTERFACE_H
