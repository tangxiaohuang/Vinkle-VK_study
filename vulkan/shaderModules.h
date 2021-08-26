#pragma once

#include <iostream>
#include <vector>

class shaderModules
{
public:
	void createGraphicsPipeline();

	VkShaderModule createShaderModule(const std::vector<char>& code);

	static std::vector<char> readFile(const std::string& filename);
};