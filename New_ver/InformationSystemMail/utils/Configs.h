#ifndef CONFIGS_H
#define CONFIGS_H

#include <QDebug>
#include <QSettings>

/**
 * @brief These functions give access to loading and saving
 *   parameters from an ini file
 */
namespace Configs {
static constexpr const char* sSettingFile = "settings.ini";

void     WriteConfigs(const QString&, const QVariant&);
QVariant ReadConfig(const QString&, QVariant def = "");

template <typename T>
T ReadConfig(uint8_t);
}

#endif // CONFIGS_H
