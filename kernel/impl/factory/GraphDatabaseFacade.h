#pragma once
#include "../core/EmbeddedProxySPI.h"
#include "../../internal/GraphDatabaseAPI.h"
#include "../core/NodeProxy.h"
#include "../core/RelationshipProxy.h"
#include "../../api/KernelTransaction.h"
#include "../../api/KernelStatement.h"

class GraphDatabaseFacade: public EmbeddedProxySPI, public GraphDatabaseAPI
{
public:
	GraphDatabaseFacade();
	~GraphDatabaseFacade();

	void init();
	NodeProxy *createNode();
	long createNodeId();
	NodeProxy *createNode(Label labels[]);
	NodeProxy *getNodeById(long id);
	RelationshipProxy *getRelationshipById(long id);
	KernelTransaction *beginTx();
	vector<NodeProxy> getAllNodes();
	vector<Relationship> getAllRelationships();
	vector<Label> getAllLabels();
	vector<RelationshipType> getAllRelationshipTypes();
	vector<string> getAllPropertyKeys();
	template <typename T>
	vector<Node> findNodes(const Label &myLabel, const string &key, const T &value);
	template <typename T>
	NodeProxy *findNode(const Label &myLabel, const string &key, const T &value);;
	vector<NodeProxy> findNodes(const Label &myLabel);
	template <typename T>
	vector<NodeProxy> nodesByLabelAndProperty(const Label &myLabel, const string &key, const T &value);
	vector<NodeProxy> allNodesWithLabel(const Label &myLabel);

	KernelTransaction *getTx();
	KernelStatement *statement();
	GraphDatabaseService *getGraphDatabase();
	void failTransaction();
	RelationshipProxy *newRelationshipProxy(const long &id);
	RelationshipProxy *newRelationshipProxy(const long &id, const long &startNodeId, const int &typeId, const long &endNodeId);
	NodeProxy *newNodeProxy(long nodeId);
	RelationshipType getRelationshipTypeById(int type);
	int getRelationshipTypeIdByName(string typeName);

private:
	KernelTransaction *tx;
};

