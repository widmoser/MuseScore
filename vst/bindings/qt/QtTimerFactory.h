//
// Created by Hannes Widmoser on 24.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_QTTIMERFACTORY_H
#define ORCHESTRALINTERFACECMAKE_QTTIMERFACTORY_H

#include <vst/lib/host/TimerFactory.h>

class QtTimerFactory : public TimerFactory {
public:
    int startRepeatingTimer(int intervalMillis, std::function<void(int)> callback) override;
    void cancelRepeatingTimer(int id) override;
};

#endif //ORCHESTRALINTERFACECMAKE_QTTIMERFACTORY_H
