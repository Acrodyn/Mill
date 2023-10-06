#include "Connection.h"
#include "Node.h"
#include "System/Core.h"

Connection::Connection(Node* node1, Node* node2)
{
	_node1 = node1;
	_node2 = node2;
}

Connection::~Connection()
{
	
}

void Connection::Update()
{
	DrawLine(_node1->GetPositionX(), _node1->GetPositionY(), _node2->GetPositionX(), _node2->GetPositionY(), RAYWHITE);
}
