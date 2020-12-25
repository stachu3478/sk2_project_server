#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::StrictMock;

class MockEpollController : public EpollController {
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(void, onClose, (EpollCloseCallback* e), (override));
};

class MockCloseCallback : public ServerCloseCallback {
    MOCK_METHOD(void, call, (), (override));
};

TEST(Server, closesWithoutErrors) {
    StrictMock<MockEpollController> c;
    ON_CALL(c, close())
    .WillByDefault([&c] {
        c.closeCallback.call();
    });

    StrictMock<MockCloseCallback> cb;

    Server* server = new Server();
    server->setEpollController(&c);
    server->onShutdown(&cb);
    server->close();

    EXPECT_CALL(c, close());
    EXPECT_CALL(cb, call());
} 