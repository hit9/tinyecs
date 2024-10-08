#include "TinyECS.h"
#include <string>

using namespace TinyECS;
// Components

namespace TinyECS_Tests
{

	enum class Status
	{
		S1,
		S2,
		S3
	};

	struct A
	{
		int		 x = 0;
		uint32_t y = 1;
	};
	struct B
	{
		std::string s = "abc";
	};
	struct C
	{
		int32_t x = 1;
	};

	extern OrderedFieldIndex<int> index1;
	struct D
	{
		FieldProxy<int, decltype(index1)> x = 0;
		D(int v = 0)
			: x(v) { x.BindIndex(index1); }
	};

	extern OrderedFieldIndex<std::string> index2;
	extern OrderedFieldIndex<int>		  index3;
	struct E
	{
		float									  y = 3.14;
		FieldProxy<int, decltype(index3)>		  x = 0;
		FieldProxy<std::string, decltype(index2)> z = std::string("abc");
		void									  BindIndexes()
		{

			x.BindIndex(index3);
			z.BindIndex(index2);
		}
		E(float y = 3.14, int x = 0, const std::string& z = "abc")
			: y(y), x(x), z(z) { BindIndexes(); }
		E(int x, const std::string& z = "abc")
			: x(x), z(z) { BindIndexes(); }
	};

	extern UnorderedFieldIndex<Status> index5;
	struct F
	{
		FieldProxy<Status, decltype(index5)> status = Status::S1;
		F(Status s = Status::S1)
			: status(s) { status.BindIndex(index5); }
	};

	extern UnorderedFieldIndex<bool> index6;
	struct G
	{
		FieldProxy<bool, decltype(index6)> isX = false;
		G() { isX.BindIndex(index6); }
	};

	extern UnorderedFieldIndex<std::string> index7;
	struct H
	{
		FieldProxy<std::string, decltype(index7)> h = "xyz";
		H() { h.BindIndex(index7); }
	};
	struct I
	{
	};
	struct J
	{
	};
	static bool kDescructorCalled = false;
	struct K
	{
		int a, b;
		K() { a = 1, b = 3; }
		~K() { kDescructorCalled = true; }
	};

	// Guarantee A, B, C, D's id is 0,1,2,3 on this file's first included
	static const auto ID_A = Internal::IComponent<A>::GetId();
	static const auto ID_B = Internal::IComponent<B>::GetId();
	static const auto ID_C = Internal::IComponent<C>::GetId();
	static const auto ID_D = Internal::IComponent<D>::GetId();
	static const auto ID_E = Internal::IComponent<E>::GetId();
	static const auto ID_F = Internal::IComponent<F>::GetId();
	static const auto ID_G = Internal::IComponent<G>::GetId();
	static const auto ID_H = Internal::IComponent<H>::GetId();
	static const auto ID_I = Internal::IComponent<I>::GetId();
	static const auto ID_J = Internal::IComponent<J>::GetId();
	static const auto ID_K = Internal::IComponent<K>::GetId();

#define SETUP_INDEX               \
	do                            \
	{                             \
		index1.Clear();           \
		index2.Clear();           \
		index3.Clear();           \
		index5.Clear();           \
		index6.Clear();           \
		index7.Clear();           \
		index1.Bind(w);           \
		index2.Bind(w);           \
		index3.Bind(w);           \
		index5.Bind(w);           \
		index6.Bind(w);           \
		index7.Bind(w);           \
		REQUIRE(index1.IsBind()); \
		REQUIRE(index2.IsBind()); \
		REQUIRE(index3.IsBind()); \
		REQUIRE(index5.IsBind()); \
		REQUIRE(index6.IsBind()); \
		REQUIRE(index7.IsBind()); \
	}                             \
	while (0)

} // namespace TinyECS_Tests
