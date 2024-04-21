#pragma once

#include <vector>
#include <optional>

template <class T>
class List {
	struct Node {
		T value;
		Node* next;
	};

	struct Iterator {
		friend class List<T>;
	private:
		mutable Node* current_;
	public:
		using value_type = T;

		explicit Iterator(Node* node) : current_{ node }
		{}

		void operator++() const
		{
			current_ = current_->next;
		}

		void operator++(int) const
		{
			current_ = current_->next;
		}

		const bool operator==(const Iterator& lhs) const
		{
			return current_ == lhs.current_;
		}

		const bool operator!=(const Iterator& lhs) const
		{
			return !(operator==(lhs));
		}

		value_type& operator*()
		{
			return current_->value;
		}

		const value_type& operator*() const {
			return current_->value;
		}
	};

	void AppendFrontNode(Node* new_node)
	{
		if (!head_) {
			head_ = new_node;
		}
		else {
			new_node->next = head_;

			head_ = new_node;
		}
	}

	Node* FindNode(const T& value)
	{
		Node* current = head_;

		while (current != nullptr) {
			if (current->value == value) return current;

			current = current->next;
		}

		return current;
	}

	void PopFrontNode()
	{
		if (head_) {
			Node* current = head_;

			head_ = current->next;

			delete current;
		}
	}

	Node* head_;
public:
	List() : head_(nullptr) {}

	List(const List<T>& rhs)
		: head_(nullptr)
	{
		std::vector<Node*> nodes;

		for (Node* current = rhs.head_; current != nullptr; current = current->next) {
			nodes.push_back(current);
		}

		auto iter = std::rbegin(nodes);
		auto end = std::rend(nodes);

		while (iter != end) {
			PushFront((*iter)->value);

			iter++;
		}
	}

	List(List<T>&& rhs) noexcept
		: head_(std::move(rhs.head_))
	{
		rhs.head_ = nullptr;
	}

	List(std::initializer_list<T> values)
		: head_(nullptr)
	{
		auto iter = std::rbegin(values);
		auto end = std::rend(values);

		while (iter != end) {
			PushFront(*iter);

			iter++;
		}
	}

	using iterator = Iterator;
	using const_iterator = const iterator;
	using value_type = T;

	iterator begin()
	{
		return Iterator{ head_ };
	}

	iterator end()
	{
		return Iterator{ nullptr };
	}

	const_iterator begin() const {
		return Iterator{ head_ };
	}

	const_iterator end() const {
		return Iterator{ nullptr };
	}

	void PushFront(T&& value)
	{
		Node* new_node = new Node{ std::move(value), nullptr };

		AppendFrontNode(new_node);
	}

	void PushFront(const T& value)
	{
		Node* new_node = new Node{ value, nullptr };

		AppendFrontNode(new_node);
	}

	bool Empty()
	{
		return head_ == nullptr;
	}

	T& Front()
	{
		return head_->value;
	}

	std::optional<T> PopFront()
	{
		if (Empty()) return std::nullopt;

		std::optional<T> value(std::move(Front()));

		PopFrontNode();

		return value;
	}

	iterator Find(const T& value)
	{
		return iterator{ FindNode(value) };
	}

	const_iterator Find(const T& value) const
	{
		return const_iterator{ FindNode(value) };
	}

	bool Erase(const T& value)
	{
		if (head_ == nullptr) return false;

		Node* current = head_;

		if (head_->value == value) {
			head_ = head_->next;

			delete current;

			return true;
		}

		while (current->next != nullptr) {
			if (current->next->value == value) {
				Node* next_next = current->next->next;

				delete current->next;
				current->next = next_next;

				return true;
			}
			current = current->next;
		}

		return false;
	}

	void InsertAfter(const_iterator position, T&& value)
	{
		Node* new_node = new Node{ std::forward<T>(value), position.current_->next };

		position.current_->next = new_node;
	}
};