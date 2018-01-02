#ifndef CIRCULAR_BUFFER_INDEX_HPP
#define CIRCULAR_BUFFER_INDEX_HPP
#include <iterator>


class CircularBufferIndex {
	public:


		class iterator: public std::iterator<
						std::input_iterator_tag,   // iterator_category
						int,                      // value_type
						int,                      // difference_type
						const int*,               // pointer
						int                       // reference
						>
		{
			int num;
			int size;
			public:
				explicit iterator(long _num, int _size) : num(_num), size(_size) {}
				iterator& operator++() {
					num++;
					if(num >= size) {
						num = 0;
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

				bool operator!=(iterator other) const {
					return !(*this == other);
				}

				reference operator*() const {
					return num;
				}
		};

		iterator begin() {return iterator(m_tail, m_size);}
		iterator end() {return iterator(m_head, m_size);}

		CircularBufferIndex(int size) {
			m_size = size;
			m_head = 0;
			m_tail = 0;
		}
		
		int push() {
			// if(full()) return -1;
			if(full()) {
				if(++m_tail >= m_size) {
					m_tail = 0;
				}
			}
			int t = m_head;
			if(++m_head >= m_size) {
				m_head = 0;
			}
			return t;
		}
		int peek() {
			return m_tail;
		}
		int pop() {
			if(empty()) return -1;
			int t = m_tail;
			if(++m_tail >= m_size) {
				m_tail = 0;
			}
			return t;
		}
		int size() {
			return m_size-1;
		}
		int space() {
			return m_head >= m_tail ? m_size-1 - (m_head - m_tail) : (m_tail - m_head) - 1;
		}
		bool empty() {
			return m_tail == m_head;
		}
		bool full() {
			int t = m_head + 1;
			if(t >= m_size) {
				t = 0;
			}
			return t == m_tail;
		}
		
	private:
		int m_size;
		int m_head;
		int m_tail;
};

#undef dbg

#endif
