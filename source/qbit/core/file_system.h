#pragma once

#include "buffer.h"

#include <filesystem>

namespace Qbit {

	class FileSystem
	{
	public:
		// TODO: move to FileSystem class
		static Buffer ReadFileBinary(const std::filesystem::path& filepath);
	};

}