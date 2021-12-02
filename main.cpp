#include <iostream>

/**
 * Leetcode 1365. How Many Numbers Are Smaller Than the Current Number
 * Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it.
 * That is, for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].
 * Return the answer in an array.
 *
 * Constraints:
 * 2 <= nums.length <= 500
 * 0 <= nums[i] <= 100
 *
 */

#include <vector>
#include <numeric>
#include <algorithm>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace {

    constexpr auto MAX_NUM = 100;

    // best, O(N)
    std::vector<int> smallerNumbersThanCurrent(const std::vector<int>& nums) {
        std::vector<int> smallerThan(MAX_NUM);
        std::for_each(nums.cbegin(), nums.cend(), [&](int n) { smallerThan[n]++; });
        std::exclusive_scan(smallerThan.cbegin(), smallerThan.cend(), smallerThan.begin(), 0);
        std::vector<int> result;
        std::transform(nums.cbegin(), nums.cend(), std::back_inserter(result), [=](int n) { return smallerThan[n]; });
        return result;
    }

    // brute force, O(N^2)
    std::vector<int> smallerNumbersThanCurrentBrute(const std::vector<int>& nums) {
        std::vector<int> result;
        for(const auto i : nums) {
            const auto f{[i](const auto v){ return v < i; }};
            const auto res = std::count_if(std::begin(nums), std::end(nums), f);
            result.push_back(static_cast<int>(res));
        }
        return result;
    }

    // with sort n log n
    std::vector<int> smallerNumbersThanCurrentSort(const std::vector<int>& nums) {
        auto sorted = nums;
        std::sort(std::begin(sorted), std::end(sorted));
        std::vector<int> result;
        for(auto i{0} ;i < sorted.size(); ++i) {
            const auto res = std::lower_bound(std::begin(sorted), std::end(sorted), nums[i]);
            const auto dis = std::distance(std::begin(sorted), res);
            result.push_back(static_cast<int>(dis));
        }
        return result;
    }

    // with sort+map n log n
    std::vector<int> smallerNumbersThanCurrentMap(const std::vector<int>& nums) {
        auto sorted = nums;
        std::sort(std::begin(sorted), std::end(sorted));
        std::unordered_map<int, int> sorted_val_to_sorted_idx;
        std::ignore = std::transform(std::begin(sorted), std::end(sorted),
                                     std::inserter(sorted_val_to_sorted_idx, std::begin(sorted_val_to_sorted_idx)),
                                     [i=0](const auto v) mutable { return std::make_pair(v, i++); });
        std::vector<int> result;
        for(const auto v : nums) {
            result.push_back(sorted_val_to_sorted_idx[v]);
        }
        return result;
    }
}

TEST(main, first) {
    const auto v = std::vector{8, 1, 2, 2, 3};
    const auto result = smallerNumbersThanCurrent(v);
    const auto expected = std::vector{4, 0, 1, 1, 3};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

TEST(main, second) {
    const auto v = std::vector{6, 5, 4, 8};
    const auto result = smallerNumbersThanCurrent(v);
    const auto expected = std::vector{2, 1, 0, 3};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

TEST(main, third) {
    const auto v = std::vector{7, 7, 7, 7};
    const auto result = smallerNumbersThanCurrent(v);
    const auto expected = std::vector{0, 0, 0, 0};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

// brute
TEST(main, first_brute) {
    const auto v = std::vector{8, 1, 2, 2, 3};
    const auto result = smallerNumbersThanCurrentBrute(v);
    const auto expected = std::vector{4, 0, 1, 1, 3};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

TEST(main, second_brute) {
    const auto v = std::vector{6, 5, 4, 8};
    const auto result = smallerNumbersThanCurrentBrute(v);
    const auto expected = std::vector{2, 1, 0, 3};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

TEST(main, third_brute) {
    const auto v = std::vector{7, 7, 7, 7};
    const auto result = smallerNumbersThanCurrentBrute(v);
    const auto expected = std::vector{0, 0, 0, 0};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

// sort
TEST(main, first_sort) {
    const auto v = std::vector{8, 1, 2, 2, 3};
    const auto result = smallerNumbersThanCurrentSort(v);
    const auto expected = std::vector{4, 0, 1, 1, 3};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

TEST(main, second_sort) {
    const auto v = std::vector{6, 5, 4, 8};
    const auto result = smallerNumbersThanCurrentSort(v);
    const auto expected = std::vector{2, 1, 0, 3};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

TEST(main, third_sort) {
    const auto v = std::vector{7, 7, 7, 7};
    const auto result = smallerNumbersThanCurrentSort(v);
    const auto expected = std::vector{0, 0, 0, 0};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

// sort + map
TEST(main, first_sort_plus_map) {
    const auto v = std::vector{8, 1, 2, 2, 3};
    const auto result = smallerNumbersThanCurrentMap(v);
    const auto expected = std::vector{4, 0, 1, 1, 3};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

TEST(main, second_sort_plus_map) {
    const auto v = std::vector{6, 5, 4, 8};
    const auto result = smallerNumbersThanCurrentMap(v);
    const auto expected = std::vector{2, 1, 0, 3};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}

TEST(main, third_sort_plus_map) {
    const auto v = std::vector{7, 7, 7, 7};
    const auto result = smallerNumbersThanCurrentMap(v);
    const auto expected = std::vector{0, 0, 0, 0};
    EXPECT_THAT(result, ::testing::ContainerEq(expected));
}
