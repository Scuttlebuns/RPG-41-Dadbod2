#include <memory>
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
		int size;
	public:
		CircleLinkedList() : head(nullptr), tail(nullptr), size(0) {}
		~CircleLinkedList() {
			clear();
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
				size--;
			}
		}

		void clear() {
			while (size > 0) {
				head = head->next;
				size--;
			}
			head = tail = nullptr;
		}

		bool empty() const {
			return size == 0;
		}
};

