#pragma once

#include <cstddef>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/string.hpp>

namespace godot::Conversion {

PackedByteArray bufferToByteArray(std::span<const std::byte> buffer);

std::vector<std::byte> byteArrayToBuffer(const PackedByteArray& byteArray);

String stringToGodot(std::string_view string);

std::string stringToStd(const String& string);

} // namespace godot::Conversion
