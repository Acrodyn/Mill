#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"
#include <vector>

class Piece;
class Connection;
enum class ConnectionDirection;
struct ConnectionReport;

class Node : public ScreenRelatedObject
{
public:
	Node() = delete;
	Node(float positionX, float positionY);
	~Node();

	void Update() override;

	void PairWith(Node* node, Connection* connection);
	float GetSize();
	void SetHostedPiece(Piece* piece);
	void ResetHostedPiece();
	Piece* GetOccupiedPiece();
	void CalculateConnections(ConnectionReport& report);

private:
	void CalculateConnections(ConnectionReport& report, bool checkAdjacentNodes, Node* filterNode, ConnectionDirection relevantDirection);

private:
	const float NODE_SIZE = 10.f;

	std::vector<std::pair<Node*, Connection*>> _pairedNodes;
	Piece* _hostedPiece = nullptr;
};