#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "Shares.h"
#include "TinyECS.h"

using namespace TinyECS;
using namespace TinyECS_Tests;

TEST_CASE("query_filters_where/1", "[simple]")
{
	World w;
	SETUP_INDEX;

	auto& a1 = w.NewArchetype<D, E>();
	auto& a2 = w.NewArchetype<D, E>();
	auto& a3 = w.NewArchetype<D, F>();

	auto e1 = a1.NewEntity();
	auto e2 = a2.NewEntity();
	auto e3 = a3.NewEntity();

	e1.Get<D>().x = 0;
	e1.Get<E>().z = "xyz";

	e2.Get<D>().x = 1;
	e2.Get<E>().z = "xyz";

	e3.Get<D>().x = 3;
	e3.Get<F>().status = Status::S2;

	Query<D, E> q(w, { index1 >= 1 });
	q.PreMatch();
	q.Where(Filters{ index2 == "xyz" }).Where(index1 < 2);

	std::vector<EntityId> z1;
	q.ForEach([&z1](EntityReference& e) { z1.push_back(e.GetId()); });
	REQUIRE(z1 == decltype(z1){ e2.GetId() });

	q.ClearFilters();
	q.Where(Filters{ index2 == "xyz" }).Where(index1 < 2);
	z1.clear();
	q.ForEach([&z1](EntityReference& e) { z1.push_back(e.GetId()); });
	REQUIRE(z1 == decltype(z1){ e1.GetId(), e2.GetId() });
}
