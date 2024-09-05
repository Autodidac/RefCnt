#pragma once

#include <atomic>
#include <memory>

// Namespace for the reference counting library
namespace RefCnt {

    // Forward declaration of DefaultDeleter
    template <typename T>
    struct DefaultDeleter;

    // A generic reference-counted base class with a custom deleter
    template <typename T, typename Deleter = DefaultDeleter<T>>
    class RefCnt {
    public:
        // Constructor
        explicit RefCnt(Deleter deleter = Deleter()) noexcept
            : ref_count(0), deleter(std::move(deleter)) {}

        // Destructor is protected to prevent direct deletion
        virtual ~RefCnt() = default;

        // Increment reference count
        void addRef() const noexcept {
            ref_count.fetch_add(1, std::memory_order_relaxed);
        }

        // Decrement reference count and delete if count reaches zero
        void release() const noexcept {
            if (ref_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                deleter(static_cast<T*>(const_cast<RefCnt*>(this)));
            }
        }

    protected:
        mutable std::atomic<int> ref_count; // Atomic reference count
        Deleter deleter; // Custom deleter

    private:
        // Disable copying
        RefCnt(const RefCnt&) = delete;
        RefCnt& operator=(const RefCnt&) = delete;

        // Enable move operations
        RefCnt(RefCnt&&) noexcept = default;
        RefCnt& operator=(RefCnt&&) noexcept = default;
    };

    // Default deleter implementation
    template <typename T>
    struct DefaultDeleter {
        // Default constructor
        DefaultDeleter() noexcept = default;

        // Delete operator
        void operator()(T* ptr) const noexcept {
            delete ptr;
        }
    };

} // namespace RefCnt