
#include <catch2/catch_test_macros.hpp>
#include <unordered_set>

#include "shares.h"
#include "tinyecs.h"

using namespace tinyecs;
using namespace tinyecs_tests;

TEST_CASE("query_filters_enum") {

  World w;
  SETUP_INDEX;

  auto &a1 = w.NewArchetype<D>();
  auto &a2 = w.NewArchetype<F>();
  auto &a3 = w.NewArchetype<D, F>();

  auto e1 = a1.NewEntity();
  auto e2 = a2.NewEntity();
  auto e3 = a3.NewEntity();

  // query status == s1
  Query<F> q1(w, {index5 == Status::S1});
  q1.PreMatch();
  std::unordered_set<EntityId> m1;
  q1.ForEach([&](EntityReference &e) {
    REQUIRE(e.IsAlive());
    REQUIRE(e.Get<F>().status == Status::S1);
    m1.insert(e.GetId());
  });
  REQUIRE(m1 == decltype(m1){e2, e3});

  // query status == s2 &&  x > 100
  w.Get(e2).Get<F>().status = Status::S2;
  w.Get(e3).Get<F>().status = Status::S2;
  w.Get(e3).Get<D>().x = 9999;
  auto e4 = a3.NewEntity();
  auto e5 = a3.NewEntity();
  w.Get(e4).Get<D>().x = 3999;
  w.Get(e5).Get<D>().x = 3999;
  w.Get(e5).Get<F>().status = Status::S2;

  Query<F> q2(w, {index5 == Status::S2, index1 > 100});
  q2.PreMatch();
  std::unordered_set<EntityId> m2;
  q2.ForEach([&](EntityReference &e) {
    REQUIRE(e.IsAlive());
    REQUIRE(e.Get<F>().status == Status::S2);
    REQUIRE(e.Get<D>().x > 100);
    m2.insert(e.GetId());
  });
  REQUIRE(m2 == decltype(m2){e3, e5});
}
