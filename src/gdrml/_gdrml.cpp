#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <RmlUi/Core.h>
#include "RmlNode.hpp"
#include "RmlUIController.hpp"
#include "RmlUIGD.hpp"

using namespace godot;

godrml::RmlUIGD* gd = nullptr;

void init_gdrml_module(ModuleInitializationLevel initLevel)
{
    if (initLevel != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;

	ClassDB::register_internal_class<godrml::RmlUIController>();
	ClassDB::register_class<godrml::RmlNode>();
	ClassDB::register_class<godrml::RmlUIGD>();

	gd = memnew(godrml::RmlUIGD);
	Engine::get_singleton()->register_singleton("RmlUIGD", gd);

	if (!ProjectSettings::get_singleton()->has_setting("autoload/RmlUIRoot"))
	{
		UtilityFunctions::push_warning("GDRML: Plugin is not enabled. If you use RmlUI, your project will crash!");
	}
}

void deinit_gdrml_module(ModuleInitializationLevel initLevel)
{
	if (initLevel != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;

	Engine::get_singleton()->unregister_singleton("RmlUIGD");
	memdelete(gd);
}

extern "C" [[maybe_unused]] GDExtensionBool GDE_EXPORT gdrml_init(GDExtensionInterfaceGetProcAddress getProcAddress, GDExtensionClassLibraryPtr library, GDExtensionInitialization* initialization) {
	GDExtensionBinding::InitObject binding{ getProcAddress, library, initialization };

	binding.register_initializer(init_gdrml_module);
	binding.register_terminator(deinit_gdrml_module);
	binding.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return binding.init();
}
