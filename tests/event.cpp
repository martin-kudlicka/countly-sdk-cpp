#include "countly.hpp"
#include "doctest.h"

TEST_CASE("events are serialized correctly") {
	SUBCASE("without segmentation") {
		SUBCASE("without sum") {
			Countly::Event event("win", 1);
			CHECK(event.serialize() == "{\"key\":\"win\",\"count\":1}");
		}

		SUBCASE("with sum") {
			Countly::Event event("buy", 2, 9.99);
			CHECK(event.serialize() == "{\"key\":\"buy\",\"count\":2,\"sum\":9.99}");
		}
	}

	SUBCASE("with segmentation") {
		SUBCASE("with raw json") {
			Countly::Event event("buy", 1);
			event.addSegmentationRaw("productID", "null");
			CHECK(event.serialize() == "{\"key\":\"buy\",\"count\":1,\"segmentation\":{\"productID\":null}}");
		}

		SUBCASE("with signed integer") {
			Countly::Event event("lose", 3);
			event.addSegmentation("points", -144);
			CHECK(event.serialize() == "{\"key\":\"lose\",\"count\":3,\"segmentation\":{\"points\":-144}}");
		}

		SUBCASE("with unsigned integer") {
			Countly::Event event("win", 1);
			event.addSegmentation("points", 4294967295ULL);
			CHECK(event.serialize() == "{\"key\":\"win\",\"count\":1,\"segmentation\":{\"points\":4294967295}}");
		}

		SUBCASE("with boolean") {
			Countly::Event event("win", 1);
			event.addSegmentation("alive", true);
			CHECK(event.serialize() == "{\"key\":\"win\",\"count\":1,\"segmentation\":{\"alive\":true}}");
		}

		SUBCASE("with string") {
			Countly::Event event("message", 1);
			event.addSegmentation("sender", "TheLegend27");
			CHECK(event.serialize() == "{\"key\":\"message\",\"count\":1,\"segmentation\":{\"sender\":\"TheLegend27\"}}");
		}

		SUBCASE("with multiple values") {
			Countly::Event event("buy", 5);
			event.addSegmentation("quantity", 27);
			event.addSegmentation("searchQuery", "cheap cheese");
			CHECK(event.serialize() == "{\"key\":\"buy\",\"count\":5,\"segmentation\":{\"quantity\":27,\"searchQuery\":\"cheap cheese\"}}");
		}

		SUBCASE("with changing values") {
			Countly::Event event("lose", 3);
			event.addSegmentation("points", -144);
			event.addSegmentation("points", 2000);
			CHECK(event.serialize() == "{\"key\":\"lose\",\"count\":3,\"segmentation\":{\"points\":2000}}");
		}
	}
}