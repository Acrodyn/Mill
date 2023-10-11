#include "Board.h"
#include "Piece.h"
#include "Node.h"
#include "Player.h"
#include "System/Core.h"
#include "Connection.h"

#include <iostream>

Board::Board()
{

}

Board::Board(uint8_t piecesPerPlayer) : PIECES_PER_PLAYER(piecesPerPlayer)
{

}

Board::~Board()
{
    for (Connection* connection : _connections)
    {
        delete connection;
    }

    for (Node* node : _nodes)
    {
        delete node;
    }

    for (Player* player : _players)
    {
        delete player;
    }
}

void Board::Init(uint8_t playerCount)
{
    _playerCount = playerCount;
    SetupBoard();
    SetupPlayers();
}

void Board::Update()
{
    for (Connection* connection : _connections)
    {
        connection->Update();
    }

    for (Node* node : _nodes)
    {
        node->Update();
    }
}

void Board::CheckForNodeInteraction()
{
    if (!ShouldCheckNodeInteractions())
    {
        return;
    }

    for (Node* node : _nodes)
    {
        if (CheckCollisionPointCircle(GetMousePosition(), node->GetPosition(), node->GetSize() * COLLISION_CHECK_MULTIPLIER))
        {
            if (EvaluateNodeInteraction(node))
            {
                return;
            }
        }
    }
}

Player* Board::GetPlayer(uint8_t playerOrder)
{
    if (_players.size() < playerOrder)
    {
        return nullptr;
    }

    return _players.at(playerOrder - 1);
}

Player* Board::GetCurrentPlayer()
{
    return _players.at(_currentPlayerIndex);
}

std::string Board::GetPhaseDescription(uint8_t playerOrder)
{
    switch (GetPlayer(playerOrder)->GetPhase())
    {
    case PlayerPhase::Placing:
        return "Place a piece";
    case PlayerPhase::Removing:
        return "Remove opponent's piece";
    case PlayerPhase::Moving:
        return "Move a piece to an adjacent node";
    case PlayerPhase::Flying:
        return "Move a piece to any free node";
    case PlayerPhase::Victory:
        return "Victory";
    case PlayerPhase::Defeat:
        return "Defeat";
    case PlayerPhase::Waiting:
        return "Wait";

    default:
        return std::string();
    }
}

Node* Board::CreateNode(float screenPosX, float screenPosY)
{
    Node* newNode = new Node(screenPosX, screenPosY);
    _nodes.push_back(newNode);

    return newNode;
}

Piece* Board::CreatePiece(Node* parentNode)
{
    if (parentNode->GetHostedPiece() != nullptr)
    {
        return nullptr;
    }

    Piece* newPiece = new Piece(parentNode->GetScreenRelatedPosition(), GetCurrentPlayer());
    parentNode->SetHostedPiece(newPiece);

    return newPiece;
}

void Board::CreateConnection(Node* node1, Node* node2, ConnectionDirection direction)
{
    Connection* newConnection = new Connection(node1, node2, direction);
    _connections.push_back(newConnection);
    PairNodes(node1, node2, newConnection);
}

void Board::SetupPlayers()
{
    for (int i = 0; i < _playerCount; ++i)
    {
        Player* newPlayer = new Player(i);
        newPlayer->SetPieceCount(PIECES_PER_PLAYER);
        newPlayer->SetPhase(PlayerPhase::Placing);
        _players.push_back(newPlayer);
    }
}

void Board::StartNextPlayer()
{
    _currentPlayerIndex = (_currentPlayerIndex + 1) % _playerCount;
}

bool Board::CheckIfWinner(Player* player)
{
    if (CheckForWinConditions())
    {
        MarkPlayerAsWinner(player);
        return true;
    }

    return false;
}

void Board::MarkPlayerAsWinner(Player* winningPlayer)
{
    for (Player* player : _players)
    {
        if (winningPlayer != player)
        {
            player->SetPhase(PlayerPhase::Defeat);
        }
    }

    winningPlayer->SetPhase(PlayerPhase::Victory);
}

bool Board::EvaluateNodeInteraction(Node* node)
{
    PlayerPhase currentPhase = GetCurrentPlayer()->GetPhase();

    switch (currentPhase)
    {
    case PlayerPhase::Moving:
        return TryPiecePlacement(node);
    case PlayerPhase::Placing:
        return TryPiecePlacement(node);
    case PlayerPhase::Removing:
        return TryPieceRemoval(node);
    case PlayerPhase::Flying:
        return TryPieceFlight(node);
    default:
        return false;
    }
}

bool Board::ShouldCheckNodeInteractions()
{
    PlayerPhase currentPhase = GetCurrentPlayer()->GetPhase();

    return (currentPhase == PlayerPhase::Moving
        || currentPhase == PlayerPhase::Placing
        || currentPhase == PlayerPhase::Removing
        || currentPhase == PlayerPhase::Flying);
}

bool Board::TryPiecePlacement(Node* node)
{
    Player* currentPlayer = GetCurrentPlayer();

    if (!currentPlayer->HasRemainingPieces())
    {
        return false;
    }

    if (CreatePiece(node) != nullptr)
    {
        GetCurrentPlayer()->RemovePiece();

        if (CheckForMill(node))
        {
            if (!CheckIfWinner(currentPlayer))
            {
                currentPlayer->SetPhase(PlayerPhase::Removing);
            }

            return true;
        }

        StartNextPlayer();
    }

    return true;
}

bool Board::TryPieceRemoval(Node* node)
{
    if (node->HasHostedPiece())
    {
        node->RemoveHostedPiece();
        GetCurrentPlayer()->BacktrackPhase();
        StartNextPlayer();
        GetCurrentPlayer()->AddPiece();

        return true;
    }

    return false;
}

bool Board::TryPieceMovement(Node* node)
{
    return false;
}

bool Board::TryPieceFlight(Node* node)
{
    return false;
}

bool Board::CheckForMill(Node* node)
{
    ConnectionReport newReport;
    node->CalculateConnections(newReport);

    for (auto connection : newReport.Connections)
    {
        if (connection.second >= MILL_CONNECTION_CONDITION)
        {
            return true;
        }
    }

    return false;
}

bool Board::CheckAdjacentNodesForConnections(Node* node)
{
    return false;
}

void Board::PairNodes(Node* node1, Node* node2, Connection* connection)
{
    node1->PairWith(node2, connection);
    node2->PairWith(node1, connection);
}
