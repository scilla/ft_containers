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
namespace ft
{
template <class T>
class vector_iterator: public iterator<T>
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
		vector_iterator(const vector_iterator<U>& vect): { *this = vect; } 
		~vector_iterator();
		pointer		base() const { return _ptr; }
	private:
		pointer		_ptr;
};

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

	typedef vector_iterator<T>							iterator;
	typedef std::reverse_iterator<iterator>				reverse_iterator; //da correggere
	typedef vector_iterator<const_pointer>				const_iterator;
	typedef std::reverse_iterator<const_pointer>		const_reverse_iterator; //da correggere

	// (con|des)tructors
	explicit vector (const allocator_type& alloc = allocator_type()):
					_alloc(alloc),
					_vector(NULL),
					_size(0),
					_capacity(0)
	{}
	explicit vector (unsigned int n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()):
					_alloc(alloc),
					_size(n),
					_capacity(n) // SBAGLIATO
	{
		_vector = _alloc.allocate(n);
		for (int i = 0; i < 0; i++) {
			_vector[i] = val;
		}
	}
	template <class inputType>
	vector (inputType first, inputType last,
			const allocator_type& alloc = allocator_type()):
			_alloc(alloc)
	{
		_size = (last - first) / sizeof(inputType);
		_capacity = _size; //SBAGLIATO
		_vector = _alloc.allocate(_size);
	}
	vector (const vector& x);
	~vector();

	// iterators
	iterator begin() {
		return(iterator(_vector));
	};
	iterator end(){
		return(iterator(_vector + _size));
	};
	reverse_iterator rbegin(){
		return(reverse_iterator(end()));
	};
	reverse_iterator rend(){
		return(reverse_iterator(begin()));
	};
	const_iterator cbegin() const noexcept{
		return(const_iterator(_vector)));
	};

	const_iterator cend() const noexcept{
		return(const_iterator(_vector + _size));
	};
	const_reverse_iterator crbegin() const noexcept
	{
		return(const_reverse_iterator(cbegin()));
	};
	const_reverse_iterator crend() const noexcept{
		return(const_reverse_iterator(cend()));
	};

	// capacity

	size_type size() const {
		return(_size);
	};

	size_type max_size() const{
		return(allocator.max_size());
	};

	void resize (size_type n, value_type val = value_type()) {
		if(n < _size)
		{
			pointer temp = allocator.allocate(n * 2);
			for (unsigned int i = 0; i < n; i++)
				temp[i] = _vector[i];
			allocator.deallocate(_vector, _capacity);
			_vector = temp;
			_size = n;
			_capacity = n * 2;
		}
		else if (n > _capacity)
		{
			pointer temp = allocator.allocate(n * 2)
			int i = -1;
			while(++i <= _size)
				temp[i] = _vector[i];
			while(++i < n * 2)
				temp[i] = val;
			allocator.deallocate(_vector, _capacity);
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
			pointer tmp = allocator.allocate(n * 2);
			for(unsigned int i = 0; i < _size; i++)
				tmp[i] = _vector[i];
			allocator.deallocate(_vector));
			_vector = tmp;
			_capacity = n * 2;
		}
	};

	void shrink_to_fit(){
		if(_capacity > _size)
		{
			pointer tmp = allocator.allocate(_size);
			for(int i = 0; i < _size; i++)
				tmp[i] = _vector[i];
			allocator.deallocate(_vector);
			_vector = tmp;
			_capacity = _size;
		}
	};

	// access

	reference operator[] (size_type n) {
		return(reference(_vector + n));
	};

	const_reference operator[] (size_type n) const {
		return(const_reference(_vector + n));
	};

	reference at (size_type n) {
		return(reference(_vector + n));
	};

	const_reference at (size_type n) const {
		return(const_reference(_vector + n));
	};

	reference front() {
		return(reference(_vector));
	};
	
	const_reference front() const {
		return(const_reference(_vector));
	};

	reference back() {
		return(reference(_vector + _size));
	};

	const_reference back() const {
		return(const_reference(_vector + _size));
	};
	
	value_type* data() noexcept;
	const value_type* data() const noexcept;

	// modifiers
	// operators
protected:
	iterator		_current;
private:
	pointer			_vector;
	size_type		_size;
	size_type		_capacity;
	allocator_type	_alloc;
};

} // namespace ft

#endif /* VECTOR_HPP */
