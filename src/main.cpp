#include "gamewindow.h"

#include <QApplication>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("NKU"));
    QCoreApplication::setApplicationName(QStringLiteral("DeepTideStation"));

    QLoggingCategory::setFilterRules(QStringLiteral("deep_tide.*=true"));

    GameWindow window;
    window.show();

    return app.exec();
}
