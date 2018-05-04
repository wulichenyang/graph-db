#include "CommonAbstractStore.h"


template<class RECORD>
CommonAbstractStore::CommonAbstractStore()
{
}

template<class RECORD>
CommonAbstractStore::~CommonAbstractStore()
{
}

template<class RECORD>
CommonAbstractStore<RECORD>::CommonAbstractStore(FileChannel * fileName, IdType idType, IdGeneratorFactory * idGeneratorFactory, RecordFormat<RECORD>* recordFormat)
{
	this->storageFileName = fileName;
	this->idType = idType;
	this->idGeneratorFactory = idGeneratorFactory;
	this->recordFormat = recordFormat;
}

template<class RECORD>
bool CommonAbstractStore<RECORD>::isInUse(long id)
{
	return false;
}
