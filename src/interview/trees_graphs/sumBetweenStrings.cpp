/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

struct Node {

	const std::string key;
	int value;
	int sum;
	Node* parent;
	Node* left;
	Node* right;

	Node(const std::string& key, int value, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
	: key(key), value(value), sum(value), parent(parent), left(left), right(right) {}
};


bool insert(Node* root, const std::string& key, int value) {

	if(!root) {
		return false;
	}

	bool result = false;
	if(key <= root->key) {
		if(root->left) {
			result = insert(root->left, key, value);
		} else {
			root->left = new Node(key, value, root);
			result = true;
		}
	} else {
		if(root->right) {
			result = insert(root->right, key, value);
		} else {
			root->right = new Node(key, value, root);
			result = true;
		}
	}
	if(result) {
		root->sum += value;
	}
	return result;
}

Node* find(Node* root, const std::string& key) {
	if(!root) {
		return nullptr;
	}

	if(key == root->key) {
		return root;
	}
	if(key < root->key) {
		return find(root->left, key);
	}
	return find(root->right, key);
}


Node* lowestCommonAncestorHelper(Node* root, const std::string& key1, const std::string& key2) {
	if(!root) {
		return nullptr;
	}

	if(key1 < root->key && key2 < root->key) {
		return lowestCommonAncestorHelper(root->left, key1, key2);
	}

	if(key1 > root->key && key2 > root->key) {
		return lowestCommonAncestorHelper(root->right, key1, key2);
	}

	if(find(root, key1) && find(root, key2)) {
		return root;
	}

	return nullptr;
}

Node* lowestCommonAncestor(Node* root, const std::string& key1, const std::string& key2) {

	if(key1 == key2) {
		return find(root, key1);
	}
	return lowestCommonAncestorHelper(root, key1, key2);
}

int prefixSum(Node* root, Node* node) {
	int sum = node->value;
	if(node->left) {
		sum += node->left->sum;
	}

	Node* current = node;
	while(current && current != root) {
		current = current->parent;
		if(current->key < node->key) {
			sum += current->value;
			if(current->left) {
				sum += current->left->sum;
			}
		}
	}
	return sum;
}

int sumBetweenStrings(Node* root, std::string str1, std::string str2) {

	if(str1 > str2) {
		std::swap(str1, str2);
	}

	Node* smaller = find(root, str1);
	Node* greater = find(root, str2);

	LOG(ERROR) << prefixSum(root, smaller);
	LOG(ERROR) << prefixSum(root, greater);

	return prefixSum(root, greater) - prefixSum(root, smaller) - greater->value;
}


struct SumBetweenStringsTest : public testing::Test {

	static void printNode(Node* node) {
		std::cout << node->key << "=(" << node->value << "," << node->sum << ")";
	}
};


TEST_F(SumBetweenStringsTest, SomeTest) {

	Node* testTree = new Node("L", 0);

	insert(testTree, "H", 1);
	insert(testTree, "C", 4);
	insert(testTree, "K", 3);
	insert(testTree, "A", 1);
	insert(testTree, "D", 2);
	insert(testTree, "J", -1);
	insert(testTree, "P", 7);
	insert(testTree, "N", 1);
	insert(testTree, "T", 4);
	insert(testTree, "M", -1);
	insert(testTree, "O", -2);


	Utils::printTree(testTree, SumBetweenStringsTest::printNode);

	ASSERT_EQ(sumBetweenStrings(testTree, "L", "L"), 0);
	ASSERT_EQ(sumBetweenStrings(testTree, "H", "P"), 0);
	ASSERT_EQ(sumBetweenStrings(testTree, "A", "T"), 14);
	ASSERT_EQ(sumBetweenStrings(testTree, "D", "T"), 8);
	ASSERT_EQ(sumBetweenStrings(testTree, "A", "M"), 9);
	ASSERT_EQ(sumBetweenStrings(testTree, "D", "M"), 3);
	ASSERT_EQ(sumBetweenStrings(testTree, "A", "O"), 9);
}
