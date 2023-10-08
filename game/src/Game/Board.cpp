#include "Board.h"
#include "Piece.h"
#include "Node.h"
#include "System/Core.h"
#include "Connection.h"

#include <iostream>

Board::Board()
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

    for (Piece* piece: _pieces)
    {
        delete piece;
    }
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

    for (Piece* piece : _pieces)
    {
        piece->Update(); 
    }
}

void Board::CheckForNodeClick()
{
   // Upgrade with different behaviours in relation to game phase
    for (Node* node : _nodes)
    {
        if (CheckCollisionPointCircle(GetMousePosition(), node->GetPosition(), node->GetSize() * COLLISION_CHECK_MULTIPLIER))
        {
            if (CreatePiece(node) != nullptr)
            {
                if (CheckForMill(node))
                {
                    std::cout << "MILL!!!!!!" << std::endl;
                }
            }

            return;
        }
    }
}

void Board::CheckForPieceClick()
{
    for (Piece* piece : _pieces)
    {

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
    if (parentNode->GetOccupiedPiece() != nullptr)
    {
        return nullptr;
    }

    Piece* newPiece = new Piece(parentNode->GetScreenRelatedPosition());
    _pieces.push_back(newPiece);
    parentNode->SetHostedPiece(newPiece);

    return newPiece;
}

void Board::CreateConnection(Node* node1, Node* node2, ConnectionDirection direction)
{
    Connection* newConnection = new Connection(node1, node2, direction);
    _connections.push_back(newConnection);
    PairNodes(node1, node2, newConnection);
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
