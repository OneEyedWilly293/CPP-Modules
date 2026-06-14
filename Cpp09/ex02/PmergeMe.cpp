#include "PmergeMe.hpp"
#include <algorithm>     // std::find, std::lower_bound
#include <chrono>        // std::chrono for timing
#include <stdexcept>     // std::runtime_error
#include <climits>       // INT_MAX
#include <iomanip>       // std::fixed, std::setprecision
#include <cctype>        // std::isdigit

// ════════════════════════════════════════════════════
//   ORTHODOX CANONICAL FORM
// ════════════════════════════════════════════════════

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
    : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    // Guard against self-assignment (e.g. obj = obj)
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

// ════════════════════════════════════════════════════
//   PARSING
// ════════════════════════════════════════════════════

void PmergeMe::parseArgs(int argc, char** argv)
{
    // argv[0] is the program name, so start from index 1
    for (int i = 1; i < argc; i++)
    {
        std::string s = argv[i];

        // Every character must be a digit (no negatives, no letters)
        for (char c : s)
        {
            if (!std::isdigit(c))
                throw std::runtime_error("Error: invalid input: " + s);
        }

        if (s.empty())
            throw std::runtime_error("Error: empty argument");

        // stol handles large numbers safely before casting to int
        long val = std::stol(s);

        // Must be strictly positive and fit in an int
        if (val <= 0 || val > INT_MAX)
            throw std::runtime_error("Error: value out of range: " + s);

        // Push into BOTH containers
        _vec.push_back(static_cast<int>(val));
        _deq.push_back(static_cast<int>(val));
    }

    if (_vec.empty())
        throw std::runtime_error("Error: no arguments provided");
}

// ════════════════════════════════════════════════════
//   JACOBSTHAL INSERTION ORDER
//
//   The Jacobsthal sequence: 0, 1, 1, 3, 5, 11, 21, 43 ...
//   Formula: J(n) = J(n-1) + 2 * J(n-2)
//
//   This function returns the ORDER in which we should insert
//   "pend" elements (0-indexed) into the main chain.
//
//   Instead of inserting b1, b2, b3, b4, b5 in order,
//   we insert:  b1, b3, b2, b5, b4, b11, b10, ... b6 ...
//   (b = pend element, using 1-indexed naming)
//
//   Why? Each group can be binary-searched with fewer comparisons.
// ════════════════════════════════════════════════════

std::vector<int> PmergeMe::buildInsertionOrder(int pendSize)
{
    // Build the Jacobsthal sequence until it exceeds pendSize
    std::vector<int> jacob = {0, 1};
    while (jacob.back() < pendSize)
    {
        int n = static_cast<int>(jacob.size());
        jacob.push_back(jacob[n - 1] + 2 * jacob[n - 2]);
    }

    // For each consecutive pair of Jacobsthal numbers (lo, hi),
    // insert pend indices from hi-1 DOWN to lo (high to low).
    // This is the key trick — descending within each group.
    std::vector<int> order;
    for (size_t i = 1; i < jacob.size(); i++)
    {
        // Clamp hi to the actual pend size (1-indexed)
        int hi = std::min(jacob[i], pendSize);
        int lo = jacob[i - 1];

        // Convert to 0-indexed as we add to order
        for (int k = hi - 1; k >= lo; k--)
        {
            // Skip index 0 — pend[0] (b1) is always inserted first separately
            if (k > 0)
                order.push_back(k);
        }
    }
    return order;
}

// ════════════════════════════════════════════════════
//   FORD-JOHNSON SORT — std::vector<int>
//
//   Step-by-step:
//   1. Pull out a "straggler" if the count is odd
//   2. Pair up elements, put larger first in each pair
//   3. Recursively sort only the larger (winner) elements
//   4. Re-match winners with their losers (pend)
//   5. Insert pend[0] at the front of the main chain
//   6. Insert remaining pend elements in Jacobsthal order
//      using binary search bounded by each element's partner
//   7. Insert straggler at the end
// ════════════════════════════════════════════════════

void PmergeMe::fjSortVec(std::vector<int>& arr)
{
    // Base case: 0 or 1 element is already "sorted"
    if (arr.size() <= 1)
        return;

    // ── Step 1: Handle odd element (straggler) ──────────────────
    // If there's an odd number of elements, the last one can't be
    // paired. We remove it now and reinsert it at the very end.
    bool    hasStraggler = (arr.size() % 2 != 0);
    int     straggler    = 0;
    if (hasStraggler)
    {
        straggler = arr.back();
        arr.pop_back();
    }

    // ── Step 2: Create pairs ─────────────────────────────────────
    // Walk through arr two elements at a time.
    // In each pair, the LARGER element is .first, SMALLER is .second.
    std::vector<std::pair<int, int>> pairs;
    for (size_t i = 0; i + 1 < arr.size(); i += 2)
    {
        int a = arr[i];
        int b = arr[i + 1];
        pairs.push_back(a >= b ? std::make_pair(a, b)
                               : std::make_pair(b, a));
    }

    // ── Step 3: Recursively sort the larger (winner) elements ────
    // Extract just the winners into a new vector, sort them,
    // then we'll re-match them with their losers afterward.
    std::vector<int> mainElems;
    mainElems.reserve(pairs.size());
    for (auto& p : pairs)
        mainElems.push_back(p.first);

    fjSortVec(mainElems); // ← recursive call

    // ── Step 4: Re-match winners with losers ─────────────────────
    // After sorting, mainElems is reordered. We need to find which
    // loser (second element) belongs to each winner (first element).
    // We rebuild sortedPairs in the order of sorted mainElems.
    std::vector<std::pair<int, int>> sortedPairs;
    sortedPairs.reserve(mainElems.size());
    for (int val : mainElems)
    {
        for (auto& p : pairs)
        {
            if (p.first == val)
            {
                sortedPairs.push_back(p);
                break; // assumes unique values; take first match
            }
        }
    }

    // pend[i] is always <= sortedPairs[i].first (its partner winner)
    std::vector<int> pend;
    pend.reserve(sortedPairs.size());
    for (auto& p : sortedPairs)
        pend.push_back(p.second);

    // ── Step 5: Build initial main chain ─────────────────────────
    // pend[0] is guaranteed to be <= mainElems[0] (the smallest winner),
    // so we can safely insert it at position 0 for FREE (no comparison needed).
    std::vector<int> mainChain = mainElems;
    mainChain.insert(mainChain.begin(), pend[0]);

    // ── Step 6: Insert remaining pend in Jacobsthal order ────────
    // For each index in the optimal order, we binary search pend[idx]
    // only within [begin, position_of_partner), not the whole chain.
    // This is the efficiency gain of the Jacobsthal ordering.
    std::vector<int> order = buildInsertionOrder(static_cast<int>(pend.size()));
    for (int idx : order)
    {
        // Find where pend[idx]'s partner (the winner it was paired with)
        // currently sits in mainChain. We binary search only up to there.
        auto upper    = std::find(mainChain.begin(), mainChain.end(),
                                  sortedPairs[idx].first);
        auto insertAt = std::lower_bound(mainChain.begin(), upper, pend[idx]);
        mainChain.insert(insertAt, pend[idx]);
    }

    // ── Step 7: Insert straggler ─────────────────────────────────
    // The straggler has no partner restriction, so search the full chain.
    if (hasStraggler)
    {
        auto insertAt = std::lower_bound(mainChain.begin(), mainChain.end(),
                                         straggler);
        mainChain.insert(insertAt, straggler);
    }

    // Write sorted result back into arr
    arr = mainChain;
}

// ════════════════════════════════════════════════════
//   FORD-JOHNSON SORT — std::deque<int>
//
//   Exact same logic as fjSortVec, but using std::deque.
//   The key difference: std::deque supports push_front()
//   natively (push_front vs insert at begin), which is
//   slightly more efficient for front insertions.
// ════════════════════════════════════════════════════

void PmergeMe::fjSortDeq(std::deque<int>& arr)
{
    if (arr.size() <= 1)
        return;

    // ── Step 1: Straggler ────────────────────────────────────────
    bool    hasStraggler = (arr.size() % 2 != 0);
    int     straggler    = 0;
    if (hasStraggler)
    {
        straggler = arr.back();
        arr.pop_back();
    }

    // ── Step 2: Pair up ──────────────────────────────────────────
    std::deque<std::pair<int, int>> pairs;
    for (size_t i = 0; i + 1 < arr.size(); i += 2)
    {
        int a = arr[i];
        int b = arr[i + 1];
        pairs.push_back(a >= b ? std::make_pair(a, b)
                               : std::make_pair(b, a));
    }

    // ── Step 3: Recursive sort of winners ───────────────────────
    std::deque<int> mainElems;
    for (auto& p : pairs)
        mainElems.push_back(p.first);

    fjSortDeq(mainElems); // ← recursive call

    // ── Step 4: Re-match with losers ─────────────────────────────
    std::deque<std::pair<int, int>> sortedPairs;
    for (int val : mainElems)
    {
        for (auto& p : pairs)
        {
            if (p.first == val)
            {
                sortedPairs.push_back(p);
                break;
            }
        }
    }

    std::deque<int> pend;
    for (auto& p : sortedPairs)
        pend.push_back(p.second);

    // ── Step 5: Build main chain, insert pend[0] at front ────────
    std::deque<int> mainChain = mainElems;
    mainChain.push_front(pend[0]); // deque has a native push_front!

    // ── Step 6: Insert remaining pend in Jacobsthal order ────────
    std::vector<int> order = buildInsertionOrder(static_cast<int>(pend.size()));
    for (int idx : order)
    {
        auto upper    = std::find(mainChain.begin(), mainChain.end(),
                                  sortedPairs[idx].first);
        auto insertAt = std::lower_bound(mainChain.begin(), upper, pend[idx]);
        mainChain.insert(insertAt, pend[idx]);
    }

    // ── Step 7: Insert straggler ─────────────────────────────────
    if (hasStraggler)
    {
        auto insertAt = std::lower_bound(mainChain.begin(), mainChain.end(),
                                         straggler);
        mainChain.insert(insertAt, straggler);
    }

    arr = mainChain;
}

// ════════════════════════════════════════════════════
//   RUN — sort, time, and display
//
//   std::chrono::high_resolution_clock is the most precise
//   clock available. We wrap each sort in a before/after
//   timestamp and compute the difference in microseconds.
// ════════════════════════════════════════════════════

void PmergeMe::run()
{
    // ── Print unsorted sequence ───────────────────────────────────
    std::cout << "Before:";
    for (int x : _vec)
        std::cout << " " << x;
    std::cout << "\n";

    // ── Sort + time the vector ────────────────────────────────────
    auto t1 = std::chrono::high_resolution_clock::now();
    fjSortVec(_vec);
    auto t2 = std::chrono::high_resolution_clock::now();

    // duration<double, std::micro> converts ticks to microseconds as a double
    double vecTime = std::chrono::duration<double, std::micro>(t2 - t1).count();

    // ── Sort + time the deque ─────────────────────────────────────
    auto t3 = std::chrono::high_resolution_clock::now();
    fjSortDeq(_deq);
    auto t4 = std::chrono::high_resolution_clock::now();

    double deqTime = std::chrono::duration<double, std::micro>(t4 - t3).count();

    // ── Print sorted sequence ─────────────────────────────────────
    std::cout << "After: ";
    for (int x : _vec)
        std::cout << " " << x;
    std::cout << "\n";

    // ── Print timing info ─────────────────────────────────────────
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << vecTime << " us\n";
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << deqTime << " us\n";
}
