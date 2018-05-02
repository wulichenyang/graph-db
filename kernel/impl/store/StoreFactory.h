#pragma once
#include <string>
#include "format/RecordFormats.h"
#include "id/IdGeneratorFactory.h"
#include "NeoStores.h"
#include "StoreType.h"

using namespace std;

class StoreFactory
{
public:
	StoreFactory();
	// 没有建立文件夹
	StoreFactory(char *storeDir, IdGeneratorFactory *idGeneratorFactory, FileChannel *file);
	~StoreFactory();

	NeoStores *openAllNeoStores();
	NeoStores *openAllNeoStores(bool createStoreIfNotExists);
	NeoStores *openNeoStores(StoreType storeTypes[]);
	NeoStores *openNeoStores(bool createStoreIfNotExists, StoreType storeTypes[]);


private:
	const static string LABELS_PART;
	const static string NAMES_PART;
	const static string INDEX_PART;
	const static string KEYS_PART;
	const static string ARRAYS_PART;
	const static string STRINGS_PART;
	const static string NODE_STORE_NAME;
	const static string NODE_LABELS_STORE_NAME;
	const static string PROPERTY_STORE_NAME;
	const static string PROPERTY_KEY_TOKEN_STORE_NAME;
	const static string PROPERTY_KEY_TOKEN_NAMES_STORE_NAME;
	const static string PROPERTY_STRINGS_STORE_NAME;
	const static string PROPERTY_ARRAYS_STORE_NAME;
	const static string RELATIONSHIP_STORE_NAME;
	const static string RELATIONSHIP_TYPE_TOKEN_STORE_NAME;
	const static string RELATIONSHIP_TYPE_TOKEN_NAMES_STORE_NAME;
	const static string LABEL_TOKEN_STORE_NAME;
	const static string LABEL_TOKEN_NAMES_STORE_NAME;
	const static string SCHEMA_STORE_NAME;
	const static string RELATIONSHIP_GROUP_STORE_NAME;
	const static string COUNTS_STORE;

	const static char* DEFAULT_NAME;
private:
	IdGeneratorFactory *idGeneratorFactory;
	FileChannel *neoStoreFileName;
	RecordFormats *recordFormats;

};

