#include <unistd.h>
#include <thread>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::StrictMock;

class MockEpollListener : public EpollListener {
    MOCK_METHOD(int, getFd, (), (override));
    MOCK_METHOD(void, triggerIn, (), (override));
};

TEST(EpollController, trggersInputEvent) {
    int fd = open();

    StrictMock<MockEpollListener> l;
    ON_CALL(l, triggerIn())
    .WillByDefault([] {});
    ON_CALL(l, getFd())
    .WillByDefault(Return(fd));

    EpollController* controller = new EpollController();
    controller->addListener(l);

    std::thread t([fd] {
        write(fd, "test", 4);
    })

    controller->listen(10);

    EXPECT_CALL(l, triggerIn());
    EXPECT_EQ(3, 4);
} 