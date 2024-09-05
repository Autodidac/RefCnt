# RefCnt
## Header-Only C++20 Reference Counting Library

#### Example of Custom Reference Counting
```cpp

Here's a basic example of how you might implement custom reference counting in C++:

cpp
Copy code
#include <iostream>

class RefCounted {
public:
    RefCounted() : ref_count(0) {}

    void addRef() {
        ++ref_count;
    }

    void release() {
        if (--ref_count == 0) {
            delete this;
        }
    }

protected:
    virtual ~RefCounted() {} // Protected to prevent direct deletion

private:
    int ref_count;
};

class MyClass : public RefCounted {
public:
    void doSomething() {
        std::cout << "Doing something!" << std::endl;
    }
};

int main() {
    MyClass* obj = new MyClass();
    obj->addRef(); // Increment reference count

    MyClass* obj2 = obj; // Share ownership
    obj->addRef(); // Increment reference count

    obj->doSomething(); // Use object

    obj->release(); // Decrement reference count
    obj2->release(); // Decrement reference count and delete if count reaches zero

    return 0;
}
```
