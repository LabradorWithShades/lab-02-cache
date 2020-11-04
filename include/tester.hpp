// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#ifndef INCLUDE_TESTER_HPP_
#define INCLUDE_TESTER_HPP_

#include <cstdint>
#include <iostream>
#include <vector>

class Tester {
 public:
  explicit Tester(const std::vector<uint32_t>& array_sizes);

  void performTests(std::ostream& out = std::cout);
 private:
  double performDirectTest(uint32_t array_size);
  double performReverseTest(uint32_t array_size);
  double performRandomTest(uint32_t array_size);

  uint32_t getRandom(uint32_t lower, uint32_t upper);

  uint32_t* genRandomArray(uint32_t size);
  void freeArray(uint32_t* array);
 private:
  std::vector<uint32_t> m_array_sizes;
};

#endif //INCLUDE_TESTER_HPP_
