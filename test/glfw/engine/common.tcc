#include <memory>

template <class Type>
std::shared_ptr<Type> MakeStrongPtr(std::weak_ptr<Type> pWeakPtr) {
    if (!pWeakPtr.expired())
        return std::shared_ptr<Type>(pWeakPtr);
    else
        return std::shared_ptr<Type>();
}

