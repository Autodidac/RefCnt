# RefCnt
## Header-Only C++20 Reference Counting Library




### Common Uses of Reference Counting in C++20:

std::shared_ptr: This is the most common use of reference counting in modern C++. std::shared_ptr is a smart pointer that retains ownership of an object through a reference count. When the reference count drops to zero, the object is automatically deleted.

```cpp
Copy code
#include <memory>

std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
std::shared_ptr<int> ptr2 = ptr1; // ptr1 and ptr2 share ownership

// The integer is destroyed when both ptr1 and ptr2 are out of scope

```
Custom Reference Counting: For more control or specific use cases, you might implement your own reference counting mechanism. This can be useful for certain types of resource management or optimization scenarios.


#### Example of Custom Reference Counting
Here's a basic example of how you might implement custom reference counting in C++:
```cpp
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
and that is one way of making sure you call delete and "garbage collection" in C++17 or when using a custom solution
