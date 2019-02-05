//
// Created by Hannes Widmoser on 16/07/2017.
//

#ifndef ORCHESTRALINTERFACECMAKE_PLUGINWINDOW_H
#define ORCHESTRALINTERFACECMAKE_PLUGINWINDOW_H

/**
 * Minimal interface for a plugin view when hosting a plugin.
 *
 * The intention of this class is to make this library independent of gui libraries. This is achieved by specifying a
 * minimum interface.
 */
class PluginView {
public:

    virtual ~PluginView() {};

    /**
     * Redraws the screen.
     */
    virtual void update() = 0;

    /**
     * Updates the position of the window.
     * @param left The new left position in pixels.
     * @param top The new top position in pixels.
     */
    virtual void setPosition(int left, int top) = 0;

    /**
     * Updates the size of the window.
     * @param width The new width in pixels.
     * @param height The new height in pixels.
     */
    virtual void setSize(int width, int height) = 0;

    /**
     * Gets the native window handle.
     */
    virtual void* getNativeWindowHandle() = 0;
};


#endif //ORCHESTRALINTERFACECMAKE_PLUGINWINDOW_H
