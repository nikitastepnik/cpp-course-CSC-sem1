namespace cls10 {

    template <typename T>
    class unique_ptr {
    public:
        // Constructors
        unique_ptr() noexcept : ptr(nullptr) {}
        unique_ptr(std::nullptr_t) noexcept : ptr(nullptr) {}
        explicit unique_ptr(T* p) noexcept : ptr(p) {}

        // Destructor
        ~unique_ptr() noexcept {
            delete ptr;
        }

        // Move constructor
        unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
            other.ptr = nullptr;
        }

        // Move assignment operator
        unique_ptr& operator=(unique_ptr&& other) noexcept {
            if (this != &other) {
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        // Copy constructor (deleted)
        unique_ptr(const unique_ptr&) = delete;

        // Copy assignment operator (deleted)
        unique_ptr& operator=(const unique_ptr&) = delete;

        // Reset the pointer
        void reset() noexcept {
            delete ptr;
            ptr = nullptr;
        }

        void reset(T* p) noexcept {
            delete ptr;
            ptr = p;
        }

        // Release the ownership of the pointer
        T* release() noexcept {
            T* temp = ptr;
            ptr = nullptr;
            return temp;
        }

        // Access the stored pointer
        T* get() const noexcept {
            return ptr;
        }

        // Overload dereference operator
        T& operator*() const noexcept {
            return *ptr;
        }

        // Overload arrow operator
        T* operator->() const noexcept {
            return ptr;
        }

        // Conversion to bool
        explicit operator bool() const noexcept {
            return ptr != nullptr;
        }

    private:
        T* ptr;
    };

} // namespace cls10
