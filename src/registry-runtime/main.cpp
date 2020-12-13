#include <map>
#include <iostream>
#include <typeindex>

class Registry final{
    typedef std::map<std::type_index, int> storage_;
    public:
    static storage_& registry(){
        static storage_ *reg = new storage_();
        return *reg;
    }

    static void add_something(std::type_index t, int val){
        storage_& reg = registry();
        reg[t] = val;
    }

    static int get_something(std::type_index t){
        storage_& reg = registry();
        return reg[t];
    }

    private:
    Registry(){};
};

class RegistryGen{
    public:
    RegistryGen(std::type_index t, int val){
        Registry::add_something(t, val);
    }
};

class A{
    public:
    A(){
        std::cout << "Something is = " 
                  << Registry::get_something(typeid(*this)) 
                  << std::endl;
    }
};

static RegistryGen gen_A_logger(typeid(A), 10);

int main(){
    A a;
}