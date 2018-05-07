#include "NeoStoreTransactionApplier.h"



NeoStoreTransactionApplier::NeoStoreTransactionApplier()
{
}


NeoStoreTransactionApplier::~NeoStoreTransactionApplier()
{
}

bool NeoStoreTransactionApplier::visitNodeCommand(Command::NodeCommand command)
{
	return false;
}

bool NeoStoreTransactionApplier::visitRelationshipCommand(Command::RelationshipCommand command)
{
	return false;
}

bool NeoStoreTransactionApplier::visitRelationshipTypeTokenCommand(Command::RelationshipTypeTokenCommand command)
{
	return false;
}

bool NeoStoreTransactionApplier::visitLabelTokenCommand(Command::LabelTokenCommand command)
{
	return false;
}
