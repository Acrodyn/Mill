#pragma once

#include "raylib.h"
#include <vector>
#include <unordered_map>

class Node;

enum class ConnectionDirection
{
	Unset,
	Horizontal,
	Vertical,
	DiagonalLeft, // Top-bottom
	DiagonalRight // Top-bottom
};

struct ConnectionReport
{
	std::unordered_map<ConnectionDirection, int> Connections;
};

class Connection
{
public:
	Connection() = delete;
	Connection(Node* node1, Node* node2, ConnectionDirection direction);
	~Connection();

	void Update();
	ConnectionDirection GetDirection();

private:
	Node* _node1 = nullptr;
	Node* _node2 = nullptr;
	ConnectionDirection _direction = ConnectionDirection::Unset;
};