#include <gtest/gtest.h>
#include <glog/logging.h>

TEST(test_gtest, demo1){

    LOG(INFO) << "Test Gtest Start";
    ASSERT_NEAR(1, 1, 1.0e-11);
    LOG(INFO) << "Test Gtest End";

}