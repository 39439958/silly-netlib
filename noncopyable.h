#pragma once

namespace silly {
/**
 * @class noncopyable
 * @brief A base class to prevent derived classes from being copyable.
 * 
 * This class disables the copy constructor and copy assignment operator,
 * making any derived class non-copyable. It is intended to be used as
 * a base class to enforce non-copyable semantics in derived classes.
 * 
 */
class noncopyable {
public:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

}