#include "projectpaths.h"

#include <QCoreApplication>
#include <QDir>
#include <QStringList>

namespace {

QString findRootFrom(const QString &startPath)
{
    QDir dir(startPath);
    const QStringList requiredEntries = {"assets", "src", "深潮回收站文档说明"};

    while (dir.exists()) {
        bool matched = true;
        for (const QString &entry : requiredEntries) {
            if (!dir.exists(entry)) {
                matched = false;
                break;
            }
        }

        if (matched) {
            return dir.absolutePath();
        }

        if (!dir.cdUp()) {
            break;
        }
    }

    return {};
}

}  // namespace

namespace ProjectPaths {

QString resolveProjectRoot()
{
    const QString fromApp = findRootFrom(QCoreApplication::applicationDirPath());
    if (!fromApp.isEmpty()) {
        return fromApp;
    }

    const QString fromCurrent = findRootFrom(QDir::currentPath());
    if (!fromCurrent.isEmpty()) {
        return fromCurrent;
    }

    return QDir::currentPath();
}

QString assetsRoot()
{
    return QDir(resolveProjectRoot()).filePath("assets");
}

QString imagesRoot()
{
    return QDir(assetsRoot()).filePath("images");
}

QString soundsRoot()
{
    return QDir(assetsRoot()).filePath("sounds");
}

QString mapsRoot()
{
    return QDir(assetsRoot()).filePath("maps");
}

bool ensureAssetLayout(QString *errorMessage)
{
    const QStringList requiredDirectories = {assetsRoot(), imagesRoot(), soundsRoot(), mapsRoot()};
    QStringList missing;

    for (const QString &path : requiredDirectories) {
        if (!QDir(path).exists()) {
            missing.push_back(path);
        }
    }

    if (!missing.isEmpty()) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Missing asset directories: %1").arg(missing.join(", "));
        }
        return false;
    }

    if (errorMessage != nullptr) {
        *errorMessage = QStringLiteral("Asset layout ready.");
    }
    return true;
}

}  // namespace ProjectPaths
