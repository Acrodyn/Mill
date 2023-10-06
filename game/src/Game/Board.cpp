#include "Board.h"
#include "System/Core.h"
#include "Node.h"

Board::Board()
{

}

Board::~Board()
{
    for (Node* node : _nodes)
    {
        delete node;
    }
}

void Board::Update()
{
    for (Node* node : _nodes)
    {
        node->Update();;
    }
}
