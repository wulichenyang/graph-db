#pragma once
#include "../../../graphdb-api/Relationship.h"
#include "../../../graphdb-api/Node.h"
#include "../../../graphdb-api/RelationshipType.h"
#include "../core/EmbeddedProxySPI.h"
#include <vector>
#include "NodeProxy.h"
#include "../store/record/AbstractBaseRecord.h"

using namespace std;

class RelationshipProxy: public Relationship
{
public:
	RelationshipProxy();
	RelationshipProxy(EmbeddedProxySPI spi, long id);
	RelationshipProxy(EmbeddedProxySPI *spi, long id, long startNode, int type, long endNode);
	void visit(long id, int type, long startNode, long endNode);

	~RelationshipProxy();
	long getId() const override;
	int typeId() const;
	long sourceId() const;
	long targetId() const;
	void remove() override;
	NodeProxy *getNodes();
	NodeProxy getOtherNode(Node node);
	NodeProxy getStartNode() const;
	NodeProxy getEndNode() const;
	RelationshipType getType() const override;
	bool isType(RelationshipType type) const override;
	long getStartNodeId() const override;
	long getEndNodeId() const override;
	long getOtherNodeId(long id) const override;

	vector<string> getPropertyKeys();
	template <typename T>
	map<string, T> getProperties(string keys[]);

	template <typename T>
	map<string, T> getAllProperties();

	template <typename T>
	T getProperty(string key);

	template <typename T>
	T getProperty(string key, T defaultValue);

	bool hasProperty(string key);

	template <typename T>
	void setProperty(string key, T value);

	template <typename T>
	T removeProperty(string key);

	bool isType(const RelationshipType &type);
	string toString();
private:
	EmbeddedProxySPI *actions;
	long id = AbstractBaseRecord::NO_ID;
	long startNode = AbstractBaseRecord::NO_ID;
	long endNode = AbstractBaseRecord::NO_ID;
	int type;
};

