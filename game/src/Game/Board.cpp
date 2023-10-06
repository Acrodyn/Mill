#include "Board.h"
#include "System/Core.h"
#include "Node.h"
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
}

void Board::Update()
{
    for (Connection* connection : _connections)
    {
        connection->Update();
    }

    for (Node* node : _nodes)
    {
        node->Update();;
    }
}

Node* Board::CreateNode(float screenPosX, float screenPosY)
{
    Node* newNode = new Node(screenPosX, screenPosY);
    _nodes.push_back(newNode);

    return newNode;
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
