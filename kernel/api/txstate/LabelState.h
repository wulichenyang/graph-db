#pragma once
class LabelState
{
public:
	LabelState();
	~LabelState();
	long getLabelId();
	SuperDiffSets<int> nodeDiffSets();

private:
	SuperDiffSets<int> labelDiffSets;
	long labelId;
};

