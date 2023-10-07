#include "Board.h"
#include "Piece.h"
#include "Node.h"
#include "System/Core.h"
#include "Connection.h"

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
    for (Node* node : _nodes)
    {
        if (CheckCollisionPointCircle(GetMousePosition(), node->GetPosition(), node->GetSize() * COLLISION_CHECK_MULTIPLIER))
        {
            CreatePiece(node);
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

    Piece* newPiece = new Piece(parentNode->GetPositionInRelationToScreen());
    _pieces.push_back(newPiece);
    parentNode->SetHostedPiece(newPiece);

    return newPiece;
}

void Board::CreateConnection(Node* node1, Node* node2, ConnectionDirection direction)
{
    _connections.push_back(new Connection(node1, node2, direction));
    PairNodes(node1, node2);
}

void Board::PairNodes(Node* node1, Node* node2)
{
    node1->PairWith(node2);
    node2->PairWith(node1);
}
