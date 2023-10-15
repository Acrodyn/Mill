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

    for (auto player : _players)
    {
        delete player.second;
    }

    _players.clear();
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

void Board::Reset()
{
    for (Connection* connection : _connections)
    {
        connection->SetAsMarked(false);
    }

    for (Node* node : _nodes)
    {
        node->Reset();
    }

    for (auto player : _players)
    {
        player.second->Reset();
    }

    _currentPlayerIndex = 0;
    _selectedPiece = nullptr;
    _isGameInProgress = true;

}

void Board::SetupFlying(bool hasFlying, uint8_t flyingPieceThreshold)
{
    _isFlyingAllowed = hasFlying;
    _flyingPieceThreshold = flyingPieceThreshold;
}

Player* Board::GetPlayer(uint8_t playerID)
{
    if (_players.find(playerID) == _players.end())
    {
        return nullptr;
    }

    return _players[playerID];
}

Player* Board::GetCurrentPlayer()
{
    return _players.at(_currentPlayerIndex + 1);
}

std::string Board::GetPhaseDescriptionForPlayer(uint8_t playerOrder)
{
    if (!_isGameInProgress)
    {
        Player* player = GetPlayer(playerOrder);
        return player->IsWinner() ? "Victory :)" : "Defeat :(";
    }

    if (GetCurrentPlayer() != GetPlayer(playerOrder))
    {
        return "~ Wait ~";
    }

    switch (GetPlayer(playerOrder)->GetPhase())
    {
    case PlayerPhase::Placing:
        return "~ Place ~";
    case PlayerPhase::Removing:
        return "~ Remove ~";
    case PlayerPhase::Moving:
        return "~ Move ~";
    case PlayerPhase::Flying:
        return "~ Fly ~";

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

void Board::CreateConnection(Node* node1, Node* node2, Node* node3, ConnectionDirection direction)
{
    CreateConnection(node1, node2, direction);
    CreateConnection(node2, node3, direction);
}

void Board::SetupPlayers()
{
    for (uint8_t i = 1; i <= _playerCount; ++i)
    {
        Player* newPlayer = new Player(i);
        newPlayer->SetPieceCount(PIECES_PER_PLAYER);
        newPlayer->SetPhase(PlayerPhase::Placing);
        _players[i] = newPlayer;
    }
}

void Board::StartNextPlayer()
{
    int nextPlayerIndex = (_currentPlayerIndex + 1) % _playerCount;
    Player* nextPlayer = GetPlayer(nextPlayerIndex + 1);

    if (!CheckIfPossibleMoves(nextPlayer))
    {
        if (CheckIfWinner(GetCurrentPlayer(), WinCondition::InsufficientMoves))
        {
            return;
        }
    }

    PlayerPhase nextPlayerPhase = nextPlayer->GetPhase();
    if (nextPlayerPhase == PlayerPhase::Moving || nextPlayerPhase == PlayerPhase::Flying)
    {
        MarkMoveablePieces(nextPlayer, nextPlayerPhase == PlayerPhase::Moving);
    }

    _currentPlayerIndex = nextPlayerIndex;
}

void Board::EvaluatePlayerPhase(Player* player)
{
    if (player->GetRemainingPieces() > 0)
    {
        player->SetPhase(PlayerPhase::Placing);
    }
    else if (_isFlyingAllowed && player->GetRemainingPieces() == 0 && GetPlayerPiecesOnBoard(player) <= _flyingPieceThreshold)
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

bool Board::IsThereRemoveablePieces(Player* remover)
{
    for (Node* node : _nodes)
    {
        if (node->HasHostedPiece() && node->GetHostedPiece()->GetOwningPlayerID() != remover->GetID())
        {
            return true;
        }
    }

    return false;
}

void Board::MarkRemovablePieces(Player* remover, bool ignoreMilledNodes)
{
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

void Board::MarkMoveablePieces(Player* player, bool checkAdjacent)
{
    for (Node* node : _nodes)
    {
        if (node->HasHostedPiece() 
            && (node->GetHostedPiece()->GetOwningPlayerID() == player->GetID())
            && ((checkAdjacent && node->HasFreeAdjacentNodes()) || !checkAdjacent))
        {
            node->GetHostedPiece()->MarkAsSelectable();
        }
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

void Board::UnmarkAllSelectablePieces()
{
    for (Node* node : _nodes)
    {
        if (node->HasHostedPiece())
        {
            node->GetHostedPiece()->MarkAsSelectable(false);
        }
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
        _selectedPiece->MarkAsSelected(false);
    }

    if (_isFlyingAllowed && GetCurrentPlayer()->GetPhase() == PlayerPhase::Flying)
    {
        MarkAllFreeNodes();
    }
    else
    {
        hostNode->MarkAdjacentNodes();
    }

    _selectedPiece = hostNode->GetHostedPiece();
    _selectedPiece->MarkAsSelected();
}

void Board::RehostSelectedPiece(Node* newHost)
{
    newHost->SetHostedPiece(_selectedPiece);
    _selectedPiece->MarkAsSelected(false);
    _selectedPiece = nullptr;

    if (CheckForMill(newHost, true))
    {
        TriggerMillEffect();
        return;
    }

    StartNextPlayer();
}

bool Board::CheckIfWinner(Player* player, WinCondition winCondition)
{
    if (CheckForWinConditions(winCondition))
    {
        player->MarkAsVictor();
        _isGameInProgress = false;
        return true;
    }

    return false;
}

bool Board::HasTurn(uint8_t playerID)
{
    return _currentPlayerIndex == (playerID - 1);
}

bool Board::IsWinner(uint8_t playerID)
{
    return GetPlayer(playerID)->IsWinner();
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
    case PlayerPhase::Flying:
        TryPieceMovement(node);
        break;
    case PlayerPhase::Placing:
        TryPiecePlacement(node);
        break;
    case PlayerPhase::Removing:
        TryPieceRemoval(node);
        break;
    }
}

bool Board::ShouldCheckNodeInteractions()
{
    return (_isGameInProgress && GetCurrentPlayer()->GetPhase() != PlayerPhase::Unset) || (_selectedPiece != nullptr && _selectedPiece->IsMoving());
}

bool Board::CheckIfPossibleMoves(Player* player)
{
    switch (player->GetPhase())
    {
    case PlayerPhase::Removing:
        return IsThereRemoveablePieces(player);
    case PlayerPhase::Placing:
    case PlayerPhase::Flying:
        return AnyFreeNode();
    case PlayerPhase::Moving:
        return DoesPlayerHaveMovementOptions(player);
    default:
        return false;
    }
}

bool Board::AnyFreeNode()
{
    for (Node* node : _nodes)
    {
        if (!node->HasHostedPiece())
        {
            return true;
        }
    }

    return false;
}

bool Board::DoesPlayerHaveMovementOptions(Player* player)
{
    for (Node* node : _nodes)
    {
        if (node->HasHostedPiece() 
            && node->GetHostedPiece()->GetOwningPlayerID() == player->GetID() 
            && node->HasFreeAdjacentNodes())
        {
            return true;
        }
    }

    return false;
}

Player* Board::GetNextPlayer()
{
    return GetPlayer(((_currentPlayerIndex + 1) % _playerCount) + 1);
}

void Board::TriggerMillEffect()
{
    Player* currentPlayer = GetCurrentPlayer();
    if (!CheckIfWinner(currentPlayer, WinCondition::Mill))
    {
        if (IsThereRemoveablePieces(currentPlayer))
        {
            currentPlayer->SetPhase(PlayerPhase::Removing);
            MarkRemovablePieces(currentPlayer);
        }
        else
        {
            StartNextPlayer();
        }
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

        if (CheckForMill(node, true))
        {
            TriggerMillEffect();
            return;
        }

        EvaluatePlayerPhase(GetCurrentPlayer());
        StartNextPlayer();
    }
}

void Board::TryPieceRemoval(Node* node)
{
    if (node->HasHostedPiece() && node->GetHostedPiece()->IsRemovable())
    {
        Player* losingPlayer = GetPlayer(node->GetHostedPiece()->GetOwningPlayerID());
        Player* currentPlayer = GetCurrentPlayer();
        
        node->RemoveHostedPiece();
        UnmarkAllPieces();
        UnmarkAllConnections();

        if (losingPlayer->GetPhase() != PlayerPhase::Placing 
            && GetPlayerPiecesOnBoard(losingPlayer) <= LOW_PIECE_COUNT 
            && CheckIfWinner(currentPlayer, WinCondition::LowPieceCount))
        {
            return;
        }

        EvaluatePlayerPhase(losingPlayer);
        EvaluatePlayerPhase(GetCurrentPlayer());
        StartNextPlayer();
    }
}

void Board::TryPieceMovement(Node* node)
{
    if (_selectedPiece != nullptr)
    {
        if (node->IsMarked())
        {
            UnmarkAllSelectablePieces();
            UnmarkAllNodes();
            _selectedPiece->MoveToPosition(node->GetScreenRelatedPosition(), [=]() { RehostSelectedPiece(node); });
            return;
        }
        else if (_selectedPiece->IsMoving())
        {
            return;
        }
    }

    if (node->GetHostedPiece() != nullptr
        && node->GetHostedPiece()->GetOwningPlayerID() == GetCurrentPlayer()->GetID()
        && (GetCurrentPlayer()->GetPhase() == PlayerPhase::Flying || node->HasFreeAdjacentNodes()))
    {
        UnmarkAllNodes();
        SetSelectedPiece(node);
    }
}

bool Board::CheckForMill(Node* node, bool markMill)
{
    ConnectionReport newReport;
    node->CalculateConnections(newReport);

    for (auto connection : newReport.Connections)
    {
        if (connection.second.size() >= MILL_CONNECTION_CONDITION)
        {
            if (markMill)
            {
                for (Connection* connection : connection.second)
                {
                    connection->SetAsMarked();
                }
            }
            
            return true;
        }
    }

    return false;
}

void Board::PairNodes(Node* node1, Node* node2, Connection* connection)
{
    node1->PairWith(node2, connection);
    node2->PairWith(node1, connection);
}
