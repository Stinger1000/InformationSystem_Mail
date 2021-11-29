#include "Configs.h"

namespace Configs {
/**
 * @brief WriteConfigs, writes parameter to ini file
 * @param[in] key - search key
 * @param[in] set - parameter
 *
 * @return none
 */
void WriteConfigs(const QString& key, const QVariant& set)
{
    QSettings settings(sSettingFile, QSettings::IniFormat);
    settings.setValue(key, set);
}

/**
 * @brief ReadConfig, reads parameters from ini file
 * @param[in] key - search key
 * @param[in] def - default value unless doesn't have a key
 *
 * @return required parameter
 */
QVariant ReadConfig(const QString& key, QVariant def)
{
    QSettings settings(sSettingFile, QSettings::IniFormat);
    return settings.value(key, def);
}
}
