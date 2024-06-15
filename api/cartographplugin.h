#ifndef CARTOGRAPH_PLUGIN_H
#define CARTOGRAPH_PLUGIN_H

#if defined(CARTOGRAPH_PLUGIN_IMPORT)
#define CARTOGRAPH_API __declspec(dllimport)
#else
#define CARTOGRAPH_API __declspec(dllexport)
#endif

#include "cartographplugininterface.h"
#include "cartographoptioninterface.h"
#include "cartographmapfileinterface.h"
#include "cartographmaplistinterface.h"

#endif // CARTOGRAPH_PLUGIN_H
