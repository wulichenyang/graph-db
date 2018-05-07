#pragma once

class NeoStoreTransactionApplier
{
public:
	NeoStoreTransactionApplier();
	~NeoStoreTransactionApplier();

private:
	NeoStores *neoStores;
	bool visitNodeCommand(Command::NodeCommand command);
	bool visitRelationshipCommand(Command::RelationshipCommand command);
	bool visitRelationshipTypeTokenCommand(Command::RelationshipTypeTokenCommand command);
	bool visitLabelTokenCommand(Command::LabelTokenCommand command);

};

