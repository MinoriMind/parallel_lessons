#include <omp.h>
#include <cstdlib>
#include <thread>
#include <vector>
#include <barrier>
#include <type_traits>
#include <assert.h>

#include "functions.cpp"
#include "thread_utils.cpp"

namespace std {
    constexpr std::size_t hardware_constructive_interference_size = 64u;
    constexpr std::size_t hardware_destructive_interference_size = 64u;
}

struct partial_sum
{
    alignas(64) double Value;
};

void* Allocate(size_t Size)
{
    void* Result = malloc(Size);
    assert(Result);

    return Result;
}

void Free(void* Memory)
{
    free(Memory);
}

void* AllocateAlign(size_t Size, size_t Alignment)
{
    void* Result = aligned_alloc(Alignment, Size);
    assert(Result);

    return Result;
}

void FreeAlign(void* Memory)
{
    free(Memory);
}

#include "integration_cpp.cpp"
#include "integration_omp.cpp"
#include "reduction.cpp"
#include "experiment.cpp"


int main()
{
#if 0
    SetThreadCount(4);
    unsigned V[16];
    for(unsigned i = 0; i < std::size(V); i++)
        V[i] = i + 1;
     // std::cout << "as Average: " << '\n';
     std::cout << "Average: " << reduce_vector(V, std::size(V), [](auto x, auto y) {return x + y;}, 0u)/ std::size(V) << '\n';
     // std::cout << "Average: " << reduce_range(1, 16, 10000, Linear, [](auto x, auto y) {return x + y;}, 0) << '\n';
     // std::cout << "sdakfj: " << IntegrateReduction(-1, 1, Quadratic) << '\n;
#endif

#if 0
    SHOW_EXPERIMENT(IntegratePS);
    SHOW_EXPERIMENT(IntegrateReductionOMP);
    SHOW_EXPERIMENT(IntegrateFalseSharingOMP);
    SHOW_EXPERIMENT(IntegrateParallelOMP);
    SHOW_EXPERIMENT(IntegrateAlignOMP);
#endif
    SHOW_EXPERIMENT(IntegrateReduction);

    return 0;
}

