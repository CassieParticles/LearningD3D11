#include "PipelineBinding.h"

PipelineBinding::PipelineBinding(int pipelineStages, unsigned int bindingRegister) :pipelineStages{ pipelineStages },bindingRegister{bindingRegister}
{

}

void PipelineBinding::setStages(int stages)
{
	pipelineStages = pipelineStages | stages;
}

void PipelineBinding::resetStages(int stages)
{
	pipelineStages = pipelineStages & ~stages;
}

void PipelineBinding::setBindingRegister(int bindRegister)
{
	bindingRegister = bindRegister;
}
