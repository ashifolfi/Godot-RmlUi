extends RmlNode

@export var demo_scenes: Array[PackedScene]
var current_scene = 0

# Called when the node enters the scene tree for the first time.
func _ready():
	connect_event("nextButton", "click", _next_demo)
	connect_event("prevButton", "click", _prev_demo)

func _next_demo():
	if current_scene < demo_scenes.size() - 1:
		current_scene += 1
	else:
		current_scene = 0
	
	get_tree().change_scene_to_packed(demo_scenes[current_scene]);

func _prev_demo():
	if current_scene > 0:
		current_scene -= 1
	else:
		current_scene = demo_scenes.size() - 1
	
	get_tree().change_scene_to_packed(demo_scenes[current_scene]);
