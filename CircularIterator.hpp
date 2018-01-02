#ifndef CIRCULAR_ITERATOR_HPP
#define CIRCULAR_ITERATOR_HPP
#include <iterator>

// #define DEBUG
#ifdef DEBUG
#define dbg(x) x
#include <iostream>
#else
#define dbg(x)
#endif
template <typename T>
class CircularIterator {
	public:

		using value_type = typename T::value_type;
		class iterator: public std::iterator<
						std::random_access_iterator_tag, // iterator_category
						typename T::value_type, // value_type
						int, // difference_type
						const typename T::value_type*, // pointer
						typename T::value_type  // reference
					>
		{
			private:
				T* obj;
				int num;
				int size;
				int head;
				
			public:
				using difference_type = typename std::iterator<std::random_access_iterator_tag, value_type, int, const value_type*, value_type&>::difference_type;
				using reference = typename std::iterator<std::random_access_iterator_tag, value_type, int, const value_type*, value_type&>::reference;
						
				explicit iterator(T* _obj, int _num, int _head) : obj(_obj), num(_num), size(_obj->size()), head(_head) {}
				
				iterator& operator++() {
					num++;
					if(num >= size) {
						num = 0;
					}
					return *this;
				}
				
				iterator& operator--() {
					num--;
					if(num < 0) {
						num = size-1;
					}
					return *this;
				}
				
				iterator operator++(int) {
					iterator retval = *this; 
					++(*this);
					return retval;
				}
				
				bool operator==(iterator other) const {
					return num == other.num;
				}
				
				bool operator<(iterator other) const {
					return !(num < head && other.num > head);
				}

				bool operator!=(iterator other) const {
					return num != other.num;
				}
				
				iterator operator+(int n) const {
					dbg(std::cout << "operator+: " << n << "\n";)
					return iterator(obj, num+n % size, head);
				}
				
				iterator operator-(int n) const {
					dbg(std::cout << "operator+: " << n << "\n";)
					return iterator(obj, normalize(num-n), head);
				}
				
				inline int normalize(int n) const {
					if(n < 0) {
						return (n % size) + n;
					} else {
						return n % size;
					}
				}
				
				difference_type operator-(iterator it) const {
					dbg(std::cout << "operator-: " << num << " - " << it.num << "\n";)
					if(num < it.num) {
						// dbg(std::cout << "\toperator-: " << size << " - " << it.num << " + " << num << "\n";)
						return size - it.num + num;
					} else if(num > it.num) {
						return num - it.num;
					} else {
						return 0;
					}
				}
				
				iterator& operator+=(int n) {
					dbg(std::cout << "operator+=: " << num << " + " << n << "\n";)
					num+=n;
					if(num >= size) {
						num = num % size;
					}
					return *this;
				}

				reference operator*() const {
					dbg(std::cout << "operator*: " << num << "\n";)
					return obj->operator[](num);
				}
				
				int GetIndex() {
					return num;
				}
		};

		iterator begin() {
			return iterator(m_obj, m_tail, m_head);
		}
		iterator end() {
			return iterator(m_obj, m_head, m_head);
		}

		CircularIterator(T& obj, int tail, int head) {
			m_obj = &obj;
			m_size = obj.size();
			m_tail = tail;
			m_head = head;
		}
		
	private:
		T* m_obj;
		int m_size;
		int m_head;
		int m_tail;
};

template<typename C>
CircularIterator<C> make_circular_iterator(C &container, int tail, int head) {
	return CircularIterator<C>(container, tail, head);
}

#undef dbg

#endif
