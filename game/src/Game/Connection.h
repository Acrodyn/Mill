#pragma once

#include "raylib.h"
#include <vector>

class Node;

enum class ConnectionDirection
{
	Unset,
	Horizontal,
	Vertical,
	DiagonalLeft, // Top-bottom
	DiagonalRight // Top-bottom
};

class Connection
{
public:
	Connection() = delete;
	Connection(Node* node1, Node* node2, ConnectionDirection direction);
	~Connection();

	void Update();

private:
	Node* _node1 = nullptr;
	Node* _node2 = nullptr;
	ConnectionDirection _direction = ConnectionDirection::Unset;
};