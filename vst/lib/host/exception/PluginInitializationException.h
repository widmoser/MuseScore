//
// Created by Hannes Widmoser on 16/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_PLUGININITIALIZATIONEXCEPTION_H
#define ORCHESTRALINTERFACECMAKE_PLUGININITIALIZATIONEXCEPTION_H

#include <exception>
#include <string>
#include <QtCore/QString>
#include <QtCore/QFileInfo>

class PluginInitializationException : public std::exception {
public:
    PluginInitializationException(const QFileInfo& path, const QString& message);
    const QString message;
    const QFileInfo path;
};


#endif //ORCHESTRALINTERFACECMAKE_PLUGININITIALIZATIONEXCEPTION_H
