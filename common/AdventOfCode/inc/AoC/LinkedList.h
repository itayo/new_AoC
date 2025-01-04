#include <string>
#include <stdexcept>
#include <memory>
#include <iterator>
#include <unordered_set>

namespace AoC {

    template<typename tData>
    struct Node {
        tData data;
        std::unique_ptr<Node<tData>> next;

        explicit Node(tData val) : data(val), next(nullptr) {}
    };

    template<typename tData>
    class LinkedList {
    private:
        std::unique_ptr<Node<tData>> head;
        Node<tData>* tail;
        size_t _size;

    public:
        LinkedList() : head(nullptr), tail(nullptr), _size(0) {}


        LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), _size(0) {
            Node<tData>* current = other.head.get();
            while (current != nullptr) {
                push_back(current->data);
                current = current->next.get();
            }
        }

        LinkedList& operator=(const LinkedList& other) {
            if (this != &other) {
                while (head != nullptr) {
                    pop_front();
                }
                Node<tData>* current = other.head.get();
                while (current != nullptr) {
                    push_back(current->data);
                    current = current->next.get();
                }
            }
            return *this;
        }

        void push_front(const tData& val) {
            auto newNode = std::make_unique<Node<tData>>(val);
            newNode->next = std::move(head);
            head = std::move(newNode);
            if (tail == nullptr) {
                tail = head.get();
            }
            ++_size;
        }

        void push_back(const tData& val) {
            auto newNode = std::make_unique<Node<tData>>(val);
            if (tail != nullptr) {
                tail->next = std::move(newNode);
                tail = tail->next.get();
            } else {
                head = std::move(newNode);
                tail = head.get();
            }
            ++_size;
        }

        [[nodiscard]] std::string ToString(char separator = ',') const {
            Node<tData>* temp = head.get();
            std::string result;

            while (temp != nullptr) {
                result += std::to_string(temp->data);
                if (temp->next != nullptr) {
                    result += separator;
                }
                temp = temp->next.get();
            }
            return result;
        }

        void pop_front() {
            if (head == nullptr) return;
            head = std::move(head->next);
            if (head == nullptr) {
                tail = nullptr;
            }
            --_size;
        }

        void pop_back() {
            if (!head) return;

            if (head.get() == tail) {
                head.reset();
                tail = nullptr;
            } else {
                Node<tData>* temp = head.get();
                while (temp->next.get() != tail) {
                    temp = temp->next.get();
                }
                temp->next.reset();
                tail = temp;
            }
            --_size;
        }

        void insert(int pos, const tData& val) {
            if (pos < 0 || pos > _size) {
                throw std::out_of_range("Invalid position");
            }
            auto newNode = std::make_unique<Node<tData>>(val);
            if (pos == 0) {
                newNode->next = std::move(head);
                head = std::move(newNode);
                if (tail == nullptr) {
                    tail = head.get();
                }
            } else {
                Node<tData>* temp = head.get();
                for (int i = 0; i < pos - 1; ++i) {
                    temp = temp->next.get();
                }
                newNode->next = std::move(temp->next);
                temp->next = std::move(newNode);
                if (temp->next == nullptr) {
                    tail = temp;
                }
            }
            ++_size;
        }

        [[nodiscard]] size_t size() const { return _size; }

        ~LinkedList() {
            while (head != nullptr) {
                pop_front();
            }
        }

        class Iterator {
        private:
            Node<tData>* current;

        public:
            explicit Iterator(Node<tData>* node) : current(node) {}

            tData& operator*() { return current->data; }
            Iterator& operator++() {
                current = current->next.get();
                return *this;
            }
            bool operator!=(const Iterator& other) const {
                return current != other.current;
            }
        };
        void sort() {
            if (head == nullptr || head->next == nullptr) return;

            bool swapped;
            do {
                swapped = false;
                Node<tData>* temp = head.get();
                while (temp->next != nullptr) {
                    if (temp->data > temp->next->data) {
                        std::swap(temp->data, temp->next->data);
                        swapped = true;
                    }
                    temp = temp->next.get();
                }
            } while (swapped);
        }

        void removeDuplicates() {
            Node<tData>* current = head.get();
            while (current != nullptr) {
                Node<tData>* prev = current;
                Node<tData>* temp = current->next.get();
                while (temp != nullptr) {
                    if (current->data == temp->data) {
                        prev->next = std::move(temp->next);
                        if (temp == tail) {
                            tail = prev;
                        }
                        --_size;
                        temp = prev->next.get();
                    } else {
                        prev = temp;
                        temp = temp->next.get();
                    }
                }
                current = current->next.get();
            }
        }

        bool contains(const tData& val) const {
            Node<tData>* temp = head.get();
            while (temp != nullptr) {
                if (temp->data == val) {
                    return true;
                }
                temp = temp->next.get();
            }
            return false;
        }

        Node<tData>* find(const tData& val) const {
            Node<tData>* temp = head.get();
            while (temp != nullptr) {
                if (temp->data == val) {
                    return temp;
                }
                temp = temp->next.get();
            }
            return nullptr;
        }

        void clear() {
            while (head != nullptr) {
                pop_front();
            }
        }

        void reverse() {
            if(head == nullptr && tail == nullptr) return;
            LinkedList<tData> n;
            while(_size > 0) {
                n.push_back(tail->data);
                pop_back();
            }
            std::swap(head,n.head);
            std::swap(tail,n.tail);
        }

        void unique() {
            if (head == nullptr) return;
            std::unordered_set<tData> seen;
            Node<tData>* current = head.get();
            Node<tData>* prev = nullptr;
            while (current != nullptr) {
                if (seen.count(current->data)) {
                    prev->next = std::move(current->next);
                    --_size;
                    if (current == tail) {
                        tail = prev;
                    }
                    current = prev->next.get();
                } else {
                    seen.insert(current->data);
                    prev = current;
                    current = current->next.get();
                }
            }
        }


        tData getAt(int pos) const {
            if (pos < 0 || pos >= _size) {
                throw std::out_of_range("Position out of range");
            }
            Node<tData>* temp = head.get();
            for (int i = 0; i < pos; ++i) {
                temp = temp->next.get();
            }
            return temp->data;
        }

        void erase(int pos) {
            if (pos < 0 || pos >= _size) {
                throw std::out_of_range("Position out of range");
            }
            if (pos == 0) {
                pop_front();
            } else {
                Node<tData>* temp = head.get();
                for (int i = 0; i < pos - 1; ++i) {
                    temp = temp->next.get();
                }
                temp->next = std::move(temp->next->next);
                if (temp->next == nullptr) {
                    tail = temp;
                }
                --_size;
            }
        }

        tData& operator[](int pos) {
            if (pos < 0 || pos >= _size) {
                throw std::out_of_range("Position out of range");
            }
            Node<tData>* temp = head.get();
            for (int i = 0; i < pos; ++i) {
                temp = temp->next.get();
            }
            return temp->data;
        }

        std::vector<tData> toVector() const {
            std::vector<tData> vec;
            Node<tData>* temp = head.get();
            while (temp != nullptr) {
                vec.push_back(temp->data);
                temp = temp->next.get();
            }
            return vec;
        }

        friend std::ostream& operator<<(std::ostream& os, const LinkedList<tData>& list) {
            os << list.ToString();
            return os;
        }

        Iterator begin() { return Iterator(head.get()); }
        Iterator end() { return Iterator(nullptr); }
    };
}