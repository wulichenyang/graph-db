#include "StoreFactory.h"

const string StoreFactory::LABELS_PART = ".labels";
const string StoreFactory::NAMES_PART = ".names";
const string StoreFactory::INDEX_PART = ".index";
const string StoreFactory::KEYS_PART = ".keys";
const string StoreFactory::ARRAYS_PART = ".arrays";
const string StoreFactory::STRINGS_PART = ".strings";
const string StoreFactory::NODE_STORE_NAME = ".nodestore.db";
const string StoreFactory::NODE_LABELS_STORE_NAME = NODE_STORE_NAME + LABELS_PART;
const string StoreFactory::PROPERTY_STORE_NAME = ".propertystore.db";
const string StoreFactory::PROPERTY_KEY_TOKEN_STORE_NAME = PROPERTY_STORE_NAME + INDEX_PART;
const string StoreFactory::PROPERTY_KEY_TOKEN_NAMES_STORE_NAME = PROPERTY_STORE_NAME + INDEX_PART + KEYS_PART;
const string StoreFactory::PROPERTY_STRINGS_STORE_NAME = PROPERTY_STORE_NAME + STRINGS_PART;
const string StoreFactory::PROPERTY_ARRAYS_STORE_NAME = PROPERTY_STORE_NAME + ARRAYS_PART;
const string StoreFactory::RELATIONSHIP_STORE_NAME = ".relationshipstore.db";
const string StoreFactory::RELATIONSHIP_TYPE_TOKEN_STORE_NAME = ".relationshiptypestore.db";
const string StoreFactory::RELATIONSHIP_TYPE_TOKEN_NAMES_STORE_NAME = RELATIONSHIP_TYPE_TOKEN_STORE_NAME +
NAMES_PART;
const string StoreFactory::LABEL_TOKEN_STORE_NAME = ".labeltokenstore.db";
const string StoreFactory::LABEL_TOKEN_NAMES_STORE_NAME = LABEL_TOKEN_STORE_NAME + NAMES_PART;
const string StoreFactory::SCHEMA_STORE_NAME = ".schemastore.db";
const string StoreFactory::RELATIONSHIP_GROUP_STORE_NAME = ".relationshipgroupstore.db";
const string StoreFactory::COUNTS_STORE = ".counts.db";

const char* StoreFactory::DEFAULT_NAME = (char*)"neostore";

StoreFactory::StoreFactory()
{
}

StoreFactory::StoreFactory(char * storeDir, IdGeneratorFactory * idGeneratorFactory, FileChannel * file)
{
	this->idGeneratorFactory = idGeneratorFactory;
	this->recordFormats = recordFormats;
	// 没有建立文件夹
	this->neoStoreFileName = new FileChannel(storeDir, StoreFactory::DEFAULT_NAME);
}


StoreFactory::~StoreFactory()
{
}
