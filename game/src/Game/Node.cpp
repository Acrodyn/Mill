#include "Node.h"
#include "Connection.h"
#include "Piece.h"
#include "System/Core.h"

Node::Node(float positionX, float positionY) : ScreenRelatedObject{ positionX,  positionY }
{

}

Node::~Node()
{
	RemoveHostedPiece();
}

void Node::Update()
{
	CheckForClick();

	if (_hostedPiece != nullptr)
	{
		if (_hostedPiece->IsMoving())
		{
			_hostedPiece = nullptr;
		}
		else
		{
			_hostedPiece->Update();
		}
	}
	else
	{
		DrawCircle(GetPositionX(), GetPositionY(), NODE_SIZE, _isMarked ? GREEN : RAYWHITE);
	}
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

void Node::RemoveHostedPiece()
{
	if (_hostedPiece != nullptr)
	{
		delete _hostedPiece;
		_hostedPiece = nullptr;
	}
}

bool Node::HasHostedPiece()
{
	return _hostedPiece != nullptr;
}

Piece* Node::GetHostedPiece()
{
	return _hostedPiece;
}

void Node::CalculateConnections(ConnectionReport& report)
{
	CalculateConnections(report, true, nullptr, ConnectionDirection::Unset);
}

void Node::MarkNode()
{
	if (_hostedPiece != nullptr)
	{
		return;
	}

	_isMarked = true;
}

void Node::MarkAdjacentNodes()
{
	for (auto pairedNode : _pairedNodes)
	{
		pairedNode.first->MarkNode();
	}
}

void Node::UnmarkNode()
{
	_isMarked = false;
}

bool Node::IsMarked()
{
	return _isMarked;
}

bool Node::HasFreeAdjacentNodes()
{
	for (auto pairedNode : _pairedNodes)
	{
		if (!pairedNode.first->HasHostedPiece())
		{
			return true;
		}
	}

	return false;
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
			if (_hostedPiece->GetOwningPlayerID() != pairedNode.first->_hostedPiece->GetOwningPlayerID())
			{
				continue;
			}

			ConnectionDirection nodeDirection = pairedNode.second->GetDirection();
			if (relevantDirection != ConnectionDirection::Unset && nodeDirection != relevantDirection)
			{
				continue;
			}

			report.Connections[nodeDirection].push_back(pairedNode.second);
		}

		if (checkAdjacentNodes)
		{
			pairedNode.first->CalculateConnections(report, false, this, pairedNode.second->GetDirection());
		}
	}
}

bool Node::IsMouseOnObject()
{
	return CheckCollisionPointCircle(GetMousePosition(), GetPosition(), GetSize() * COLLISION_CHECK_MULTIPLIER);
}
