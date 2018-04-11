#pragma once
class Record
{
public:
	enum RecEnum {
		NULL_REFERENCE = -1,
		NOT_IN_USE = 0,
		IN_USE = 1,
		FIRST_IN_CHAIN = 2,
		RESERVED = (-1),
		NO_NEXT_PROPERTY = NULL_REFERENCE,
		NO_PREVIOUS_PROPERTY = NULL_REFERENCE,
		NO_NEXT_RELATIONSHIP = NULL_REFERENCE,
		NO_PREV_RELATIONSHIP = NULL_REFERENCE,
		NO_NEXT_BLOCK = NULL_REFERENCE,

		NODE_PROPERTY = 0,
		REL_PROPERTY = 2,
		NO_LABELS_FIELD = 0
	} state;

	Record(RecEnum type);
	~Record();

	void setType(RecEnum type);
	RecEnum getType() const;
	int getIntType() const;
	long getLongType() const;
	char getByteType() const;
	bool is(long value) const;

};



