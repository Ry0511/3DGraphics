#pragma once

#include "GLFW/glfw3.h"
#include <cstdint>
#include <string>
#include <format>

namespace Input {

	//////////////////////////////////////////////////
	// Event Types
	//////////////////////////////////////////////////

	enum class EventType {
		MOUSE, KEY
	};

	constexpr const char* UNDEFINED_KEY = "NULL";

	//////////////////////////////////////////////////
	// Action Event Class
	//////////////////////////////////////////////////

	class ActionEvent {

	protected:
		const EventType m_EventType;
		const int m_Button, m_Action, m_Mods, m_Scancode;

	public:
		ActionEvent(const int btn, const int act, const int mods, const int scan)
			: m_EventType(scan == -1 ? EventType::MOUSE : EventType::KEY),
			m_Button(btn), m_Action(act), m_Mods(mods), m_Scancode(-1)
		{};

		//////////////////////////////////////////////////
		// GENERIC EVENT METHODS
		//////////////////////////////////////////////////
	public:
		const EventType& getEventType() const;
		const int getButton() const;
		const int getAction() const;
		const int getMods() const;
		const int getScan() const;

	public:
		const bool isPress() const;
		const bool isRelease() const;
		const bool isRepeat() const;

		const bool isAltDown() const;
		const bool isShiftDown() const;
		const bool isCtrlDown() const;
		const bool isCapsLockEnabled() const;

		//////////////////////////////////////////////////
		// EVENT TYPE METHODS
		//////////////////////////////////////////////////
	public:
		const bool isMouseEvent() const;
		const bool isKeyEvent() const;

		//////////////////////////////////////////////////
		// MOUSE EVENT METHODS
		//////////////////////////////////////////////////
	public:
		const bool isMouseLeft() const;
		const bool isMouseRight() const;
		const bool isMouseMiddle() const;

		//////////////////////////////////////////////////
		// KEY EVENT METHODS
		//////////////////////////////////////////////////
	public:
		const bool isKey(const int key) const;
		const char* getKey() const;

	public:
		const std::string toString() const;
	};
}

