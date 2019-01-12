// Common parts for pasgen and pasgen-cli

#ifndef COMMON_H
#define COMMON_H

#include <QSettings>
#include <QString>

QString generate(QString password, QString page, QSettings &settings);

#endif
