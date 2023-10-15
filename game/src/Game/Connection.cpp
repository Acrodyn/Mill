#include "Connection.h"
#include "Node.h"
#include "System/Core.h"

Connection::Connection(Node* node1, Node* node2, ConnectionDirection direction) : _node1(node1), _node2(node2), _direction(direction)
{

}

Connection::~Connection()
{
	
}

void Connection::Update()
{
	DrawLine(_node1->GetPixelPositionX(), _node1->GetPixelPositionY(), _node2->GetPixelPositionX(), _node2->GetPixelPositionY(), _isMarked ? YELLOW : RAYWHITE);
}

ConnectionDirection Connection::GetDirection()
{
	return _direction;
}

void Connection::SetAsMarked(bool isMarked)
{
	_isMarked = isMarked;
}

bool Connection::ContainsNode(Node* node)
{
	return node == _node1 || node == _node2;
}
