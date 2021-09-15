#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "iterator.hpp"
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iterator>
#include "utils.hpp"
#include "enable_if.hpp"

namespace ft
{
template <class T>
class vector_iterator //: public iterator<T>
{
	public:
		typedef T												iterator_type;
		typedef typename iterator_traits<T>::difference_type	difference_type;
		typedef typename iterator_traits<T>::value_type			value_type;
		typedef typename iterator_traits<T>::reference			reference;
		typedef typename iterator_traits<T>::pointer			pointer;
		typedef random_access_iterator_tag						iterator_category; //or another tag

		explicit	vector_iterator(): _ptr(NULL) {};
		explicit	vector_iterator(iterator_type ptr): _ptr(ptr) {};
		template<class U>
		vector_iterator(const vector_iterator<U>& vect): _ptr(vect.base()) { *this = vect; } 
		~vector_iterator() {}

		reference operator*() const { return *_ptr; }
		pointer operator->() const { return _ptr; }

		vector_iterator& operator++() {
			++_ptr;
			return *this;
		}
		vector_iterator operator++(int) {
			vector_iterator tmp = *this;
			++_ptr;
			return *this;
		}
		vector_iterator& operator--() {
			--_ptr;
			return *this;
		}
		vector_iterator operator--(int) {
			vector_iterator tmp = *this;
			--_ptr;
			return *this;
		}

		vector_iterator operator-(difference_type n) {
			return vector_iterator(_ptr - n);
		}
		vector_iterator operator-=(difference_type n) {
			_ptr -= n;
			return _ptr;
		}
		vector_iterator operator+(difference_type n) {
			return vector_iterator(_ptr + n);
		}
		vector_iterator operator+=(difference_type n) {
			_ptr += n;
			return _ptr;
		}

		reference operator[](size_t i) {
			return (*(_ptr + i));
		}

		template <class K>
		vector_iterator&	operator=(const vector_iterator<K> & other) {
			_ptr = other.base();
			return *this;
		}

		pointer		base() const { return _ptr; }
	private:
		pointer		_ptr;
};

template <class T, class U>
std::ptrdiff_t operator-(const vector_iterator<T>& left, const vector_iterator<U>& right) { return (left.base() - right.base()); }
template <class T, class U>
std::ptrdiff_t operator+(const vector_iterator<T>& left, const vector_iterator<U>& right) { return (left.base() + right.base()); }
template <class T, class U>
vector_iterator<U> operator+(T left, const vector_iterator<U>& right) { return left + right; }
template <class T, class U>
bool operator== (const vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() == right.base()); }
template <class T, class U>
bool operator!= (const vector_iterator<T>& left,const vector_iterator<U>& right) { return !(left == right); }
template <class T, class U>
bool operator< (const vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() < right.base()); }
template <class T, class U>
bool operator<= (const vector_iterator<T>& left,const vector_iterator<U>& right) { return left.base() <= right.base(); }
template <class T, class U>
bool operator> (const vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() > right.base()); }
template <class T, class U>
bool operator>= (const vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() >= right.base()); }

template <class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef T									value_type;
	typedef Alloc								allocator_type;

	typedef typename Alloc::reference			reference;
	typedef typename Alloc::const_reference		const_reference;
	typedef typename Alloc::pointer				pointer;
	typedef typename Alloc::const_pointer		const_pointer;
	typedef typename Alloc::difference_type 	difference_type;
    typedef typename Alloc::size_type 			size_type;
	//typedef std::ptrdiff_t						difference_type;
	//typedef size_t								size_type;

	typedef vector_iterator<pointer>					iterator;
	// typedef std::reverse_iterator<iterator>				reverse_iterator; //da correggere
	typedef iterator			reverse_iterator; //da correggere
	typedef vector_iterator<const_pointer>				const_iterator;
	// typedef std::reverse_iterator<const_iterator>		const_reverse_iterator; //da correggere
	typedef const_iterator		const_reverse_iterator; //da correggere

	// (con|des)tructors
	explicit vector (const allocator_type& alloc = allocator_type()):
					_alloc(alloc),
					_vector(NULL),
					_size(0),
					_capacity(0)
	{};
	explicit vector (unsigned int n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()):
					_alloc(alloc),
					_size(n),
					_capacity(n)
	{
		/*_vector = _alloc.allocate(n);
		for (size_t i = 0; i < n; i++) {
			_vector[i] = val;
		}*/
					    if (n)
				    _vector = _alloc.allocate(n);
				while (n--)
					_alloc.construct(_vector + n, val);
	};

	template <class inputType>
	vector (inputType first, inputType last,
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<inputType>::value, inputType >::type* = 0 ): // change to FT
			_alloc(alloc)
	{
		_size = (last - first) /*/ sizeof(inputType)*/;
		_capacity = _size;
		_vector = _alloc.allocate(_size);
	};
	vector (const vector& x):
		_vector(NULL),
		_size(0),
		_capacity(0)
	{
		*this = x;
	};
	~vector() {
		//_alloc.deallocate(_vector, _capacity);
	};

	// iterators
	iterator begin() const {
		return(iterator(_vector));
	};
	iterator end() const {
		return(iterator(_vector + _size));
	};
	reverse_iterator rbegin() const {
		return(reverse_iterator(end()));
	};
	reverse_iterator rend() const {
		return(reverse_iterator(begin()));
	};

	// capacity

	size_type size() const {
		return(_size);
	};

	size_type max_size() const{
		return(_alloc.max_size());
	};

	void resize (size_type n, value_type val = value_type()) {
		
		if(n < _size)
		{
			_size = n;
			/*
			pointer temp = _alloc.allocate(n * 2);
			for (unsigned int i = 0; i < n; i++)
				temp[i] = _vector[i];
			_alloc.deallocate(_vector, _capacity);
			_vector = temp;
			_capacity = n * 2;
			*/
		}
		else if (n > _capacity)
		{
			pointer temp = _alloc.allocate(n * 2);
			int i = -1;
			while((unsigned int)++i <= _size)
				temp[i] = _vector[i];
			while((unsigned int)++i < n * 2)
				temp[i] = val;
			_alloc.deallocate(_vector, _capacity);
			_vector = temp;
			_size = n;
			_capacity = n * 2;
		}
	};

	size_type capacity() const{
		return(_capacity);
	};

	bool empty() const{
		return(_size == 0 ? true : false);
	};

	void reserve (size_type n){
		if(n > _capacity)
		{
			pointer tmp = _alloc.allocate(n * 2);
			for(unsigned int i = 0; i < _size; i++)
				tmp[i] = _vector[i];
			_alloc.deallocate(_vector, _capacity);
			_vector = tmp;
			_capacity = n * 2;
		}
	};
/*
	void shrink_to_fit(){
		if(_capacity > _size)
		{
			pointer tmp = _alloc.allocate(_size);
			for(int i = 0; i < _size; i++)
				tmp[i] = _vector[i];
			_alloc.deallocate(_vector);
			_vector = tmp;
			_capacity = _size;
		}
	};
*/
	// access
	vector& operator= (const vector& alt) {
		_alloc.deallocate(_vector, _size);
		_size = alt.size();
		_capacity = _size;
		_vector = _alloc.allocate(_size);
		for (size_t i = 0; i < _size; i++)
			_vector[i] = alt[i];
		return *this;
	}

	reference operator[] (size_type n) {
		return(*(_vector + n));
	};

	const_reference operator[] (size_type n) const {
		return(*(_vector + n));
	};

	reference at (size_type n) {
		return(*(_vector + n));
	};

	const_reference at (size_type n) const {
		return(*(_vector + n));
	};

	reference front() {
		return(*_vector);
	};
	
	const_reference front() const {
		return(_vector);
	};

	reference back() {
		return(*(_vector + _size));
	};

	const_reference back() const {
		return(*(_vector + _size));
	};
	
	// modifiers
	/*
	template <class InputIterator>
        void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type& u);
    void assign(initializer_list<value_type> il);
	*/
	template <class InputIterator>
	void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
		clear();
		_size = last - first;
		_vector = _alloc.allocate(_size);
		_capacity = _size;
		for (size_t i = 0; first + i < last; i++)
			_vector[i] = *(first + i);
	};
	
	void assign (size_type n, const value_type& val) {
		clear();
		_size = n;
		_capacity = n;
		_vector = _alloc.allocate(n);
		for (size_t i = 0; i < n; i++)
			_vector[i] = val;
	};

	void push_back (const value_type& val) {
		if (_size == _capacity) {
			if (!_capacity)
				_capacity = 1;
			pointer tmp = _alloc.allocate(_capacity*2);
			_capacity *= 2;
			for (size_t i = 0; i < _size; i++)
				tmp[i] = _vector[i];
			_alloc.deallocate(_vector, _size);
			_vector = tmp;
		}
		_vector[_size] = val;
		_size++;
	};

	void pop_back() {
		_size--;
	}

	iterator erase (iterator position){
		_size--;
		for (size_t i = 0; position + i + 1 != end(); i++)
			*(position + i) = *(position + i + 1);
		return position;
	};

	iterator erase (iterator first, iterator last){
		// size_type distance = std::distance(first, last);
		size_type distance = last - first;
		for (size_t i = 0; first + i + distance != end(); i++)
			*(first + i) = *(first + i + distance);
		_size -= distance;
		return first;
	};

	void swap (vector& x) {
		std::swap(_vector, x._vector);
		std::swap(_size, x._size);
		std::swap(_capacity, x._capacity);
	};

	iterator insert (iterator position, const value_type& val) {
		(void)val;
		return position;
	};

    void insert (iterator position, size_type n, const value_type& val){
		size_type index = std::distance(begin(), position);
		resize(_size + n);
		for(size_t i = _size - 1; i >= index; i--)
			_vector[i] = _vector[i - n];
		for (size_t i = 0; i < n; i++)
			_vector[index + i] = val;
	};

	template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last) {
		// size_type dist = std::distance(first, last);
		// size_type index = std::distance(begin(), position);
		size_type dist = last - first;
		size_type index = position - begin();
		resize(_size + dist);
		for(size_t i = _size - 1; i >= index; i--)
			_vector[i] = _vector[i - dist];
		for (size_t i = 0; i < dist; i++)
			_vector[index + i] = *(first + i);
	};

	void clear() {
		_alloc.deallocate(_vector, _capacity);
		_size = 0;
		_capacity = 0;
		_vector = NULL;
	};
	// allocator

	allocator_type get_allocator() const {
		return(_alloc);
	};
private:
	allocator_type	_alloc;
protected:
	pointer			_vector;
	size_type		_size;
	size_type		_capacity;
}; //end vector class



//non member function operators

template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	if(lhs.size() != rhs.size())
		return(false);
	for (size_t i = 0; i < lhs.size(); i++)
		if(lhs[i] != rhs[i])
			return(false);
	return(true);
};
	
template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return(!(lhs == rhs));
};
	
template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return(lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
};

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return(!(lhs > rhs));
};
	
template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return(lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
};

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return(!(lhs < rhs));
};

} // namespace ft
#endif /* VECTOR_HPP */
