#pragma once

#include "raylib.h"
#include <vector>

class Player;
class Piece;
class Node;
class Connection;
enum class ConnectionDirection;

class Board
{
public:
	Board();
	Board(uint8_t piecesPerPlayer);
	virtual ~Board();

	void Init(uint8_t playerCount = 2);
	void Update();

	void CheckForNodeClick();
	void CheckForPieceClick();
	Player* GetPlayer(uint8_t playerOrder);
	Player* GetCurrentPlayer();

protected:
	virtual void SetupBoard() = 0;
	virtual bool CheckForWinConditions() = 0;

	Node* CreateNode(float screenPosX, float screenPosY);
	Piece* CreatePiece(Node* parentNode);
	void CreateConnection(Node* node1, Node* node2, ConnectionDirection direction);

private:
	void SetupPlayers();
	void StartNextPlayer();
	bool CheckForMill(Node* node);
	bool CheckAdjacentNodesForConnections(Node* node);
	void PairNodes(Node* node1, Node* node2, Connection* connection);

protected:
	const uint8_t PIECES_PER_PLAYER = 0;

	std::vector<Player*> _players;
	std::vector<Piece*> _pieces;
	std::vector<Node*> _nodes;
	std::vector<Connection*> _connections;

	uint8_t _currentPlayerIndex = 0;
	uint8_t _playerCount = 0;

private:
	const uint8_t COLLISION_CHECK_MULTIPLIER = 3;
	const uint8_t MILL_CONNECTION_CONDITION = 2;
};