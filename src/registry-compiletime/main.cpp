#include <iostream>
#include <array>
#include <string_view>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

template<int N>
struct RegistryTmpl{
    std::array<int,N> value_store = {};
    std::array<std::string_view, N> key_store = {};
    size_t size = N;

    // Initialize first entry
    constexpr RegistryTmpl(std::string_view k, int v){
       value_store[0] = v;
       key_store[0] = k;
    }

    // intialize and append
    constexpr RegistryTmpl(std::string_view k, int v, 
        const RegistryTmpl<N-1>& arr_cp){
        value_store[0] = v;
        key_store[0] = k;
        if(N > 1){
            for(int i=1;i<N;i++){
                value_store[i] = arr_cp.value_store[i-1];
                key_store[i] = arr_cp.key_store[i-1];
            }
        }
    }

    // Initialize by copy
    constexpr RegistryTmpl(const RegistryTmpl<N>& arr_cp){
        for(int i=0;i<N;i++){
            value_store[i] = arr_cp.value_store[i];
            key_store[i] = arr_cp.key_store[i];
        }
    }

    // Initialize by copy
    constexpr RegistryTmpl<N> operator=(const RegistryTmpl<N>& arr_cp){
        RegistryTmpl<N> tmp(arr_cp);
        return tmp;
    }

    size_t get_size(){
        return size;
    }
};

class A{
    public:
    A(){
        
    }
};

#define A_REF __COUNTER__ + 1
constexpr RegistryTmpl<A_REF> arr_A("A", 0);
#define ARR_NAME arr_A

class B{
    public:
    B(){
    
    }
};

#define B_REF __COUNTER__ + 1
constexpr RegistryTmpl<B_REF> arr_B("B", 1, ARR_NAME);
#define ARR_NAME arr_B

class C{
    public:
    C(){
    
    }
};

#define C_REF __COUNTER__ + 1
constexpr RegistryTmpl<C_REF> arr_C("C", 2, ARR_NAME);
#define ARR_NAME arr_C

constexpr static RegistryTmpl<__COUNTER__> registry = ARR_NAME;

int main(){
    static_assert(registry.size == 3);
    static_assert(registry.value_store[0] == 2);
    static_assert(registry.value_store[1] == 1);
    static_assert(registry.value_store[2] == 0);

    std::cout << "registry size = " 
              << registry.size << std::endl;
    std::cout << "===================" << std::endl;

    for(int i=0;i<registry.value_store.size();i++){
        std::cout << "val = " << registry.value_store[i] 
                  << " | key = " << registry.key_store[i] 
                  << std::endl;
    }
}