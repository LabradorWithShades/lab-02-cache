// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#include <gtest/gtest.h>
#include "tester.hpp"
#include <chrono>

TEST(General, IsLaunching) {
  std::vector<uint32_t> array_sizes;
  uint32_t L1 = 128,
           L3 = 8192; //In KiB
  uint32_t current = L1 / 2;
  while (current < 3 * L3 / 2) {
    array_sizes.push_back(current * 256); //* 1024 / 4 = * 256
    current <<= 1; //Multiply by 2
  }
  array_sizes.push_back(3 * L3 * 128);

  Tester tester(array_sizes);
  tester.performTests();
  EXPECT_TRUE(true);
}
