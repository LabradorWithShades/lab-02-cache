// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#include "tester.hpp"

#include <chrono>

Tester::Tester(const std::vector<uint32_t>& array_sizes)
  : m_array_sizes(array_sizes) {
}

void Tester::performTests(std::ostream& out) const {
  //Direct
  out << "investigation:" << std::endl << "travel_variant: direct" <<\
         std::endl << "experiments:" << std::endl;
  for (size_t i = 0; i < m_array_sizes.size(); ++i) {
    out << "    number: " << i + 1 << std::endl <<\
           "    input data:" << std::endl <<\
           "      buffer_size: " << m_array_sizes[i] / 256 << " KiB" <<\
                                                           std::endl <<\
           "    results:" << std::endl <<\
           "      duration: " << performDirectTest(m_array_sizes[i]) <<\
           " mcs" << std::endl;
  }

  //Reverse
  out << "investigation:" << std::endl << "travel_variant: reverse" <<\
         std::endl << "experiments:" << std::endl;
  for (size_t i = 0; i < m_array_sizes.size(); ++i) {
    out << "    number: " << i + 1 << std::endl <<\
           "    input data:" << std::endl <<\
           "      buffer_size: " << m_array_sizes[i] / 256 << " KiB" <<\
                                                           std::endl <<\
           "    results:" << std::endl <<\
           "      duration: " << performReverseTest(m_array_sizes[i]) <<\
           " mcs" << std::endl;
  }

  //Random
  out << "investigation:" << std::endl << "travel_variant: random" <<\
         std::endl << "experiments:" << std::endl;
  for (size_t i = 0; i < m_array_sizes.size(); ++i) {
    out << "    number: " << i + 1 << std::endl <<\
           "    input data:" << std::endl <<\
           "      buffer_size: " << m_array_sizes[i] / 256 << " KiB" <<\
                                                           std::endl <<\
           "    results:" << std::endl <<\
           "      duration: " << performRandomTest(m_array_sizes[i]) <<\
           " mcs" << std::endl;
  }
}

double Tester::performDirectTest(uint32_t array_size) const {
  uint32_t* array = genRandomArray(array_size);
  uint32_t arr_var = 0;

  //Avoid unused variable warning
  arr_var = arr_var + 1;

  //Cache warmup
  for (uint32_t i = 0; i < array_size; i += 16)
    arr_var = array[i];

  //Test
  const int test_count = 1000;
  int64_t time_taken = 0;
  for (int j = 0; j < test_count; ++j) {
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t i = 0; i < array_size; i += 16)
      arr_var = array[i];
    auto finish = std::chrono::high_resolution_clock::now();
    time_taken +=
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
            .count();
  }

  //Free the array
  freeArray(array);
  return (static_cast<double>(time_taken) / 1000.0);
}

double Tester::performReverseTest(uint32_t array_size) const {
  uint32_t* array = genRandomArray(array_size);
  uint32_t arr_var = 0;

  //Avoid unused variable warning
  arr_var = arr_var + 1;

  //Cache warmup
  for (uint32_t i = 0; i < array_size; i += 16)
    arr_var = array[array_size - i - 1];

  //Test
  int64_t time_taken = 0;
  const int test_count = 1000;
  for (int j = 0; j < test_count; ++j) {
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t i = 0; i < array_size; i += 16)
      arr_var = array[array_size - i - 1];
    auto finish = std::chrono::high_resolution_clock::now();
    time_taken +=
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
            .count();
  }

  //Free the array
  freeArray(array);
  return static_cast<double>(time_taken) / 1000.0;
}

double Tester::performRandomTest(uint32_t array_size) const {
  uint32_t* array = genRandomArray(array_size);
  uint32_t arr_var = 0;

  //Avoid unused variable warning
  arr_var = arr_var + 1;

  //Cache warmup
  for (uint32_t i = 0; i < array_size / 16; ++i)
    arr_var = array[getRandom(0, array_size - 1)];

  //Test
  int64_t time_taken = 0;
  const int test_count = 1000;
  for (int j = 0; j < test_count; ++j) {
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t i = 0; i < array_size / 16; ++i)
      arr_var = array[getRandom(0, array_size - 1)];
    auto finish = std::chrono::high_resolution_clock::now();
    time_taken +=
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
            .count();
  }

  //Free the array
  freeArray(array);
  return static_cast<double>(time_taken) / 1000.0;
}

uint32_t* Tester::genRandomArray(uint32_t size) const {
  uint32_t* array = new uint32_t[size];
  for (uint32_t i = 0; i < size; ++i)
    array[i] = random();
  return array;
}

void Tester::freeArray(uint32_t* array) const {
  delete[] array;
}

uint32_t Tester::getRandom(uint32_t lower, uint32_t upper) const {
  return lower + random() % (upper - lower + 1);
}
