#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* node = new Node(value);
    if (front_ == nullptr){
      front_ = node;
    } else {
      back_->next = node;
    }
    back_ = node;
    size_ += 1;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index < 0 or index > size_){
      return false;
    }
    Node* node = new Node(value);
    if (index == 0){
      if (front_ != nullptr) {
        node->next = front_;
      } else {
        back_ = node;
      }
      front_ = node;
    } else if (index == size_){
      back_->next = node;
      back_ = node;
    } else {
      Node* prev_node = FindNode(index - 1);
      node->next = prev_node->next;
      prev_node->next = node;
    }
    size_ += 1;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    return false;
    if (index < 0 or index >= size_) {
      return false;
    }
    Node *curr = front_;
    for (int i = 0; i < index; i++){
      curr = curr->next;
    }
    curr->value = new_value;
    return true;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index < 0 or index >= size_){
      return std::nullopt;
    }
    if (index == 0){
      if (front_ == nullptr){
        return std::nullopt;
      }
      auto val = front_->value;
      front_ = front_->next;
      size_ -= 1;
      return val;
    }
    Node* prev = FindNode(index - 1);
    auto val = prev->next->value;
    prev->next = prev->next->next;
    size_ -= 1;
    return val;
  }

  void LinkedList::Clear() {
    for (Node* curr = front_; curr != nullptr; /* */) {
      Node* node_to_remove = curr;
      curr = curr->next;
      delete node_to_remove;
    }
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index >= size_ or index < 0) {
      return std::nullopt;
    }
    Node* curr = front_;
    for (int i = 0; i < index; i++){
      curr = curr->next;
    }
    return curr->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* curr = front_;
    int index = 0;
    while(curr != nullptr){
      if (curr->value != value){
        curr = curr->next;
      } else {
        return index;
      }
      index += 1;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node* curr = front_;
    while(curr != nullptr){
      if (curr->value != value) {
        curr = curr->next;
      } else {
        return true;
      }
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr){
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr){
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index >= size_ or index < 0){
      return nullptr;
    }
    Node* curr = front_;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment