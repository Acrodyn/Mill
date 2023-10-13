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

class Connection
{
public:
	Connection() = delete;
	Connection(Node* node1, Node* node2, ConnectionDirection direction);
	~Connection();

	void Update();
	ConnectionDirection GetDirection();
	void SetAsMarked(bool isMarked = true);

private:
	const Node* const _node1 = nullptr;
	const Node* const _node2 = nullptr;
	const ConnectionDirection _direction;

	bool _isMarked = false;
};

struct ConnectionReport
{
	std::unordered_map<ConnectionDirection, std::vector<Connection*>> Connections;
};