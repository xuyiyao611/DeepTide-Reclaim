#pragma once

#include <QString>

namespace ProjectPaths {

QString resolveProjectRoot();
QString assetsRoot();
QString imagesRoot();
QString soundsRoot();
QString mapsRoot();
bool ensureAssetLayout(QString *errorMessage = nullptr);

}  // namespace ProjectPaths
