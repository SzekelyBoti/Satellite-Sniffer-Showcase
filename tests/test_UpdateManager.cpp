#include <gtest/gtest.h>
#include "UpdateManager.h"

// Use nullptr for Application since we're not testing interactions with it
class UpdateManagerTest : public ::testing::Test {
protected:
  UpdateManager* manager;

  void SetUp() override {
    manager = new UpdateManager(nullptr);
  }

  void TearDown() override {
    delete manager;
  }
};

TEST_F(UpdateManagerTest, DefaultValues) {
  EXPECT_DOUBLE_EQ(manager->getSimulatedTime(), 0.0);
  EXPECT_DOUBLE_EQ(manager->getSpeedMultiplier(), 1.0);
}

TEST_F(UpdateManagerTest, SetModeChangesMode) {
  manager->setMode(UpdateMode::MANUAL);
  manager->setMode(UpdateMode::REALTIME);
  manager->setMode(UpdateMode::SIMULATION);
}

TEST_F(UpdateManagerTest, SpeedMultiplierChange) {
  manager->setSpeedMultiplier(2.5);
  EXPECT_DOUBLE_EQ(manager->getSpeedMultiplier(), 2.5);
  manager->setSpeedMultiplier(0.5);
  EXPECT_DOUBLE_EQ(manager->getSpeedMultiplier(), 0.5);
}

TEST_F(UpdateManagerTest, ResetSimulationResetsTime) {
  manager->tick();
  manager->resetSimulation();
  EXPECT_DOUBLE_EQ(manager->getSimulatedTime(), 0.0);
}

TEST_F(UpdateManagerTest, NextPrevStepAdjustsMultiplier) {
  double initial = manager->getSpeedMultiplier();
  manager->nextStep();
  EXPECT_NE(manager->getSpeedMultiplier(), initial);
  manager->prevStep();
  EXPECT_DOUBLE_EQ(manager->getSpeedMultiplier(), initial);
}


