/**
* @Author: Thomas Scholtz <thomas>
* @Date:   2016-11-06T22:39:40+02:00
* @Email:  thomas@quantum-sicarius.za.net
* @Last modified by:   thomas
* @Last modified time: 2016-12-07T19:16:40+02:00
* @License: Attribution-NonCommercial-ShareAlike 4.0 International
*/

#include "../libs/listAsSLL.hpp"

void ListAsSLL::shrinkList() {
  // If list empty just return.
  if (this->head == nullptr) {
    return;
  }

  auto last_Node = this->head.get();
  auto prev_Node = last_Node;

  // Traverse entire list to the end.
  while (last_Node->next != nullptr) {
    // Save the previous node.
    prev_Node = last_Node;
    last_Node = last_Node->next.get();
  }

  prev_Node->next.reset();
  if (prev_Node == this->head.get()) {
    this->head.reset();
  }

  if (this->listSize != 0) {
    --this->listSize;
  }
}

int ListAsSLL::compareTo(Object const &) const { return 0; }

ListAsSLL::ListAsSLL() {
  this->head = nullptr;
  this->listSize = 0;
}

ListAsSLL::~ListAsSLL() {
  this->head.reset();
  this->listSize = 0;
}

void ListAsSLL::insert(std::shared_ptr<Object> o) {
  auto last_Node = this->head.get();

  // Traverse entire list to the end.
  while (last_Node && last_Node->next != nullptr) {
    last_Node = last_Node->next.get();
  }

  if (this->head == nullptr) {
    this->head.reset(new Node(o, nullptr));
  } else {
    last_Node->next.reset(new Node(o, nullptr));
  }
  ++this->listSize;
}

void ListAsSLL::remove(std::shared_ptr<Object> o) {
  // If list empty just return.
  if (this->head == nullptr) {
    return;
  }

  auto current_Node = this->head.get();
  auto prev_Node = current_Node;
  bool found = false;

  if (current_Node->value == o) {
    found = true;
  }

  // Traverse till we find the object;
  while (current_Node->next != nullptr) {
    // If found exit loop.
    if (current_Node->value == o) {
      found = true;
      break;
    }

    prev_Node = current_Node;
    current_Node = current_Node->next.get();
  }

  if (!found) {
    return;
  }

  // If the current node is the head we must repoint the head.
  if (current_Node == this->head.get()) {
    this->head = std::move(current_Node->next);
  }

  // Fix pointers.
  if (prev_Node != nullptr) {
    prev_Node->next = std::move(current_Node->next);
  }

  // Delete current_Node.
  // current_Node.reset();

  if (this->listSize != 0) {
    --this->listSize;
  }
}

void ListAsSLL::grow(int amount = 1) {
  for (size_t i = 0; i < amount; i++) {
    this->insert(std::make_unique<NullObject>(NullObject()));
  }
}

void ListAsSLL::shrink(int amount = 1) {
  for (size_t i = 0; i < amount; i++) {
    this->shrinkList();
  }
}

int ListAsSLL::size() { return this->listSize; }

std::shared_ptr<Object> &ListAsSLL::operator[](int i) {
  if (i < 0) {
    throw "Out of bounds!";
  }

  int start = 0;
  auto current_Node = this->head.get();

  while (start != i && start <= this->listSize &&
         current_Node->next != nullptr) {
    current_Node = current_Node->next.get();
    start++;
  }

  if (start == i && current_Node) {
    return current_Node->value;
  } else {
    throw "Node not found!";
  }
}

void ListAsSLL::print(std::ostream &o) const {}
