//
// Created by Hannes Widmoser on 30.12.17.
//

#ifndef ORCHESTRALINTERFACECMAKE_EDITOR_H
#define ORCHESTRALINTERFACECMAKE_EDITOR_H

namespace oi {

namespace lib {
// TODO: extend namespace to the whole library

class Rect {
public:

    Rect(int left, int top, int right, int bottom)
        : left(left), top(top), right(right), bottom(bottom) {
    }

    int left;
    int top;
    int right;
    int bottom;

    int width() const {
        return right - left;
    };
    int height() const {
        return bottom - top;
    };
};

}
}

using namespace oi;

class Editor {
public:
    virtual const lib::Rect getBounds() const = 0;
    virtual void update() = 0;
    virtual void open(void* nativeParentWindowHandle) = 0;
    virtual void close() = 0;
};

#endif //ORCHESTRALINTERFACECMAKE_EDITOR_H
