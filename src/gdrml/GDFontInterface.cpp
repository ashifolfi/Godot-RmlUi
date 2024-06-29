#include "GDFontInterface.hpp"

#include <godot_cpp/classes/theme.hpp>
#include <godot_cpp/classes/font.hpp>
#include <godot_cpp/classes/font_variation.hpp>

using namespace gdrml;

GDFontInterface::GDFontInterface()
{
}

GDFontInterface::~GDFontInterface()
{
}

bool GDFontInterface::LoadFontFace(const Rml::String& file_name, bool fallback_face, Rml::Style::FontWeight weight)
{
	return false;
}

bool GDFontInterface::LoadFontFace(
	const Rml::byte* data,
	int data_size,
	const Rml::String& family,
	Rml::Style::FontStyle style,
	Rml::Style::FontWeight weight,
	bool fallback_face
)
{
	return false;
}

int GDFontInterface::GenerateString(
	Rml::FontFaceHandle face_handle,
	Rml::FontEffectsHandle font_effects_handle,
	const Rml::String& string,
	const Rml::Vector2f& position,
	const Rml::Colourb& colour,
	float opacity,
	Rml::GeometryList& geometry
)
{
	return 0;
}
