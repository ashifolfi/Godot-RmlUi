extends Node

# Called when the node enters the scene tree for the first time.
func _enter_tree():
	if ClassDB.class_exists("RmlUIController"):
		add_child(ClassDB.instantiate("RmlUIController"))
	else:
		printerr("GDRML: FATAL: Cannot instantiate RmlUIController!")
