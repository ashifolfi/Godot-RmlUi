#include "RmlNode.hpp"

#include "GDRenderInterface.hpp"
#include "RmlUIController.hpp"

#include <RmlUi/Core/Context.h>
#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "GDScriptEventListener.hpp"
#include "GDScriptEventListenerInstancer.hpp"

#include <Conversion.h>

using namespace godrml;

void RmlNode::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("connect_event", "elementId", "eventName", "func"), &RmlNode::connect_event);
	ClassDB::bind_method(D_METHOD("get_document_path"), &RmlNode::get_document_path);
	ClassDB::bind_method(D_METHOD("set_document_path", "newPath"), &RmlNode::set_document_path);
	ClassDB::add_property("RmlNode", PropertyInfo(Variant::STRING, "m_DocumentPath", PROPERTY_HINT_FILE), "set_document_path", "get_document_path");
}

RmlNode::RmlNode()
{
	m_Context = nullptr;
	m_Document = nullptr;
}

RmlNode::~RmlNode()
{
}

void RmlNode::set_document_path(const String newPath)
{
	m_DocumentPath = newPath;
}

String RmlNode::get_document_path() const
{
	return m_DocumentPath;
}

void RmlNode::connect_event(const String elementId, const String eventName, Callable func)
{
	Rml::Element* elem = m_Document->GetElementById(Conversion::stringToStd(elementId));

	if (elem == nullptr)
	{
		UtilityFunctions::push_error("GDRML: No element named '", elementId, "' exists in the document.");
		return;
	}

	// hack: stupid but we got a mem violation so just make a new callable around what we were passed
	elem->AddEventListener(Conversion::stringToStd(eventName), new GDScriptEventListener(elem, new Callable(func)));
}

void RmlNode::_ready()
{
}

void RmlNode::_enter_tree()
{
	// don't run in the editor please
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (RmlUIController::Instance() == nullptr)
	{
		UtilityFunctions::push_error("GDRML: !!!! RmlUIController didn't get initialized!");
		return;
	}

	m_Context = Rml::CreateContext("GodotNode_" + std::to_string(get_instance_id()), Rml::Vector2i(
		get_viewport_rect().get_size().width, get_viewport_rect().get_size().height
	));

	if (m_Context)
	{
		m_Document = m_Context->LoadDocument(Conversion::stringToStd(m_DocumentPath));
		m_Document->Show();
	}
	else
	{
		UtilityFunctions::printerr("GDRML: Failed to initialize context!");
	}
}

void RmlNode::_exit_tree()
{
	m_Document->Close();
}

void RmlNode::_input(const Ref<InputEvent>& event)
{
	if (m_Context) {
		// small maybe optimization? don't check against motion and button if we aren't even a mouse event.
		Ref<InputEventMouse> mouseEvent = event;

		if (mouseEvent != nullptr) {
			Ref<InputEventMouseMotion> mouseMotionEvent = mouseEvent;

			if (mouseMotionEvent != nullptr)
			{
				m_Context->ProcessMouseMove(mouseMotionEvent->get_position().x, mouseMotionEvent->get_position().y, 0);
			}
			else
			{
				Ref<InputEventMouseButton> mouseButtonEvent = mouseEvent;

				if (mouseButtonEvent->is_pressed())
				{
					switch (mouseButtonEvent->get_button_index())
					{
					case MouseButton::MOUSE_BUTTON_LEFT:
						m_Context->ProcessMouseButtonDown(0, 0);
						break;
					case MouseButton::MOUSE_BUTTON_RIGHT:
						m_Context->ProcessMouseButtonDown(1, 0);
						break;
					case MouseButton::MOUSE_BUTTON_MIDDLE:
						m_Context->ProcessMouseButtonDown(2, 0);
						break;
					}
				}
				else
				{
					switch (mouseButtonEvent->get_button_index())
					{
					case MouseButton::MOUSE_BUTTON_LEFT:
						m_Context->ProcessMouseButtonUp(0, 0);
						break;
					case MouseButton::MOUSE_BUTTON_RIGHT:
						m_Context->ProcessMouseButtonUp(1, 0);
						break;
					case MouseButton::MOUSE_BUTTON_MIDDLE:
						m_Context->ProcessMouseButtonUp(2, 0);
						break;
					}
				}
			}
		}
		// todo: keyboard
		Ref<InputEventKey> keyEvent = event;
		if (keyEvent != nullptr)
		{	
			String textInput = keyEvent->as_text();
			m_Context->ProcessTextInput(Conversion::stringToStd(textInput));
		}
	}
}

void RmlNode::_process(double deltaTime)
{
	if (m_Context) {
		// I wish I had LateUpdate to mostly ensure that this ran after everything else
		m_Context->Update();

		// we don't really have any indication as to if we're idle or not with RML :shrug:
		queue_redraw();
	}
}

void RmlNode::_draw()
{
	if (m_Context) {
		// set the current canvas item to our canvas item RID
		dynamic_cast<GDRenderInterface*>(Rml::GetRenderInterface())->SetCanvasItem(get_canvas_item());

		// TODO: update the context size when things get resized

		m_Context->Render();
	}
}
