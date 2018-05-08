#pragma once
#include "../../../io/fs/FileChannel.h"
#include "id/IdType.h"
#include "id/IdGeneratorFactory.h"
#include "format/RecordFormat.h"
#include "record/AbstractBaseRecord.h"
#include "../../../io/file/FileSwapper.h"

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
	void freeId(long id);
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
	virtual void updateRecord(RECORD *record);
protected:
	IdType idType;
	IdGeneratorFactory *idGeneratorFactory;
	RecordFormat<RECORD> *recordFormat;
	FileSwapper<RECORD> *fileSwapper;
	int recordSize;

	IdType getIdType();
	void deleteIdGenerator();
	RECORD *newRecord();
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
	bool isInUse(PageCursor cursor);
	void createIdGenerator(File fileName);
	void closeIdGenerator();
	void flush();

};