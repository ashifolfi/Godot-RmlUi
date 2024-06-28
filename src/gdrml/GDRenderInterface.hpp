#pragma once

#include <rmlui/Core/RenderInterface.h>
#include <rmlui/Core/Types.h>
#include <godot_cpp/variant/rid.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <vector>

namespace godrml {

class GDRenderInterface : public Rml::RenderInterface
{
public:
	GDRenderInterface();
	~GDRenderInterface();

	void SetCanvasItem(godot::RID canvasItemId);
	void RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation) override;

	void EnableScissorRegion(bool enable) override;
	void SetScissorRegion(int x, int y, int width, int height) override;

	bool LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source) override;
	bool GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions) override;
	void ReleaseTexture(Rml::TextureHandle texture) override;

private:
	godot::RID m_CurCanvasItem;
	std::vector<godot::Ref<godot::Texture2D>> m_LoadedTextures;
};

}
