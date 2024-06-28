#include "GDRenderInterface.hpp"

#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/image.hpp>

#include <Conversion.h>
#include <algorithm>

using namespace godrml;
using namespace godot;

GDRenderInterface::GDRenderInterface()
{
}

GDRenderInterface::~GDRenderInterface()
{
}

void GDRenderInterface::SetCanvasItem(RID canvasItemId)
{
	m_CurCanvasItem = canvasItemId;
}

void GDRenderInterface::RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation)
{
	PackedVector2Array gdVertices;
	PackedVector2Array gdUvs;
	PackedInt32Array gdIdxs;
	PackedColorArray gdColors;

	RenderingServer* RS = RenderingServer::get_singleton();

	gdVertices.resize(num_vertices);
	gdUvs.resize(num_vertices);
	gdColors.resize(num_vertices);
	gdIdxs.resize(num_indices);

	for (int i = 0; i < num_vertices; i++)
	{
		gdVertices[i] = Vector2(translation.x + vertices[i].position.x, translation.y + vertices[i].position.y);
		gdUvs[i] = Vector2(vertices[i].tex_coord.x, vertices[i].tex_coord.y);
		gdColors[i] = Color(
			vertices[i].colour.red / 255.0f,
			vertices[i].colour.green / 255.0f,
			vertices[i].colour.blue / 255.0f,
			vertices[i].colour.alpha / 255.0f
		);
	}
	
	for (int i = 0; i < num_indices; i++)
	{
		gdIdxs[i] = indices[i];
	}

	Texture2D* texturePtr = reinterpret_cast<Texture2D*>(texture);
	if (texturePtr != nullptr)
		RS->canvas_item_add_triangle_array(m_CurCanvasItem, gdIdxs, gdVertices, gdColors, gdUvs, {}, {}, texturePtr->get_rid());
	else
		RS->canvas_item_add_triangle_array(m_CurCanvasItem, gdIdxs, gdVertices, gdColors, gdUvs);
}

// these are simple implementations that I assume are mostly accurate?
// todo: do these work actually
void GDRenderInterface::EnableScissorRegion(bool enable)
{
	RenderingServer* RS = RenderingServer::get_singleton();
	RS->canvas_item_set_clip(m_CurCanvasItem, enable);
}

void GDRenderInterface::SetScissorRegion(int x, int y, int width, int height)
{
	RenderingServer* RS = RenderingServer::get_singleton();
	RS->canvas_item_set_custom_rect(m_CurCanvasItem, true, Rect2(x, y, width, height));
}

bool GDRenderInterface::LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source)
{
	String gdPath = Conversion::stringToGodot(source);

	Ref<Resource> res = ResourceLoader::get_singleton()->load(gdPath);
	if (res == nullptr)
		return false;

	Ref<Texture2D> texRes = res;
	if (res == nullptr)
		return false;

	m_LoadedTextures.push_back(texRes);
	// specifically use back here to make sure it points to the right place.
	texture_handle = reinterpret_cast<Rml::TextureHandle>(m_LoadedTextures.back().ptr());
	texture_dimensions = Rml::Vector2i(texRes->get_width(), texRes->get_height());

	return true;
}

bool GDRenderInterface::GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions)
{
	Ref<Image> imageRef;
	imageRef.instantiate();

	PackedByteArray bytes;
	bytes.resize((source_dimensions.x * source_dimensions.y) * 4);
	for (int i = 0; i < (source_dimensions.x * source_dimensions.y) * 4; i++)
	{
		bytes[i] = source[i];
	}
	imageRef->set_data(source_dimensions.x, source_dimensions.y, false, Image::FORMAT_RGBA8, bytes);

	m_LoadedTextures.push_back(ImageTexture::create_from_image(imageRef));
	texture_handle = reinterpret_cast<Rml::TextureHandle>(m_LoadedTextures.back().ptr());

	return true;
}

void GDRenderInterface::ReleaseTexture(Rml::TextureHandle texture)
{
	// pointers :smile:
	Texture2D* handle = reinterpret_cast<Texture2D*>(texture);

	if (handle == nullptr)
	{
		UtilityFunctions::printerr("GDRML: Attempted to close invalid TextureHandle!");
		return;
	}

	// locate this pointer within our list and remove it (disgusting!!)
	if (std::find(m_LoadedTextures.begin(), m_LoadedTextures.end(), handle) != m_LoadedTextures.end())
	{
		std::remove(m_LoadedTextures.begin(), m_LoadedTextures.end(), handle);
	}
}
