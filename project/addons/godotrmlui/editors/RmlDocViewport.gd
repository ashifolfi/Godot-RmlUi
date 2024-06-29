@tool
extends VBoxContainer

const PLUGIN_PATH = "res://addons/godotrmlui/"
@export var Toolbar: HBoxContainer

enum ToolMode
{
	Select,
	Move
}

# Called when the node enters the scene tree for the first time.
func _ready():
	# add toolbar buttons
	_CreateToolbarButton("editor::ToolSelect", null)
	_CreateToolbarButton("editor::ToolPan", null)
	_CreateToolbarButton("editor::ToolMove", null)
	pass

func _CreateToolbarButton(iconName: String, action):
	var _button = Button.new()
	_button.flat = true
	_button.toggle_mode = true
	
	# using an editor icon
	if iconName.begins_with("editor::"):
		_button.icon = EditorInterface.get_editor_theme().get_icon(iconName.split("::")[1], "EditorIcons")
	else:
		_button.icon = load(PLUGIN_PATH + "assets/icons/" + iconName + ".png")
	
	Toolbar.add_child(_button)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
