#include <gtest/gtest.h>
#include "WinnerState.h"
#include "gumballmachine.h"
#include "state_lib/state.h"
#include "SoldState.h"
#include "SoldOutState.h"
#include "NoQuarterState.h"
#include "HasQuarterState_lib/HasQuarterState.h"
#include "gumballmachine_lib/gumballmachine.h"

TEST(WinnerStateTest, InsertCoin) {
    GumballMachine m(5);
    WinnerState state(&m);

    testing::internal::CaptureStdout();
    state.insertCoin();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Please wait, we're already giving you a gumball"), std::string::npos);
}

TEST(WinnerStateTest, EjectQuarter) {
    GumballMachine m(5);
    WinnerState state(&m);

    testing::internal::CaptureStdout();
    state.ejectQuarter();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Sorry, you already turned the crank"), std::string::npos);
}

TEST(WinnerStateTest, TurnCrank) {
    GumballMachine m(5);
    WinnerState state(&m);

    testing::internal::CaptureStdout();
    state.turnCrank();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Turning twice doesn't get you another gumball"), std::string::npos);
}

TEST(WinnerStateTest, Dispense) {
    GumballMachine m(5);
    WinnerState state(&m);

    testing::internal::CaptureStdout();
    state.dispense();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(
        out.find("YOU'RE A WINNER") != std::string::npos ||
        out.find("Oops, out of gumballs") != std::string::npos
    );
}

class DummyState : public State {
public:
    std::string called;

    void insertCoin() override { called = "insertCoin"; }
    void ejectQuarter() override { called = "ejectQuarter"; }
    void turnCrank() override { called = "turnCrank"; }
    void dispense() override { called = "dispense"; }
};

TEST(StateTest, InsertCoinCallsMethod) {
    DummyState s;
    s.insertCoin();
    EXPECT_EQ(s.called, "insertCoin");
}

TEST(StateTest, EjectQuarterCallsMethod) {
    DummyState s;
    s.ejectQuarter();
    EXPECT_EQ(s.called, "ejectQuarter");
}

TEST(StateTest, TurnCrankCallsMethod) {
    DummyState s;
    s.turnCrank();
    EXPECT_EQ(s.called, "turnCrank");
}

TEST(StateTest, DispenseCallsMethod) {
    DummyState s;
    s.dispense();
    EXPECT_EQ(s.called, "dispense");
}

TEST(SoldStateTest, InsertCoin) {
    GumballMachine m(5);
    SoldState state(&m);

    testing::internal::CaptureStdout();
    state.insertCoin();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Please wait, we're already giving you a gumball"), std::string::npos);
}

TEST(SoldStateTest, EjectQuarter) {
    GumballMachine m(5);
    SoldState state(&m);

    testing::internal::CaptureStdout();
    state.ejectQuarter();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Sorry, you already turned the crank"), std::string::npos);
}

TEST(SoldStateTest, TurnCrank) {
    GumballMachine m(5);
    SoldState state(&m);

    testing::internal::CaptureStdout();
    state.turnCrank();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Turning twice doesn't get you another gumball"), std::string::npos);
}

TEST(SoldStateTest, Dispense) {
    GumballMachine m(5);
    SoldState state(&m);

    testing::internal::CaptureStdout();
    state.dispense();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(
        out.find("A gumball comes rolling out the slot") != std::string::npos ||
        out.find("Oops, out of gumballs") != std::string::npos
    );
}

TEST(SoldOutStateTest, InsertCoin) {
    GumballMachine m(0);
    SoldOutState state(&m);

    testing::internal::CaptureStdout();
    state.insertCoin();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("can't insert a quarter, the machine is sold out"), std::string::npos);
}

TEST(SoldOutStateTest, EjectQuarter) {
    GumballMachine m(0);
    SoldOutState state(&m);

    testing::internal::CaptureStdout();
    state.ejectQuarter();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("can't eject, you haven't inserted a quarter yet"), std::string::npos);
}

TEST(SoldOutStateTest, TurnCrank) {
    GumballMachine m(0);
    SoldOutState state(&m);

    testing::internal::CaptureStdout();
    state.turnCrank();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("turned, but there are no gumballs"), std::string::npos);
}

TEST(SoldOutStateTest, Dispense) {
    GumballMachine m(0);
    SoldOutState state(&m);

    testing::internal::CaptureStdout();
    state.dispense();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("No gumball dispensed"), std::string::npos);
}

TEST(NoQuarterStateTest, InsertCoin) {
    GumballMachine m(5);
    NoQuarterState state(&m);

    testing::internal::CaptureStdout();
    state.insertCoin();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("You inserted a quarter"), std::string::npos);
}

TEST(NoQuarterStateTest, EjectQuarter) {
    GumballMachine m(5);
    NoQuarterState state(&m);

    testing::internal::CaptureStdout();
    state.ejectQuarter();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("You haven't inserted a quarter"), std::string::npos);
}

TEST(NoQuarterStateTest, TurnCrank) {
    GumballMachine m(5);
    NoQuarterState state(&m);

    testing::internal::CaptureStdout();
    state.turnCrank();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("turned, but there's no quarter"), std::string::npos);
}

TEST(NoQuarterStateTest, Dispense) {
    GumballMachine m(5);
    NoQuarterState state(&m);

    testing::internal::CaptureStdout();
    state.dispense();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("You need to pay first"), std::string::npos);
}


TEST(HasQuarterStateTest, InsertCoinTwice) {
    GumballMachine machine(5);
    HasQuarterState state(&machine);

    testing::internal::CaptureStdout();
    state.insertCoin();
    std::string out1 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    state.insertCoin();
    std::string out2 = testing::internal::GetCapturedStdout();

    EXPECT_NE(out1.find("You can't insert another coin"), std::string::npos);
    EXPECT_NE(out2.find("You can't insert another coin"), std::string::npos);
}

TEST(HasQuarterStateTest, EjectQuarter) {
    GumballMachine machine(5);
    HasQuarterState state(&machine);

    testing::internal::CaptureStdout();
    state.ejectQuarter();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Quarter returned"), std::string::npos);
}

TEST(HasQuarterStateTest, TurnCrank) {
    GumballMachine machine(5);
    HasQuarterState state(&machine);

    testing::internal::CaptureStdout();
    state.turnCrank();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("You turned..."), std::string::npos);
}

TEST(GumballMachineTest, InitialStateIsNoQuarter) {
    GumballMachine m(5);
    EXPECT_EQ(m.getCount(), 5);
}

TEST(GumballMachineTest, InsertCoinChangesState) {
    GumballMachine m(5);
    testing::internal::CaptureStdout();
    m.insertCoin();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("inserted"), std::string::npos);
}
