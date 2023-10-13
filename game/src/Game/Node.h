#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"
#include "UI/ClickableObject.h"
#include <vector>

class Piece;
class Connection;
enum class ConnectionDirection;
struct ConnectionReport;

class Node : public ScreenRelatedObject, public ClickableObject
{
public:
	Node() = delete;
	Node(float positionX, float positionY);
	~Node();

	void Update() override;

	void PairWith(Node* node, Connection* connection);
	float GetSize();
	void SetHostedPiece(Piece* piece);
	void RemoveHostedPiece();
	bool HasHostedPiece();
	Piece* GetHostedPiece();
	void CalculateConnections(ConnectionReport& report);
	void MarkNode();
	void MarkAdjacentNodes();
	void UnmarkNode();
	bool IsMarked();

private:
	void CalculateConnections(ConnectionReport& report, bool checkAdjacentNodes, Node* filterNode, ConnectionDirection relevantDirection);
	bool IsMouseOnObject() override;

private:
	const float NODE_SIZE = 10.f;
	const uint8_t COLLISION_CHECK_MULTIPLIER = 5;

	std::vector<std::pair<Node*, Connection*>> _pairedNodes;
	Piece* _hostedPiece = nullptr;
	bool _isMarked = false;
};