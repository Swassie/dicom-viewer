#include "common/Event.h"

#include "catch/catch.hpp"

TEST_CASE("Adding event handler.") {

    Event<> event;

    SECTION("if event handler adds more handlers, the rest of the handlers are unaffected.") {
        bool handler_1_run = false;
        bool handler_2_run = false;
        event.add_handler([&] {
            handler_1_run = true;
            event.add_handler([] {});
            event.add_handler([] {});
            event.add_handler([] {});
            event.add_handler([] {});
        });
        event.add_handler([&] {
            handler_2_run = true;
        });

        event.trigger();

        CHECK(handler_1_run);
        CHECK(handler_2_run);
	}
}

TEST_CASE("Removing event handler.") {

    Event<> event;

    SECTION("if event handler removes itself, the rest of the handlers are unaffected.") {
        bool handler_1_run = false;
        bool handler_2_run = false;
        std::function<void()> remove_1;
        auto id_1= event.add_handler([&] {
            handler_1_run = true;
            remove_1();
        });
        remove_1 = event.get_handler_remover(id_1);
        event.add_handler([&] {
            handler_2_run = true;
        });

        event.trigger();

        CHECK(handler_1_run);
        CHECK(handler_2_run);
	}
}
