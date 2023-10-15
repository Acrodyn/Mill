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

enum class WinCondition
{
	Unset,
	Mill,
	LowPieceCount,
	InsufficientMoves
};

class Board
{
public:
	Board();
	Board(uint8_t piecesPerPlayer);
	virtual ~Board();

	void Init(uint8_t playerCount = 2);
	void Update();
	void Reset();

	void SetupFlying(bool hasFlying, uint8_t flyingPieceThreshold = 3);
	Player* GetPlayer(uint8_t playerID);
	Player* GetCurrentPlayer();
	std::string GetPhaseDescriptionForPlayer(uint8_t playerOrder);

protected:
	virtual void SetupBoard() = 0;
	virtual bool CheckForWinConditions(WinCondition winCondition) = 0;

	Node* CreateNode(float screenPosX, float screenPosY);
	bool CreatePiece(Node* parentNode);
	void CreateConnection(Node* node1, Node* node2, ConnectionDirection direction);
	void CreateConnection(Node* node1, Node* node2, Node* node3, ConnectionDirection direction);

private:
	void SetupPlayers();
	void StartNextPlayer();
	void EvaluatePlayerPhase(Player* player);
	void TriggerMillEffect();
	void MarkRemovablePieces(Player* remover, bool ignoreMilledNodes = true);
	void MarkMoveablePieces(Player* remover);
	void MarkAllFreeNodes();
	void UnmarkAllPieces();
	void UnmarkAllNodes();
	void UnmarkAllSelectablePieces();
	void UnmarkAllConnections();
	void SetSelectedPiece(Node* hostNode);
	void RehostSelectedPiece(Node* newHost);
	void EvaluateNodeInteraction(Node* node);
	void PairNodes(Node* node1, Node* node2, Connection* connection);
	void TryPiecePlacement(Node* node);
	void TryPieceRemoval(Node* node);
	void TryPieceMovement(Node* node);
	int GetPlayerPiecesOnBoard(Player* player);
	bool AnyPiecePlaced();
	bool IsThereRemoveablePieces(Player* remover);
	bool CheckForMill(Node* node, bool markMill = false);
	bool CheckIfWinner(Player* player, WinCondition winCondition);
	bool ShouldCheckNodeInteractions();
	bool CheckIfPossibleMoves(Player* player);
	bool AnyFreeNode();
	bool DoesPlayerHaveMovementOptions(Player* player);
	Player* GetNextPlayer();

private:
	const uint8_t PIECES_PER_PLAYER = 0;
	const uint8_t MILL_CONNECTION_CONDITION = 2;
	const uint8_t LOW_PIECE_COUNT = 2;

	std::unordered_map<uint8_t, Player*> _players;
	std::vector<Node*> _nodes;
	std::vector<Connection*> _connections;

	uint8_t _currentPlayerIndex = 0;
	uint8_t _playerCount = 0;
	uint8_t _flyingPieceThreshold = 3;
	Piece* _selectedPiece = nullptr;
	bool _isGameInProgress = false;
	bool _isFlyingAllowed = false;
};