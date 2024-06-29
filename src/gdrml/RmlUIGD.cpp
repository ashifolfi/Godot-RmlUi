#include "RmlUIGD.hpp"

#include <RmlUi/Core.h>
#include <Conversion.h>
#include <godot_cpp/classes/engine.hpp>

using namespace gdrml;

void RmlUIGD::_bind_methods()
{
#define BIND_EVENT_ID(ID) ClassDB::bind_integer_constant(get_class_static(), "EventID", #ID, static_cast<GDExtensionInt>(Rml::EventId::ID))
	BIND_EVENT_ID(Mousedown);
	BIND_EVENT_ID(Mousescroll);
	BIND_EVENT_ID(Mouseover);
	BIND_EVENT_ID(Mouseout);
	BIND_EVENT_ID(Focus);
	BIND_EVENT_ID(Blur);
	BIND_EVENT_ID(Keydown);
	BIND_EVENT_ID(Keyup);
	BIND_EVENT_ID(Textinput);
	BIND_EVENT_ID(Mouseup);
	BIND_EVENT_ID(Click);
	BIND_EVENT_ID(Dblclick);
	BIND_EVENT_ID(Load);
	BIND_EVENT_ID(Unload);
	BIND_EVENT_ID(Show);
	BIND_EVENT_ID(Hide);
	BIND_EVENT_ID(Mousemove);
	BIND_EVENT_ID(Dragmove);
	BIND_EVENT_ID(Drag);
	BIND_EVENT_ID(Dragstart);
	BIND_EVENT_ID(Dragover);
	BIND_EVENT_ID(Dragdrop);
	BIND_EVENT_ID(Dragout);
	BIND_EVENT_ID(Dragend);
	BIND_EVENT_ID(Handledrag);
	BIND_EVENT_ID(Resize);
	BIND_EVENT_ID(Scroll);
	BIND_EVENT_ID(Animationend);
	BIND_EVENT_ID(Transitionend);
	BIND_EVENT_ID(Change);
	BIND_EVENT_ID(Submit);
	BIND_EVENT_ID(Tabchange);
	BIND_EVENT_ID(Columnadd);
	BIND_EVENT_ID(Rowadd);
	BIND_EVENT_ID(Rowchange);
	BIND_EVENT_ID(Rowremove);
	BIND_EVENT_ID(Rowupdate);
	BIND_EVENT_ID(NumDefinedIds);
	BIND_EVENT_ID(FirstCustomId);
	BIND_EVENT_ID(MaxNumIds);
#undef BIND_EVENT_ID

	ClassDB::bind_method(D_METHOD("add_font_file", "path"), &RmlUIGD::add_font_file);
}

RmlUIGD::RmlUIGD()
{
}

RmlUIGD::~RmlUIGD()
{
}

void RmlUIGD::add_font_file(String path)
{
	Rml::LoadFontFace(Conversion::stringToStd(path));
}
