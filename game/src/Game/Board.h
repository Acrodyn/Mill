#pragma once

#include "raylib.h"
#include <vector>

class Piece;
class Node;
class Connection;
enum class ConnectionDirection;

class Board
{
public:
	Board();
	virtual ~Board();

	virtual void Init() = 0;
	virtual void Update();

	void CheckForNodeClick();
	void CheckForPieceClick();

protected:
	virtual bool CheckForWinConditions() = 0;

	Node* CreateNode(float screenPosX, float screenPosY);
	Piece* CreatePiece(Node* parentNode);
	void CreateConnection(Node* node1, Node* node2, ConnectionDirection direction);

private:
	bool CheckForMill(Node* node);
	bool CheckAdjacentNodesForConnections(Node* node);
	void PairNodes(Node* node1, Node* node2, Connection* connection);

protected:
	int _piecesPerPlayer = 0;
	int _nodesCount = 0;

	std::vector<Piece*> _pieces;
	std::vector<Node*> _nodes;
	std::vector<Connection*> _connections;

private:
	const int COLLISION_CHECK_MULTIPLIER = 3;
	const int MILL_CONNECTION_CONDITION = 2;
};