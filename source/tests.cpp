#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "list.hpp"


// Hilfsfunktionen, um indirekt auf die Member der Klasse List zuzugreifen (nur für die Tests!)
template <typename T>
size_t get_size(List<T> const& list_to_test) {return list_to_test.size_;}

template <typename T>
ListNode<T>* get_first_pointer(List<T> const& list_to_test) {return list_to_test.first_;}

template <typename T>
ListNode<T>* get_last_pointer(List<T> const& list_to_test) {return list_to_test.last_;}


//test case definitions for default constructor of list as well as empty and size for empty list
#include "sub_tests/default_constructed_list.test"

//test case definitions for push methods of list
#include "sub_tests/push_front.test"
#include "sub_tests/push_back.test"

//test case definitions for pop methods of list
#include "sub_tests/pop_front.test"
#include "sub_tests/pop_back.test"

#include "sub_tests/clear.test"
#include "sub_tests/copyconst.test"
//test case definitions for 

//test cases for element access of list
#include "sub_tests/front.test"
#include "sub_tests/back.test"

#include "sub_tests/unifying_Assignment.test"
#include "sub_tests/equal.test"


#include "sub_tests/reverse.test" //TODO
//test cases for retrieving iterators
#include "sub_tests/begin.test"
#include "sub_tests/end.test"

//iterator tests
#include "sub_tests/iterators/operator_star.test"
#include "sub_tests/iterators/operator_arrow.test"
#include "sub_tests/iterators/operator_equals.test"
#include "sub_tests/iterators/operator_does_not_equal.test"
#include "sub_tests/iterators/operator_iterate_forward.test"

#include "sub_tests/iterators/insert.test"

#include "sub_tests/iterators/move.test"


#include <map>
struct test_struct{
	int test_1 = 0;
	char test_2 = 'c';
	std::string test_3 = "test";

	bool operator==(test_struct rhs) const {
		return test_1 == rhs.test_1 && test_2 == rhs.test_2 && test_3 == rhs.test_3;
	};
	bool operator!=(test_struct rhs) const {
		return !operator==(rhs);
	};
};
class test_class{
	int test_1 = 0;
	char test_2 = 'c';
	std::string test_3 = "test";

	bool operator==(test_class rhs) const {
		return test_1 == rhs.test_1 && test_2 == rhs.test_2 && test_3 == rhs.test_3;
	};
	bool operator!=(test_class rhs) const {
		return !operator==(rhs);
	};
};

TEST_CASE("push_front 2", "[list_insertion]") {
	List<test_struct> list{};

	list.push_front(test_struct{});
	{
		auto first_pointer = get_first_pointer(list);
		auto last_pointer = get_last_pointer(list);

		SECTION("first_ and last_ should not be nullptrs anymore") {
			REQUIRE(nullptr != first_pointer);
			REQUIRE(nullptr != last_pointer);
		}

		SECTION("the links between nodes are set correctly") {
			REQUIRE(nullptr == first_pointer->prev);
			REQUIRE(nullptr == first_pointer->next);
			REQUIRE(first_pointer == last_pointer);
		}

		SECTION("the only element in the list should be 9") {
			REQUIRE(test_struct{} == first_pointer->value);
		}

		SECTION("the list has size 1 and is not empty") {
			REQUIRE(1 == list.size());
			REQUIRE(false == list.empty());
		}
	}
}
TEST_CASE("reverse Methode 2") {
	List<int> list1{};
	for (int x = 0; x != 10; ++x) {
		list1.push_front(x);
	}
	List<int> list2{};
	for (int x = 0; x != 10; ++x) {
		list2.push_back(x);
	}

	list1.reverse();
	REQUIRE(list1 == list2);
	auto list3 = reverse(list1);
	list1.reverse();
	REQUIRE(list3 == list1);


	List<test_struct> listt1{};
	for (int x = 0; x != 10; ++x) {
		listt1.push_front(test_struct{ x });
	}
	List<test_struct> listt2{};
	for (int x = 0; x != 10; ++x) {
		listt2.push_back(test_struct{ x });
	}
	listt1.reverse();
	REQUIRE(listt1 == listt2);
	auto listt3 = reverse(listt1);
	listt1.reverse();
	REQUIRE(listt3 == listt1);

	List <int> emptylist{};
	List <int> r_emptylist{};
	r_emptylist.reverse();
	REQUIRE(r_emptylist == emptylist);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}




