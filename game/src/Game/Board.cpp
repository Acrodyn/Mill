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
    _isGameInProgress = true;
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
    if (_players.size() < playerOrder || playerOrder == 0)
    {
        return nullptr;
    }

    return _players.at(playerOrder - 1);
}

Player* Board::GetCurrentPlayer()
{
    return _players.at(_currentPlayerIndex);
}

std::string Board::GetPhaseDescriptionForPlayer(uint8_t playerOrder)
{
    if (!_isGameInProgress)
    {
        Player* player = GetPlayer(playerOrder);
        return player->IsVictor() ? "Victory" : "Defeat";
    }

    if (GetCurrentPlayer() != GetPlayer(playerOrder))
    {
        return "Wait";
    }

    switch (GetPlayer(playerOrder)->GetPhase())
    {
    case PlayerPhase::Placing:
        return "Place";
    case PlayerPhase::Removing:
        return "Remove";
    case PlayerPhase::Moving:
        return "Move";
    case PlayerPhase::Flying:
        return "Fly";

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

bool Board::CreatePiece(Node* parentNode)
{
    if (parentNode->GetHostedPiece() != nullptr)
    {
        return false;
    }

    Piece* newPiece = new Piece(parentNode->GetScreenRelatedPosition(), GetCurrentPlayer());
    parentNode->SetHostedPiece(newPiece);

    return true;
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

bool Board::AnyPiecePlaced()
{
    for (Node* node : _nodes)
    {
        if (node->HasHostedPiece())
        {
            return true;
        }
    }

    return false;
}

void Board::MarkRemovablePieces(Player* remover, bool ignoreMilledNodes)
{
    if (!AnyPiecePlaced())
    {
        return;
    }

    std::vector<Node*> piecesToMark;

    for (Node* node : _nodes)
    {
        if (!node->HasHostedPiece() || (node->GetHostedPiece()->GetOwningPlayerID() == remover->GetID()))
        {
            continue;
        }

        if (!ignoreMilledNodes || (ignoreMilledNodes && !CheckForMill(node)))
        {
            piecesToMark.push_back(node);
        }
    }

    if (piecesToMark.size() == 0)
    {
        MarkRemovablePieces(remover, false);
        return;
    }

    for (Node* node : piecesToMark)
    {
        node->GetHostedPiece()->MarkAsRemovable();
    }
}

void Board::UnmarkAllPieces()
{
    for (Node* node : _nodes)
    {
        if (node->HasHostedPiece())
        {
            node->GetHostedPiece()->MarkAsRemovable(false);
        }
    }
}

bool Board::CheckIfWinner(Player* player)
{
    if (CheckForWinConditions())
    {
        player->MarkAsVictor();
        _isGameInProgress = false;
        return true;
    }

    return false;
}

bool Board::EvaluateNodeInteraction(Node* node)
{
    PlayerPhase currentPhase = GetCurrentPlayer()->GetPhase();

    switch (currentPhase)
    {
    case PlayerPhase::Moving:
        return TryPieceMovement(node);
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

    if (CreatePiece(node))
    {
        GetCurrentPlayer()->RemovePiece();

        if (CheckForMill(node))
        {
            if (!CheckIfWinner(currentPlayer))
            {
                currentPlayer->SetPhase(PlayerPhase::Removing);
                MarkRemovablePieces(currentPlayer);
            }

            return true;
        }

        StartNextPlayer();
    }

    return true;
}

bool Board::TryPieceRemoval(Node* node)
{
    if (node->HasHostedPiece() && node->GetHostedPiece()->IsRemovable())
    {
        node->RemoveHostedPiece();
        GetCurrentPlayer()->BacktrackPhase();
        UnmarkAllPieces();
        StartNextPlayer();

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
