#pragma once
#include "../newapi/Read.h"
#include "../../../storageengine/api/Token.h"
#include "../newapi/AllStoreHolder.h"
#include "../newapi/KernelToken.h"
#include "../../api/KernelTransaction.h"

class Operations
{
public:
	Operations();
	Operations(AllStoreHolder *allStoreHolder, 
		StorageStatement *statement, 
		KernelTransaction *ktx,
		KernelToken *token);
	~Operations();

	void initialize();
	long nodeCreate();
	bool nodeDelete(long node);
	long relationshipCreate(long sourceNode, int relationshipType, long targetNode);
	bool relationshipDelete(long relationship);
	bool nodeAddLabel(long node, int nodeLabel);
	bool nodeRemoveLabel(long node, int nodeLabel);
	template <typename T>
	T nodeSetProperty(long node, int propertyKey, T value);
	template <typename T>
	T nodeRemoveProperty(long node, int propertyKey);
	template <typename T>
	T relationshipSetProperty(long relationship, int propertyKey, T value);
	template <typename T>
	T relationshipRemoveProperty(long node, int propertyKey);
	template <typename T>
	T readNodeProperty(int propertyKey);
	Token getToken();
	void nodeExists(long sourceNode);
	Read dataRead();

private:
	KernelTransaction *ktx;
	AllStoreHolder *allStoreHolder;
	KernelToken *token;
	StorageStatement *statement;

};

