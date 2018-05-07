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
	void initialise(boolean createIfNotExists);
	PageCursor openPageCursorForReading(long id);
	long nextId();
	IdRange *nextIdBatch(int size);
	void freeId(long id);
	long getHighId();
	void setHighId(long highId);
	FileChannel *getStorageFileName();
	FileChannel *getIdFileName();
	void openIdGenerator();
	int getRecordSize();
	void close()newRecord();
	RECORD *getRecord(long id, RECORD *record, RecordLoad mode);
	void readIntoRecord(long id, RECORD *record, RecordLoad mode, PageCursor cursor);
	void updateRecord(RECORD *record);
protected:;
	IdType getIdType();
	void deleteIdGenerator();
	RECORD *newRecord();
	IdType idType;
	IdGeneratorFactory *idGeneratorFactory;
	RecordFormat<RECORD> *recordFormat;
	int recordSize;

	void checkAndLoadStorage(bool createIfNotExists);
	void initialiseNewStoreFile(PagedFile file);
	int offsetForId(long id);
	char * getRawRecordData(long id);
	long scanForHighId();
	bool isRecordReserved(PageCursor cursor);

private:
	IdGenerator *idGenerator;
	bool storeOk = true;

	void loadIdGenerator();
	void createStore(int pageSize)
	boolean isInUse(PageCursor cursor);
	void createIdGenerator(File fileName);
	closeIdGenerator();
	void flush();

};

