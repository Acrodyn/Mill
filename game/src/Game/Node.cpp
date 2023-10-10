#include "Node.h"
#include "Connection.h"
#include "System/Core.h"

Node::Node(float positionX, float positionY) : ScreenRelatedObject{ positionX,  positionY }
{

}

Node::~Node()
{
	
}

void Node::Update()
{
	DrawCircle(GetPositionX(), GetPositionY(), NODE_SIZE, RAYWHITE);
}

void Node::PairWith(Node* node, Connection* connection)
{
	_pairedNodes.push_back(std::make_pair(node, connection));
}

float Node::GetSize()
{
	return NODE_SIZE;
}

void Node::SetHostedPiece(Piece* piece)
{
	_hostedPiece = piece;
}

void Node::ResetHostedPiece()
{
	_hostedPiece = nullptr;
}

Piece* Node::GetOccupiedPiece()
{
	return _hostedPiece;
}

void Node::CalculateConnections(ConnectionReport& report)
{
	CalculateConnections(report, true, nullptr, ConnectionDirection::Unset);
}

void Node::CalculateConnections(ConnectionReport& report, bool checkAdjacentNodes, Node* filterNode, ConnectionDirection relevantDirection)
{
	if (_hostedPiece == nullptr || &(*this) == &(*filterNode))
	{
		return;
	}

	for (auto pairedNode : _pairedNodes)
	{
		if (pairedNode.first->_hostedPiece != nullptr && &(*pairedNode.first) != &(*filterNode))
		{
			ConnectionDirection nodeDirection = pairedNode.second->GetDirection();

			if (relevantDirection != ConnectionDirection::Unset && nodeDirection != relevantDirection)
			{
				continue;
			}

			if (report.Connections.find(nodeDirection) == report.Connections.end())
			{
				report.Connections[nodeDirection] = 0;
			}

			++report.Connections[nodeDirection];
		}

		if (checkAdjacentNodes)
		{
			pairedNode.first->CalculateConnections(report, false, this, pairedNode.second->GetDirection());
		}
	}
} 