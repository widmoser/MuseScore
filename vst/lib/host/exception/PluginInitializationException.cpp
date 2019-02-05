//
// Created by Hannes Widmoser on 16/09/15.
//

#include "PluginInitializationException.h"

PluginInitializationException::PluginInitializationException(const QFileInfo &path, const QString &message) : path(
        path), message(message) {
}
