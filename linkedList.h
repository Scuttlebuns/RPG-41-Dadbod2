#pragma once
#include <memory>
#include <iostream>
using namespace std;

template<typename T>
class CircleLinkedList {
	private:
		struct Node {
			T data;
			shared_ptr<Node> prev;
			shared_ptr<Node> next;

			Node(T val) : data(val), prev(nullptr), next(nullptr) {}

		};

		shared_ptr<Node> head;
		shared_ptr<Node> tail;
		shared_ptr<Node> current;
		int size;
	public:
		CircleLinkedList() : head(nullptr), tail(nullptr),current(nullptr), size(0) {}
		~CircleLinkedList() {
			clear();
		}

		T& at(shared_ptr<Node> node) {
			if (!node) {
				cerr << "Node doesn't exist" << endl;	
			}
			auto currNode = head;
			while (currNode != node && currNode != tail) {
				currNode = currNode->next;
			}
			if (currNode == node) {
				return currNode->data;
			}
			cerr << "Node not found in list" << endl;
		}
		
		shared_ptr<Node> getCurrent() const { return current; }
		shared_ptr<Node> getHead() const { return head; }
		shared_ptr<Node> getTail() const { return tail; }
		int getSize() const { return size; }

		void setCurrent(shared_ptr<Node> toChange, T new_data) {
			toChange->data = new_data;
		}

		void push_back(T val) {
			auto newNode = make_shared<Node>(val);
			if (size == 0) {
				head = tail = newNode;
				head->next = tail;
				tail->prev = head;
			}
			else {
				tail->next = newNode;
				newNode->prev = tail;
				newNode->next = head;
				head->prev = newNode;
				tail = newNode;
			}
			size++;
			current = newNode;
		}

		void remove(T val) {
			if (size == 0) {
				return;
			}

			auto currNode = head;
			while (currNode->data != val && currNode->next != head) {
				currNode = currNode->next;
			}
			if (currNode->data == val) {
				if (currNode == head) {
					head = head->next;
					tail->next = head;
					head->prev = tail;
				}
				else if (currNode == tail) {
					tail = tail->prev;
					head->prev = tail;
					tail->next = head;
				}
				else {
					currNode->prev->next = currNode->next;
					currNode->next->prev = currNode->prev;
				}
				if(currNode == current){
					current = current->next;
				}
				size--;
			}
		}

		void clear() {
			while (size > 0) {
				head = head->next;
				size--;
			}
			head = tail = current = nullptr;
		}

		bool empty() const {
			return size == 0;
		}
		bool contains(T dataSearch){
			shared_ptr<Node> curr = head;
			while (curr->next != head){
				cerr << *curr->data << endl;
				cerr << *dataSearch << endl;
				if (curr->data == dataSearch){
					return true;
				}
				curr = curr->next;
			}
			return false;
		}

};
