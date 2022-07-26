#include "../../fair/dynamic_array.h"
#include "test.h"

TEST("dynamic array empty") {
  FAIR_DA_CREATE(v, char, 0);

  REQUIRE(v.size == 0);

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array resize") {
  FAIR_DA_CREATE(v, char, 0);
  FAIR_DA_RESIZE(v, 10);

  REQUIRE(v.size == 10);

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array grow") {
  FAIR_DA_CREATE(v, char, 2);
  FAIR_DA_RESIZE(v, 10);

  REQUIRE(v.size == 10);

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array diminish") {
  FAIR_DA_CREATE(v, char, 10);
  FAIR_DA_RESIZE(v, 9);

  REQUIRE(v.size == 9);

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array of chars") {
  FAIR_DA_CREATE(v, char, 100);

  REQUIRE(v.size == 100);
  REQUIRE(v.capacity >= 100);
  REQUIRE(v.values != NULL);

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array push") {
  FAIR_DA_CREATE(v, char, 0);
  FAIR_DA_APPEND(v, 'x');

  REQUIRE(v.size == 1);
  REQUIRE(v.values[0] == 'x');

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array insert front") {
  FAIR_DA_CREATE(v, char, 3);

  v.values[0] = 'a';
  v.values[1] = 'b';
  v.values[2] = 'c';

  FAIR_DA_INSERT(v, 0, 'x');

  REQUIRE(v.size == 4);
  REQUIRE(v.values[0] == 'x');
  REQUIRE(v.values[1] == 'a');
  REQUIRE(v.values[2] == 'b');
  REQUIRE(v.values[3] == 'c');

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array insert back") {
  FAIR_DA_CREATE(v, char, 3);

  v.values[0] = 'a';
  v.values[1] = 'b';
  v.values[2] = 'c';

  FAIR_DA_INSERT(v, 3, 'x');

  REQUIRE(v.size == 4);
  REQUIRE(v.values[0] == 'a');
  REQUIRE(v.values[1] == 'b');
  REQUIRE(v.values[2] == 'c');
  REQUIRE(v.values[3] == 'x');

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array insert middle") {
  FAIR_DA_CREATE(v, char, 3);

  v.values[0] = 'a';
  v.values[1] = 'b';
  v.values[2] = 'c';

  FAIR_DA_INSERT(v, 2, 'x');

  REQUIRE(v.size == 4);
  REQUIRE(v.values[0] == 'a');
  REQUIRE(v.values[1] == 'b');
  REQUIRE(v.values[2] == 'x');
  REQUIRE(v.values[3] == 'c');

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array erase front") {
  FAIR_DA_CREATE(v, char, 3);

  v.values[0] = 'a';
  v.values[1] = 'b';
  v.values[2] = 'c';

  FAIR_DA_ERASE(v, 0);

  REQUIRE(v.size == 2);
  REQUIRE(v.values[0] == 'b');
  REQUIRE(v.values[1] == 'c');

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array erase back") {
  FAIR_DA_CREATE(v, char, 3);

  v.values[0] = 'a';
  v.values[1] = 'b';
  v.values[2] = 'c';

  FAIR_DA_ERASE(v, 2);

  REQUIRE(v.size == 2);
  REQUIRE(v.values[0] == 'a');
  REQUIRE(v.values[1] == 'b');

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array erase middle") {
  FAIR_DA_CREATE(v, char, 3);

  v.values[0] = 'a';
  v.values[1] = 'b';
  v.values[2] = 'c';

  FAIR_DA_ERASE(v, 1);

  REQUIRE(v.size == 2);
  REQUIRE(v.values[0] == 'a');
  REQUIRE(v.values[1] == 'c');

  FAIR_DA_DESTROY(v);
}

TEST("dynamic array of ints") {
  FAIR_DA_CREATE(v, int, 10);
  FAIR_DA_RESIZE(v, 5);
  v.values[4] = 42;
  FAIR_DA_APPEND(v, 43);

  REQUIRE(v.size == 6);
  REQUIRE(v.values[4] == 42);
  REQUIRE(v.values[5] == 43);

  FAIR_DA_DESTROY(v);
}
