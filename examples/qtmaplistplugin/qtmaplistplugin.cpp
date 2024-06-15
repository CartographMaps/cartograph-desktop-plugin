#include "qtmaplistplugin.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

QtMapListPlugin::QtMapListPlugin()
{
}

QtMapListPlugin::~QtMapListPlugin()
{
}

std::string QtMapListPlugin::getMapTypeName() const
{
    return "Qt map list example";
}

bool QtMapListPlugin::supportsCaching() const
{
    // Allow Cartograph Maps to cache the downloaded tiles.
    return true;
}

bool QtMapListPlugin::closeMap()
{
    m_tileBuffer.clear();
	return true;
}

std::string QtMapListPlugin::getLastErrorMessage()
{
    return "";
}

std::string QtMapListPlugin::getMapName()
{
    return "OpenStreetMap.org tiles";
}

std::string QtMapListPlugin::getMapDescription()
{
    return std::string();
}

std::string QtMapListPlugin::getMapCopyright()
{
    return std::string();
}

int QtMapListPlugin::getSupportedTileSize()
{
    return 0;
}

CartographMapInterface::BoundingBox QtMapListPlugin::getMapBoundingBox()
{
	// The map covers the whole world
    return BoundingBox(90.0, -180.0, -90.0, 180.0);
}

CartographMapInterface::ImageFormat QtMapListPlugin::getOutputImageFormat() const
{
    return ImageFormat::Raster;
}

const uint8_t *QtMapListPlugin::getTileAt(Tile &tile, CalcTool *helper, int* outDataSize)
{
    m_tileBuffer.clear();

    QEventLoop loop;
    QNetworkAccessManager nam;

    QString url = QStringLiteral("https://tile.openstreetmap.org/%1/%2/%3.png")
            .arg(tile.zoomLevel)
            .arg(tile.x)
            .arg(tile.y);
    QNetworkRequest requ(url);
    requ.setRawHeader("User-Agent", "Cartograph Maps example plugin");

    requ.setTransferTimeout(5000);
    auto reply = nam.get(requ);

    // Debugging in case of SSL errors:
    /*
    QList<QSslError> sslErrors;
    sslErrors.append(QSslError(QSslError::CertificateNotYetValid));
    sslErrors.append(QSslError(QSslError::CertificateExpired));

    if (reply)
    {
        reply->ignoreSslErrors(sslErrors);
    }

    QObject::connect(reply, &QNetworkReply::sslErrors, &loop, [reply, sslErrors](const QList<QSslError> &errors)
    {
        qDebug() << "SSL errors: " << errors;

        if (errors.size() == 1 && errors.first().error() == QSslError::CertificateExpired)
        {
            reply->ignoreSslErrors(sslErrors);
        }
    });
    */

    QObject::connect(reply, &QNetworkReply::readyRead, &loop, [this, reply]()
    {
        m_tileBuffer.append(reply->readAll());
    });

    QObject::connect(reply, &QNetworkReply::finished, &loop, [this, reply, &loop]()
    {
        m_tileBuffer.append(reply->readAll());
        if (reply->error() == QNetworkReply::TimeoutError)
        {
            m_downloadError = true;
        }
        else if (reply->error() != QNetworkReply::NoError)
        {
            m_downloadError = true;
        }
        else
        {
            m_downloadError = false;
        }
        loop.exit();
    });
    loop.exec();
    delete reply;

    if (m_downloadError)
    {
        qWarning() << "Error downloading" << url;
        *outDataSize = 0;
        return nullptr;
    }

    *outDataSize = m_tileBuffer.size();
    return (const uint8_t*)m_tileBuffer.constData();
}

std::vector<QtMapListPlugin::MapListEntry> QtMapListPlugin::getMaps()
{
    std::vector<MapListEntry> maps;
    maps.push_back(MapListEntry("osm", "OpenStreetMap.org tiles", ""));
    return maps;
}

bool QtMapListPlugin::openMap(const std::string& key)
{
    const auto maps = getMaps();
    for (const auto& e : maps)
    {
        if (strcmp(e.key.c_str(), "osm") == 0 && key == e.key)
        {
            return true;
        }
    }
    return false;
}
