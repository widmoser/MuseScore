//
// Created by Hannes Widmoser on 17/09/15.
//

#ifndef ORCHESTRALINTERFACECMAKE_PROGRESS_H
#define ORCHESTRALINTERFACECMAKE_PROGRESS_H

#include <string>

class Progress {
public:
    virtual void message(const std::string& message) const = 0;
    virtual void percent(float value) const = 0;
};

#endif //ORCHESTRALINTERFACECMAKE_PROGRESS_H
