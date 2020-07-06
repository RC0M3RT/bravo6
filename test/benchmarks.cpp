#include <benchmark/benchmark.h>

struct param_1
{
    int a{0};
    int b{0};
};

struct param_2
{
    int c = 1 ;
    int d = 1;
};

struct system_1
{
    void update(param_1& p1, param_2& p2) {
        p1.a += p2.c;
        p1.b += p2.d;
    }
};

struct system_wrapper_1
{
    template<class S>
    system_wrapper_1(S& s) 
        : repr_{ (void*)&s }
    , update_{ [](void* r, param_1& p1, param_2& p2) -> void { (*(S*)r).update(p1, p2); } }
    {
    }

    void* repr_;

    void (*update_)(void*, param_1& p1, param_2& p2);

    void update(param_1& p1, param_2& p2) {
        update_(repr_, p1, p2);
    }

};

// --------------------

struct vtable {
    void (*update)(void* this_, param_1& p1, param_2& p2);
};

template <typename T>
vtable const vtable_for = {
    [](void* this_, param_1& p1, param_2& p2) {
        static_cast<T*>(this_)->update(p1, p2);
    }
};

class system_wrapper_2 {
    vtable const vptr_;
    void* ptr_;
public:
    template <typename Any>
    system_wrapper_2(Any s)
        : vptr_{ vtable_for<Any> }
        , ptr_{ new Any(s) }
    { }

    void update(param_1& p1, param_2& p2)
    {
        vptr_.update(ptr_, p1, p2);
    }
};

// --------------------

// --------------------

struct system_base
{
    virtual ~system_base(){}

    virtual void update(param_1& p1, param_2& p2) = 0;
};

struct system_3: system_base
{
    ~system_3() override{
    }

    void update(param_1& p1, param_2& p2) override {
        p1.a += p2.c;
        p1.b += p2.d;
    }
};

// --------------------

static void BM_system_wrapper_1(benchmark::State& state) {
    // Perform setup here

    param_1 p1;
    param_2 p2;

    std::vector<system_wrapper_1> vec;

    for (size_t i = 0; i < 100; i++)
    {
        system_1 s1;
        system_wrapper_1 sw1(s1);
        vec.emplace_back(std::move(sw1));
    }
    benchmark::DoNotOptimize(vec);
    for (auto _ : state) {
        for (auto& sw : vec) {
            sw.update(p1, p2);
        }
    }
}

static void BM_system_wrapper_2(benchmark::State& state) {
    // Perform setup here

    param_1 p1;
    param_2 p2;

    std::vector<system_wrapper_2> vec;

    for (size_t i = 0; i < 100; i++)
    {
        system_1 s1;
        system_wrapper_2 sw2(s1);
        vec.emplace_back(std::move(sw2));
    }

    benchmark::DoNotOptimize(vec);

    for (auto _ : state) {
        for (auto& sw : vec) {
            
            sw.update(p1, p2);
        }
    }
}

static void BM_intheritance_call(benchmark::State& state) {
    // Perform setup here

    param_1 p1;
    param_2 p2;

    std::vector<system_base*> vec;

    for (size_t i = 0; i < 100; i++)
    {
        system_base* sb_ = new system_3();
        vec.emplace_back(std::move(sb_));
    }
    benchmark::DoNotOptimize(vec);
    for (auto _ : state) {
        for (auto& sw : vec) {
            sw->update(p1, p2);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_system_wrapper_1);
BENCHMARK(BM_system_wrapper_2);
BENCHMARK(BM_intheritance_call);
// Run the benchmark
BENCHMARK_MAIN();

