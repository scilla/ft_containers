#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "iterator.hpp"
#include <functional>
#include <iostream>
#include <limits>
#include <utility>
#include <memory>
#include <string>
#include "utils.hpp"
#include "enable_if.hpp"
#include <stdio.h>
#include <vector>
#include <string.h>

namespace ft
{
template <class T>
class vector_iterator
{
	public:
		typedef T												iterator_type;
		typedef typename iterator_traits<T>::difference_type	difference_type;
		typedef typename iterator_traits<T>::value_type			value_type;
		typedef typename iterator_traits<T>::reference			reference;
		typedef typename iterator_traits<T>::pointer			pointer;
		typedef random_access_iterator_tag						iterator_category;

		explicit	vector_iterator(): _ptr(NULL) {};
		explicit	vector_iterator(iterator_type ptr): _ptr(ptr) {};
		template<class U>
		vector_iterator(const vector_iterator<U>& vect) { *this = vect; }
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
			return tmp;
		}
		vector_iterator& operator--() {
			--_ptr;
			return *this;
		}
		vector_iterator operator--(int) {
			vector_iterator tmp = *this;
			--_ptr;
			return tmp;
		}

		vector_iterator operator-(difference_type n) const {
			return vector_iterator(_ptr - n);
		}
		vector_iterator operator-=(difference_type n) {
			_ptr -= n;
			return vector_iterator(_ptr);
		}
		vector_iterator operator+(difference_type n) const {
			return vector_iterator(_ptr + n);
		}
		vector_iterator operator+=(difference_type n) {
			_ptr += n;
			return vector_iterator(_ptr);
		}

		reference operator[](size_t i) {
			return reference(*(_ptr + i));
		}

		template <class K>
		vector_iterator&	operator=(vector_iterator<K> const& other) const{
			_ptr = static_cast<pointer>(other.base());
			return *this;
		}

		template <class K>
		vector_iterator&	operator=(vector_iterator<K> const& other) {
			_ptr = static_cast<pointer>(other.base());
			return *this;
		}


		pointer		base() { return _ptr; }
		const pointer		base() const { return _ptr; }
	private:
		pointer		_ptr;
};

template <class T, class U>
std::ptrdiff_t operator-(const vector_iterator<T>& left, const vector_iterator<U>& right) { return (left.base() - right.base()); }
template <class T, class U>
std::ptrdiff_t operator+(const vector_iterator<T>& left, const vector_iterator<U>& right) { return (left.base() + right.base()); }
template <class T, class U>
vector_iterator<U> operator+(T left, const vector_iterator<U>& right) { 
	vector_iterator<U> it = right;
	for(T i = 0; i < left; i++)
		it++;
	return it; }
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

	typedef vector_iterator<pointer>				iterator;
	typedef vector_iterator<const_pointer>			const_iterator;
	typedef reverse_iterator<const_iterator>		const_reverse_iterator; //da correggere
	typedef reverse_iterator<iterator>				reverse_iterator; //da correggere

	class out_of_range: public std::out_of_range {
	public:
		explicit out_of_range(std::string str): std::out_of_range(str) {}
	};

	// (con|des)tructors
	explicit vector (const allocator_type& alloc = allocator_type()):
					_alloc(alloc),
					_vector(NULL),
					_size(0),
					_capacity(0)
	{
		reserve(10);
	};
	explicit vector (unsigned int n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()):
					_alloc(alloc),
					_size(n),
					_capacity(n)
	{
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
		//_size = last - first /*/ sizeof(inputType)*/;
		size_t i = 0;
		for(inputType it = first; it != last; it++)
			i++;
		_size = i;
		_capacity = _size;
		_vector = _alloc.allocate(_size);
		for (size_t i = 0; i < _size; i++)
		{
			_vector[i] = *first;
			first++;
		}
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
	iterator begin() {
		return(iterator(_vector));
	};

	const_iterator begin() const {
		return(const_iterator(_vector));
	};

	iterator end() {
		return(iterator(_vector + _size));
	};

	const_iterator end() const {
		return(const_iterator(_vector + _size));
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

	void resize(size_type n, value_type val = value_type())
	{
		if (n > max_size())
			return ;
		while (n < _size)
			_alloc.destroy(_vector + --_size);
		if (n > _size)
			insert(end(), n - _size, val);
	}


	size_type capacity() const{
		return(_capacity);
	};

	bool empty() const{
		return(_size == 0 ? true : false);
	};

	void reserve (size_type n){
		if(n > _capacity)
		{
			pointer tmp = _alloc.allocate(n);
			for(unsigned int i = 0; i < _size; i++)
				tmp[i] = _vector[i];
			_alloc.deallocate(_vector, _capacity);
			_vector = tmp;
			_capacity = n;
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

	reference at(size_type index) {
		if (index >= _size)
			throw out_of_range("Out of range exception!");
		return _vector[index];
	}
	
	const_reference	at(size_type index) const {
		if (index >= _size)
			throw out_of_range("Out of range exception!");
		return _vector[index];
	}

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

	reference front() {
		return(*_vector);
	};
	
	const_reference front() const {
		return(*_vector);
	};

	reference back() {
		return(*(_vector + _size - 1));
	};

	const_reference back() const {
		return(*(_vector + _size - 1));
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
		size_t i = 0;
		InputIterator tmp = first;
		for(; tmp != last; tmp++)
			i++;
		_size = i;
		_vector = _alloc.allocate(_size);
		if(_capacity < _size)
			_capacity = _size;
		InputIterator tmp2 = first;
		for(size_t j = 0; tmp2 != last; tmp2++, j++)
			_vector[j] = *(tmp2);
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
			_capacity *= 2;
			if (!_capacity)
				_capacity = 1;
			pointer tmp = _alloc.allocate(_capacity);
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

	iterator erase(iterator position)
	{
		if (position == --end())
		{
			pop_back();
			return (end());
		}
		size_type	dis_end_pos = _size - (position.base() - _vector + 1);
		memmove(position.base(), (position + 1).base(), dis_end_pos * sizeof(value_type));
		--_size;
		return(position);
	}

	iterator erase(iterator first, iterator last)
	{
		size_type	dist = last - first;
		iterator	after_last = last;
		size_type	dis_end_pos = (end().base() - last.base());
		memmove(first.base(), last.base(), dis_end_pos * sizeof(value_type));
		_size -= dist;
		return(first);
	}

	void swap (vector& x) { // cambiare a ft::swap
		std::swap(_vector, x._vector);
		std::swap(_size, x._size);
		std::swap(_capacity, x._capacity);
	};

	iterator insert(iterator position, const value_type &val)
	{
		size_type equal = position - begin();
		push_back(value_type());
		position = iterator(_vector + equal);
		iterator next = end() - 2, last = position - 1;
		memmove((position + 1).base(), position.base(), (_size - equal) * sizeof(T));
		_alloc.construct(position.base(), val);
		return (position);
	}

	void insert(iterator position, size_type n, const value_type &val)
	{
		size_type equal = position.base() - begin().base();
		size_type new_size = _size + n;
		if (new_size > _capacity)
			reserve(new_size);
		position = iterator(_vector + equal);
		iterator end_ = position - 1;
		memmove((position + n).base(), position.base(), (_size - equal) * sizeof(T));
		for (size_type j = 0; j < n; ++j, ++position)
			_alloc.construct((position).base(), val);
		_size += n;
	}
	
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
	{
		size_type	dist = 0;
		for(InputIterator it = first; it != last; it++)
			dist++;
		size_type	equal = position.base() - _vector;
		size_type	new_size = _size + dist;
		if (new_size > _capacity)
			reserve(new_size);
		position = iterator(_vector + equal);
		memmove((position + dist).base(), (position).base(), (_size - equal) * sizeof(T));
		for (size_type j = 0; j < dist; ++j, ++position, ++first)
			_alloc.construct((position).base(), *first);
		_size += dist;
	}

	void clear() {
		_size = 0;
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
	void recapacity (size_type n) {
		if (n > _capacity)
		{
			pointer temp = _alloc.allocate(n);
			int i = -1;
			while((unsigned int)++i < _size)
				temp[i] = _vector[i];
			_alloc.deallocate(_vector, _capacity);
			_vector = temp;
			_capacity = n;
		}
	};
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
