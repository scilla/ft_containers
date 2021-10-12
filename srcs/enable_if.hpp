#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	template <typename _Tp, _Tp __v>
	struct integral_constant
	{
		static const _Tp                  value = __v;
		typedef _Tp                           value_type;
		typedef integral_constant<_Tp, __v>   type;
	};

	typedef integral_constant<bool, true>	true_type;

	typedef integral_constant<bool, false>	false_type;

	template <typename>
	struct __is_integral_helper : public false_type {};

	template<>
		struct __is_integral_helper<bool>
		: public true_type { };

	template<>
		struct __is_integral_helper<char>
		: public true_type { };

	template<>
		struct __is_integral_helper<signed char>
		: public true_type { };

	template<>
		struct __is_integral_helper<unsigned char>
		: public true_type { };

	template<>
		struct __is_integral_helper<short>
		: public true_type { };

	template<>
		struct __is_integral_helper<unsigned short>
		: public true_type { };

	template<>
		struct __is_integral_helper<int>
		: public true_type { };

	template<>
		struct __is_integral_helper<unsigned int>
		: public true_type { };

	template<>
		struct __is_integral_helper<long>
		: public true_type { };

	template<>
		struct __is_integral_helper<unsigned long>
		: public true_type { };

	template <typename T>
		struct is_integral : public __is_integral_helper<T> { };

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

}

#endif
