#include "LabelState.h"



LabelState::LabelState()
{
}

LabelState::~LabelState()
{
}

long LabelState::getLabelId()
{
	return this->labelId;
}

SuperDiffSets<int> LabelState::nodeDiffSets()
{
	return this->labelDiffSets;
}
