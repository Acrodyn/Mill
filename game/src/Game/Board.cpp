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

Board::Board(uint8_t piecesPerPlayer, bool isFlyingAllowed, uint8_t flyingPieceThreshold) : PIECES_PER_PLAYER(piecesPerPlayer), IS_FLYING_ALLOWED(isFlyingAllowed), FLYING_PIECE_THRESHOLD(flyingPieceThreshold)
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

    if (_selectedPiece != nullptr)
    {
        _selectedPiece->Update();
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
    newNode->RegisterOnClick([=]() { this->EvaluateNodeInteraction(newNode); });
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

void Board::StartNextPhase(Player* player)
{
    if (player->GetRemainingPieces() > 0)
    {
        player->SetPhase(PlayerPhase::Placing);
    }
    else if (IS_FLYING_ALLOWED && GetPlayerPiecesOnBoard(player) < FLYING_PIECE_THRESHOLD)
    {
        player->SetPhase(PlayerPhase::Flying);
    }
    else
    {
        player->SetPhase(PlayerPhase::Moving);
    }
}

int Board::GetPlayerPiecesOnBoard(Player* player)
{
    int pieceCount = 0;

    for (Node* node : _nodes)
    {
        if (!node->HasHostedPiece())
        {
            continue;
        }

        if (node->GetHostedPiece()->GetOwningPlayerID() == player->GetID())
        {
            ++pieceCount;
        }
    }

    return pieceCount;
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

void Board::MarkAllFreeNodes()
{
    for (Node* node : _nodes)
    {
        if (!node->HasHostedPiece())
        {
            node->MarkNode();
        }
    }
}

void Board::UnmarkAllNodes()
{
    for (Node* node : _nodes)
    {
        node->UnmarkNode();
    }
}

void Board::UnmarkAllConnections()
{
    for (Connection* connection : _connections)
    {
        connection->SetAsMarked(false);
    }
}

void Board::SetSelectedPiece(Node* hostNode)
{
    if (_selectedPiece != nullptr && _selectedPiece != hostNode->GetHostedPiece())
    {
        _selectedPiece->SetAsSelected(false);
    }

    if (IS_FLYING_ALLOWED && GetCurrentPlayer()->GetPhase() == PlayerPhase::Flying)
    {
        MarkAllFreeNodes();
    }
    else
    {
        hostNode->MarkAdjacentNodes();
    }

    _selectedPiece = hostNode->GetHostedPiece();
    _selectedPiece->SetAsSelected();
}

void Board::RehostSelectedPiece(Node* newHost)
{
    newHost->SetHostedPiece(_selectedPiece);
    _selectedPiece->SetAsSelected(false);
    _selectedPiece = nullptr;

    if (CheckForMill(newHost))
    {
        TriggerMillEffect();
        return;
    }

    StartNextPlayer();
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

void Board::EvaluateNodeInteraction(Node* node)
{
    if (!ShouldCheckNodeInteractions())
    {
        return;
    }

    PlayerPhase currentPhase = GetCurrentPlayer()->GetPhase();

    switch (currentPhase)
    {
    case PlayerPhase::Moving:
        TryPieceMovement(node);
        break;
    case PlayerPhase::Placing:
        TryPiecePlacement(node);
        break;
    case PlayerPhase::Removing:
        TryPieceRemoval(node);
        break;
    case PlayerPhase::Flying:
        TryPieceFlight(node);
        break;
    }
}

bool Board::ShouldCheckNodeInteractions()
{
    return (_isGameInProgress && GetCurrentPlayer()->GetPhase() != PlayerPhase::Unset) || (_selectedPiece != nullptr && _selectedPiece->IsMoving());
}

void Board::TriggerMillEffect()
{
    Player* currentPlayer = GetCurrentPlayer();
    if (!CheckIfWinner(currentPlayer))
    {
        currentPlayer->SetPhase(PlayerPhase::Removing);
        MarkRemovablePieces(currentPlayer);
    }
}

void Board::TryPiecePlacement(Node* node)
{
    Player* currentPlayer = GetCurrentPlayer();

    if (!currentPlayer->HasRemainingPieces())
    {
        return;
    }

    if (CreatePiece(node))
    {
        currentPlayer->RemovePiece();

        if (CheckForMill(node))
        {
            TriggerMillEffect();
            return;
        }

        StartNextPhase(GetCurrentPlayer());
        StartNextPlayer();
    }
}

void Board::TryPieceRemoval(Node* node)
{
    if (node->HasHostedPiece() && node->GetHostedPiece()->IsRemovable())
    {
        node->RemoveHostedPiece();
        StartNextPhase(GetCurrentPlayer());
        UnmarkAllPieces();
        UnmarkAllConnections();
        StartNextPlayer();
    }
}

void Board::TryPieceMovement(Node* node)
{
    if (_selectedPiece == nullptr && node->HasHostedPiece() && node->GetHostedPiece()->GetOwningPlayerID() == GetCurrentPlayer()->GetID())
    {
        SetSelectedPiece(node);
    }
    else if (_selectedPiece != nullptr)
    {
        if (node->IsMarked())
        {
            UnmarkAllNodes();
            _selectedPiece->MoveToPosition(node->GetScreenRelatedPosition(), [=]() { RehostSelectedPiece(node); });
        }
        else if (node->GetHostedPiece() != nullptr && node->GetHostedPiece()->GetOwningPlayerID() == GetCurrentPlayer()->GetID())
        {
            UnmarkAllNodes();
            SetSelectedPiece(node);
        }
    }
}

void Board::TryPieceFlight(Node* node)
{
    
}

bool Board::CheckForMill(Node* node)
{
    bool isMill = false;
    ConnectionReport newReport;
    node->CalculateConnections(newReport);

    for (auto connection : newReport.Connections)
    {
        if (connection.second.size() >= MILL_CONNECTION_CONDITION)
        {
            isMill = true;
            
            for (Connection* connection : connection.second)
            {
                connection->SetAsMarked();
            }
        }
    }

    return isMill;
}

void Board::PairNodes(Node* node1, Node* node2, Connection* connection)
{
    node1->PairWith(node2, connection);
    node2->PairWith(node1, connection);
}
