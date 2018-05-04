#pragma once
#include "../../../io/fs/FileChannel.h"
#include "id/IdType.h"
#include "id/IdGeneratorFactory.h"
#include "format/RecordFormat.h"
#include "record/AbstractBaseRecord.h"

template <class RECORD>
class CommonAbstractStore:public AbstractBaseRecord
{
public:
	FileChannel *storageFileName;

	CommonAbstractStore();
	~CommonAbstractStore();
	CommonAbstractStore(
		FileChannel *fileName,
		IdType idType,
		IdGeneratorFactory *idGeneratorFactory,
		RecordFormat<RECORD> *recordFormat
	);

	// 读取文件中的inuse标志位
	virtual bool isInUse(long id);

protected:
	IdType idType;
	IdGeneratorFactory *idGeneratorFactory;
	RecordFormat<RECORD> *recordFormat;
	int recordSize;

private:
	IdGenerator *idGenerator;
	bool storeOk = true;
};

