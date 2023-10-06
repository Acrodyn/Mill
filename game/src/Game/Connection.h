#pragma once

#include "raylib.h"
#include <vector>

class Node;

class Connection
{
public:
	Connection() = delete;
	Connection(Node* node1, Node* node2);
	~Connection();

	void Update();

private:
	Node* _node1 = nullptr;
	Node* _node2 = nullptr;
};