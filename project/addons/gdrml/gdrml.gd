@tool
extends EditorPlugin

const PLUGIN_PATH = "res://addons/gdrml/"
const MAIN_PANEL = preload(PLUGIN_PATH + "editors/EditorMainView.tscn")

var mainPanelInstance

func _enter_tree():
	mainPanelInstance = MAIN_PANEL.instantiate()
	
	EditorInterface.get_editor_main_screen().add_child(mainPanelInstance)
	_make_visible(false)
	
	add_autoload_singleton("RmlUIRoot", PLUGIN_PATH + "RmlUIRoot.tscn")

func _exit_tree():
	if mainPanelInstance:
		mainPanelInstance.queue_free()
	
	remove_autoload_singleton("RmlUIRoot")

func _has_main_screen():
	return true

func _make_visible(visible):
	if mainPanelInstance:
		mainPanelInstance.visible = visible

func _get_plugin_name():
	return "RmlUI"

func _get_plugin_icon():
	return load(PLUGIN_PATH + "assets/icons/RmlNodeEditor.png")
