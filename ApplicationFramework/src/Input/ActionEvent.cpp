#include "ActionEvent.h"

namespace Input {

    //////////////////////////////////////////////////
    // GENERIC EVENT METHODS
    //////////////////////////////////////////////////

    const EventType& ActionEvent::getEventType() const {
        return m_EventType;
    }

    const int ActionEvent::getButton() const {
        return m_Button;
    }
    const int ActionEvent::getAction() const {
        return m_Action;
    }
    const int ActionEvent::getMods() const {
        return m_Mods;
    }
    const int ActionEvent::getScan() const {
        return m_Scancode;
    }

    const bool ActionEvent::isPress() const {
        return getAction() == GLFW_PRESS;
    }
    const bool ActionEvent::isRelease() const {
        return getAction() == GLFW_RELEASE;
    }
    const bool ActionEvent::isRepeat() const {
        return getAction() == GLFW_REPEAT;
    }

    const bool ActionEvent::isAltDown() const {
        return getMods() & GLFW_MOD_ALT;
    }
    const bool ActionEvent::isShiftDown() const {
        return getMods() & GLFW_MOD_SHIFT;
    }
    const bool ActionEvent::isCtrlDown() const {
        return getMods() & GLFW_MOD_CONTROL;
    }
    const bool ActionEvent::isCapsLockEnabled() const {
        return getMods() & GLFW_MOD_CAPS_LOCK;
    }

    //////////////////////////////////////////////////
    // EVENT TYPE METHODS
    //////////////////////////////////////////////////

    const bool ActionEvent::isMouseEvent() const {
        return m_EventType == EventType::MOUSE;
    }
    const bool ActionEvent::isKeyEvent() const {
        return m_EventType == EventType::KEY;
    }

    //////////////////////////////////////////////////
    // MOUSE EVENT METHODS
    //////////////////////////////////////////////////

    const bool ActionEvent::isMouseLeft() const {
        return getButton() == GLFW_MOUSE_BUTTON_1;
    }
    const bool ActionEvent::isMouseRight() const {
        return getButton() == GLFW_MOUSE_BUTTON_2;
    }
    const bool ActionEvent::isMouseMiddle() const {
        return getButton() == GLFW_MOUSE_BUTTON_3;
    }

    //////////////////////////////////////////////////
    // KEY EVENT METHODS
    //////////////////////////////////////////////////

    const bool ActionEvent::isKey(const int key) const {
        return getButton() == key;
    }

    const char* ActionEvent::getKey() const {
        const char* c = glfwGetKeyName(getButton(), getScan());
        if (!c) return UNDEFINED_KEY;
        return c;
    }

    //////////////////////////////////////////////////
    // DEBUG
    //////////////////////////////////////////////////

    const std::string ActionEvent::toString() const {
#define _CH(a, b) a ? b : "*"
#define ACTION_TO_STRING isPress() ? "PRESS" : isRelease() ? "RELEASE" : "REPEAT"
#define MODS_TO_STRING std::format("{{{0:*>5}, {1:*>5}, {2:*>5}, {3:*>5}}}", \
        _CH(isAltDown(), "  ALT"),                                           \
        _CH(isShiftDown(), "SHIFT"), _CH(isCtrlDown(), " CTRL"),             \
        _CH(isCapsLockEnabled(), " CAPS"))                                   \

        return std::format(
            "{0:>5}({1:>4}, {2:>8}, {3}, {4:>4})",
            isKeyEvent() ? "Key" : "Mouse",
            getButton(),
            ACTION_TO_STRING,
            MODS_TO_STRING,
            getKey()
        );
    }

}

