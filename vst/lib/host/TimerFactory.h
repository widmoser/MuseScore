//
// Created by Hannes Widmoser on 16/07/2017.
//

#ifndef ORCHESTRALINTERFACECMAKE_TIMER_H
#define ORCHESTRALINTERFACECMAKE_TIMER_H

#include <functional>

/**
 * Interface for creating a repeating timer.
 *
 * The intention of this class is to make this library independent of gui libraries, because it makes sense to run such
 * a timer in the main thread of a ui library in order to save creating an additional thread.
 */
class TimerFactory {
public:
    /**
     * Creates a timer, that is executed repeatedly in the given interval.
     *
     * @param intervalMillis The interval in milliseconds. The timer does not need to guarantee that the interval is
     * exactly observed.
     * @param callback A callback that is invoked when the timer triggers. The timer id provided as a parameter to the
     * callback.
     * @return An id that can be later used to cancel the timer.
     */
    virtual int startRepeatingTimer(int intervalMillis, std::function<void(int)> callback) = 0;

    /**
     * Cancels the timer with the specified id.
     */
    virtual void cancelRepeatingTimer(int id) = 0;
};


#endif //ORCHESTRALINTERFACECMAKE_TIMER_H
