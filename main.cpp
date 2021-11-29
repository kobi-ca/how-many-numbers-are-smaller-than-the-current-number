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
#include <cassert>

namespace {

    constexpr auto MAX_NUM = 100;

    std::vector<int> smallerNumbersThanCurrent(const std::vector<int>& nums) {
        std::vector<int> smallerThan(MAX_NUM);
        std::for_each(nums.cbegin(), nums.cend(), [&](int n) { smallerThan[n]++; });
        std::exclusive_scan(smallerThan.cbegin(), smallerThan.cend(), smallerThan.begin(), 0);
        std::vector<int> result;
        std::transform(nums.cbegin(), nums.cend(), std::back_inserter(result), [=](int n) { return smallerThan[n]; });
        return result;
    }
}

int main() {
    {
        // 1
        const auto v = std::vector{8, 1, 2, 2, 3};
        const auto result = smallerNumbersThanCurrent(v);
        const auto expected = std::vector{4, 0, 1, 1, 3};
        assert(result == expected);
    }

    {
        // 2
        const auto v = std::vector{6, 5, 4, 8};
        const auto result = smallerNumbersThanCurrent(v);
        const auto expected = std::vector{2, 1, 0, 3};
        assert(result == expected);
    }

    {
        // 3
        const auto v = std::vector{7, 7, 7, 7};
        const auto result = smallerNumbersThanCurrent(v);
        const auto expected = std::vector{0, 0, 0, 0};
        assert(result == expected);
    }

    return 0;
}
