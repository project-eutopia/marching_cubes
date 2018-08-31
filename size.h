#pragma once

#include "point.h"

#include <array>
#include <type_traits>

template <typename T, size_t N>
class Size {
  static_assert(std::is_unsigned<T>::value, "Size must be of unsigned type");

  public:
    using value_type = T;
    using index_type = Point<T,N>;

  private:
    index_type sizes_;

  public:
    class const_iterator {
      public:
        using reference = const index_type&;

      private:
        const_iterator(const Size& size, const index_type& index)
          : size_(size), index_(index)
        {}

      public:
        static const_iterator begin(const Size& size) {
          index_type index;
          for (size_t i = 0; i < N; ++i) index(0) = 0;
          return const_iterator(size, index);
        }

        static const_iterator end(const Size& size) {
          index_type index;
          for (size_t i = 0; i < N-1; ++i) index(0) = 0;
          index(N-1) = size(N-1);
          return const_iterator(size, index);
        }

        const_iterator& operator++() {
          for (size_t i = 0; i < N-1; ++i) {
            if (index_(i) < size_(i)-1) {
              ++index_(i);
              return *this;
            }
            else {
              index_(i) = 0;
            }
          }

          // On last index, always increment so we can detect overflow outside of size
          ++index_(N-1);
          return *this;
        }

        const_iterator operator++(int) {
          const_iterator tmp(*this);
          operator++();
          return tmp;
        }

        reference operator*() {
          return index_;
        }

        bool operator==(const const_iterator& rhs) const { return index_ == rhs.index_; }
        bool operator!=(const const_iterator& rhs) const { return index_ != rhs.index_; }

      private:
        const Size& size_;
        index_type index_;
    };

    class iterator {
      public:
        using reference = index_type&;

      private:
        iterator(const Size& size, const index_type& index)
          : size_(size), index_(index)
        {}

      public:
        static iterator begin(const Size& size) {
          index_type index;
          for (size_t i = 0; i < N; ++i) index(0) = 0;
          return iterator(size, index);
        }

        static iterator end(const Size& size) {
          index_type index;
          for (size_t i = 0; i < N-1; ++i) index(0) = 0;
          index(N-1) = size(N-1);
          return iterator(size, index);
        }

        iterator& operator++() {
          for (size_t i = 0; i < N-1; ++i) {
            if (index_(i) < size_(i)-1) {
              ++index_(i);
              return *this;
            }
            else {
              index_(i) = 0;
            }
          }

          // On last index, always increment so we can detect overflow outside of size
          ++index_(N-1);
          return *this;
        }

        iterator operator++(int) {
          iterator tmp(*this);
          operator++();
          return tmp;
        }

        reference operator*() {
          return index_;
        }

        bool operator==(const iterator& rhs) const { return index_ == rhs.index_; }
        bool operator!=(const iterator& rhs) const { return index_ != rhs.index_; }

      private:
        const Size& size_;
        index_type index_;
    };

    template <typename ... Args>
    constexpr Size(const Args& ... args) : sizes_{args...} {}

    const T& operator()(size_t i) const { return sizes_[i]; }
    T&       operator()(size_t i)       { return sizes_[i]; }
    const T& operator[](size_t i) const { return sizes_[i]; }
    T&       operator[](size_t i)       { return sizes_[i]; }

    auto begin() const { return const_iterator::begin(*this); }
    auto end()   const { return const_iterator::end(*this); }
    auto begin()       { return iterator::begin(*this); }
    auto end()         { return iterator::end(*this); }

    auto operator+=(const Size<T,N>& rhs) { sizes_ += rhs.sizes_; return *this; }
    auto operator-=(const Size<T,N>& rhs) { sizes_ -= rhs.sizes_; return *this; }

    auto operator+(const Size<T,N>& rhs) { return Size<T,N>(sizes_ + rhs.sizes_); }
    auto operator-(const Size<T,N>& rhs) { return Size<T,N>(sizes_ - rhs.sizes_); }

    T prod() const {
      return sizes_.prod();
    }

    T absolute_index_for(const index_type& index) const {
      T i = index(0);

      for (T j = 1; j < N; ++j) {
        T factor = 1;
        for (T k = 0; k < j; ++k) {
          factor *= sizes_(k);
        }
        i += factor * index(j);
      }

      return i;
    }
};

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const Size<T,N>& s) {
  os << s.size_;
  return os;
}
