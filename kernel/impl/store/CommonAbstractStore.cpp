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

template<class RECORD>
inline void CommonAbstractStore<RECORD>::updateRecord(RECORD * record)
{
	long id = record->getId();
	// 验证id是否合法
	IdValidator::assertValidId(getIdType(), id, recordFormat->getMaxId());
	// 
	long blockId = blockIdForRecord(id);

	try
	{
		fileSwapper.write(record);

		// 删除后，释放id
		if (!record->inUse())
		{
			freeId(id);
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what();
	}
}
