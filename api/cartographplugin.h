#ifndef CARTOGRAPH_PLUGIN_H
#define CARTOGRAPH_PLUGIN_H

#if defined(_WIN32)
#if defined(CARTOGRAPH_PLUGIN_COMPILE)
#define CARTOGRAPH_API __declspec(dllexport)
#else
#define CARTOGRAPH_API __declspec(dllimport)
#endif
#else
#define CARTOGRAPH_API
#endif

#include "cartographplugininterface.h"
#include "cartographoptioninterface.h"
#include "cartographmapfileinterface.h"
#include "cartographmaplistinterface.h"

#endif // CARTOGRAPH_PLUGIN_H
