#pragma once

namespace GLProgram {
	/// <summary>
	/// Returns already linked program with attached vertex and fragment shaders
	/// </summary>
	/// <param name="vertexShaderPath"></param>
	/// <param name="fragmentShaderPath"></param>
	/// <returns></returns>
	unsigned int CreateProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
}