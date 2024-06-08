#pragma once

enum Shaders
{
	VERTEX_SHADER = 1,
	HULL_SHADER = 2,
	DOMAIN_SHADER = 4,
	GEOMETRY_SHADER = 8,
	PIXEL_SHADER = 16,
	ALL_SHADER = 31
};

class PipelineBinding
{
public:
	PipelineBinding(int pipelineStages, unsigned int bindingRegister);
	~PipelineBinding() = default;

	void setStages(int stages);
	void resetStages(int stages);
	void setBindingRegister(int bindRegister);

	int getStages() { return pipelineStages; }
	int getBindingRegister() { return bindingRegister; }

protected:
	int pipelineStages;
	unsigned int bindingRegister;
};