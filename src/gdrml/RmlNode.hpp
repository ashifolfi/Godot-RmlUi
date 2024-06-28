#pragma once

#include <memory>
#include <vector>

#include "GDScriptEventListener.hpp"

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>

using namespace godot;

namespace Rml
{

class Context;
class ElementDocument;

}

namespace godrml
{

class RmlNode : public Control
{
	GDCLASS(RmlNode, Control);

protected:
	static void _bind_methods();

public:
	RmlNode();
	~RmlNode();

	void set_document_path(const String newPath);
	String get_document_path() const;

	void connect_event(const String elementId, const String eventName, Callable func);

	void _ready() override;
	void _enter_tree() override;
	void _exit_tree() override;
	void _input(const Ref<InputEvent>& event) override;
	void _process(double deltaTime) override;
	void _draw() override;

private:
	String m_DocumentPath;
	Rml::Context* m_Context;
	Rml::ElementDocument* m_Document;
	std::vector<GDScriptEventListener*> m_Listeners;
};

}
