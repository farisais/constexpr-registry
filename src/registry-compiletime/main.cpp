#include <iostream>
#include <array>
#include <string_view>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

template<typename K, typename V, int N>
struct RegistryTmpl{
    std::array<K,N> key_store = {};
    std::array<V,N> value_store = {};
    size_t size = N;

    // Initialize first entry
    constexpr RegistryTmpl(K k, V v){
       value_store[0] = v;
       key_store[0] = k;
    }

    // intialize and append
    constexpr RegistryTmpl(K k, V v, 
        const RegistryTmpl<K,V,N-1>& reg_cp){
        value_store[0] = v;
        key_store[0] = k;
        if(N > 1){
            for(int i=1;i<N;i++){
                value_store[i] = reg_cp.value_store[i-1];
                key_store[i] = reg_cp.key_store[i-1];
            }
        }
    }

    // Initialize by copy
    constexpr RegistryTmpl(const RegistryTmpl<K,V,N>& reg_cp){
        for(int i=0;i<N;i++){
            value_store[i] = reg_cp.value_store[i];
            key_store[i] = reg_cp.key_store[i];
        }
    }

    // Initialize by copy
    constexpr RegistryTmpl<K,V,N> operator=(const RegistryTmpl<K,V,N>& reg_cp) noexcept{
        RegistryTmpl<K,V,N> tmp(reg_cp);
        return tmp;
    }

    size_t get_size(){
        return size;
    }
};

typedef std::string_view K;
typedef int V;

#define A_REF __COUNTER__ + 1
constexpr RegistryTmpl<K,V,A_REF> reg_A("A", 0);
#define REG_NAME reg_A

class A{
    public:
    A(){
        std::cout << "Call from A constructor: " << std::endl;
        std::cout << "Key = " 
                  << REG_NAME.key_store[0]
                  << "| Val = " 
                  << REG_NAME.value_store[0]
                  << std::endl;
    }
};

#define B_REF __COUNTER__ + 1
constexpr RegistryTmpl<K,V,B_REF> reg_B("B", 1, REG_NAME);
#define REG_NAME reg_B

class B{
    public:
    B(){
        std::cout << "Call from B constructor: " << std::endl;
        std::cout << "Key = " 
                  << REG_NAME.key_store[0]
                  << "| Val = " 
                  << REG_NAME.value_store[0]
                  << std::endl;
    }
};

#define C_REF __COUNTER__ + 1
constexpr RegistryTmpl<K,V,C_REF> reg_C("C", 2, REG_NAME);
#define REG_NAME reg_C

class C{
    public:
    C(){
        std::cout << "Call from C constructor: " << std::endl;
        std::cout << "Key = " 
                  << REG_NAME.key_store[0]
                  << "| Val = " 
                  << REG_NAME.value_store[0]
                  << std::endl;
    }
};



constexpr static RegistryTmpl<K,V,__COUNTER__> registry = REG_NAME;

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
    std::cout << std::endl;

    A a;
    B b;
    C c;
}