#pragma once

#include "raylib.h"
#include <vector>
#include <string>
#include <unordered_map>

class Node;
class Piece;
class Player;
class Connection;
enum class ConnectionDirection;

enum class PlayerPhase
{
	Unset,
	Placing,
	Removing,
	Moving,
	Flying
};

class Board
{
public:
	Board();
	Board(uint8_t piecesPerPlayer, bool isFlyingAllowed, uint8_t flyingPieceThreshold = 0);
	virtual ~Board();

	void Init(uint8_t playerCount = 2);
	void Update();

	Player* GetPlayer(uint8_t playerID);
	Player* GetCurrentPlayer();
	std::string GetPhaseDescriptionForPlayer(uint8_t playerOrder);

protected:
	virtual void SetupBoard() = 0;
	virtual bool CheckForWinConditions() = 0;

	Node* CreateNode(float screenPosX, float screenPosY);
	bool CreatePiece(Node* parentNode);
	void CreateConnection(Node* node1, Node* node2, ConnectionDirection direction);
	void CreateConnection(Node* node1, Node* node2, Node* node3, ConnectionDirection direction);

private:
	void SetupPlayers();
	void StartNextPlayer();
	void EvaluatePlayerPhase(Player* player);
	int GetPlayerPiecesOnBoard(Player* player);
	bool AnyPiecePlaced();
	bool CheckForMill(Node* node, bool markMill = false);
	bool CheckIfWinner(Player* player);
	bool ShouldCheckNodeInteractions();
	void TriggerMillEffect();
	void MarkRemovablePieces(Player* remover, bool ignoreMilledNodes = true);
	void UnmarkAllPieces();
	void MarkAllFreeNodes();
	void UnmarkAllNodes();
	void UnmarkAllConnections();
	void SetSelectedPiece(Node* hostNode);
	void RehostSelectedPiece(Node* newHost);
	void EvaluateNodeInteraction(Node* node);
	void PairNodes(Node* node1, Node* node2, Connection* connection);
	void TryPiecePlacement(Node* node);
	void TryPieceRemoval(Node* node);
	void TryPieceMovement(Node* node);

protected:
	const uint8_t PIECES_PER_PLAYER = 0;
	const bool IS_FLYING_ALLOWED = false;
	const uint8_t FLYING_PIECE_THRESHOLD = 3;

private:
	const uint8_t MILL_CONNECTION_CONDITION = 2;

	std::unordered_map<uint8_t, Player*> _players;
	std::vector<Node*> _nodes;
	std::vector<Connection*> _connections;

	uint8_t _currentPlayerIndex = 0;
	uint8_t _playerCount = 0;
	Piece* _selectedPiece = nullptr;
	bool _isGameInProgress = false;
};