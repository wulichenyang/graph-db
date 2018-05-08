#pragma once
#include "../fs/FileChannel.h"
#include "../lock/FileLock.h"
#include "../../kernel/impl/store/format/RecordFormat.h"

using namespace std;

template<class RECORD>
class FileSwapper
{
public:
	int recordSize;

	FileSwapper();
	~FileSwapper();
	long read(RECORD *record);
	long write(RECORD *record);
private:

	// FileChannel µÄÊýÁ¿
	const static int defaultChannelStripePower();
	const static int channelStripeCount;
	FileChannel * fileName;
	FileChannel * channels;

	RecordFormat<RECORD> *recordFormat;

	int swapOut(RECORD *record, long fileOffset, FileChannel *fileChannel);
};
