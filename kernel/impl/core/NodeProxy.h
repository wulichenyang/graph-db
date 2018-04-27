#pragma once
#include "../../../graphdb-api/Entity.h"
#include "../../../graphdb-api/Node.h"
#include "../../../graphdb-api/RelationshipType.h"
#include "../core/EmbeddedProxySPI.h"
#include "RelationshipProxy.h"
#include <vector>
#include "../../../graphdb-api/Label.h"
#include "../../../storageengine/api/Direction.h"
#include "../../api/Statement.h"
#include <map>

using namespace std;

class NodeProxy: public Node
{
public:
	NodeProxy();
	NodeProxy(EmbeddedProxySPI *spi, const long &nodeId);
	~NodeProxy();
	long getId() const override;
	void remove() override;
	vector<RelationshipProxy> getRelationships() const;
	vector<RelationshipProxy> getRelationships(const Direction &dir);
	vector<RelationshipProxy> getRelationships(RelationshipType types[]);
	vector<RelationshipProxy> getRelationships(const RelationshipType &type) const;
	vector<RelationshipProxy> getRelationships(const RelationshipType &type, Direction dir);
	vector<RelationshipProxy> getRelationships(const Direction &direction, RelationshipType types[]);
	bool hasRelationship();
	bool hasRelationship(const Direction &dir);
	bool hasRelationship(RelationshipType types[]);
	bool hasRelationship(const Direction &direction, RelationshipType types[]);
	bool hasRelationship(const RelationshipType &type, const Direction &dir);
	RelationshipProxy getSingleRelationship(RelationshipType type, Direction dir);

	template <typename T> 
	void setProperty(string key, T value);

	template <typename T>
	T removeProperty(string key);

	template <typename T>
	T getProperty(string key, T defaultValue);

	vector<string> getPropertyKeys();

	template <typename T>
	map<string, T> getProperties(string keys[]);

	template <typename T>
	map<string, T> getAllProperties();

	template <typename T>
	T getProperty(string key);

	bool hasProperty(string key);
	RelationshipProxy createRelationshipTo(const NodeProxy &otherNode, const RelationshipType &type);
	void addLabel(const Label &label);
	void removeLabel(const Label &label);
	bool hasLabel(Label label);
	vector<Label> getLabels();
	vector<RelationshipType> getRelationshipTypes();
	int *relTypeIds(RelationshipType types[], Statement statement);
	RelationshipType convertToRelationshipType(Statement statement, const int &relTypeId);
	string toString();
private:
	EmbeddedProxySPI *spi;
	long nodeId;
};

