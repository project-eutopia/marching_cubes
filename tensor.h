#pragma once

#include <limits>
#include <vector>
#include <iostream>
#include <functional>

#include "size.h"
#include "point.h"

template <typename T, size_t N>
class Tensor {
  static_assert(N >= 1, "N must be at least 1 for Tensor");

  public:
    using size_type            = Size<size_t,N>;
    using index_type           = Point<size_t,N>;
    using reference_type       = typename std::vector<T>::reference;
    using const_reference_type = typename std::vector<T>::const_reference;

  private:
    const size_type size_;
    std::vector<T> data_;

    mutable bool min_max_calculated_;
    mutable T min_, max_;

  public:
    explicit Tensor(size_type size)                : size_(size), data_(size.prod()),       min_max_calculated_(false) {}
    explicit Tensor(size_type size, const T& fill) : size_(size), data_(size.prod(), fill), min_max_calculated_(false) {}

    Tensor<T,N>& transform(const std::function<T(T)> f) {
      for (const auto& index : size_) {
        transformed(index) = f((*this)(index));
      }
      return *this;
    }

    template <typename U>
    Tensor<U,N> transformed(const std::function<U(T)> f) const {
      Tensor<U,N> transformed(size_);

      for (const auto& index : size_) {
        transformed(index) = f((*this)(index));
      }

      return transformed;
    }

    // Value at absolute index (or regular index if 1D)
    const_reference_type operator()(size_t i) const {
      return data_[i];
    }
    reference_type operator()(size_t i) {
      return data_[i];
    }

    const_reference_type operator()(size_t i, size_t j) const {
      static_assert(N == 2, "Cannot call operator() with 2 argument unless N == 2");
      return data_[i + size_(0)*j];
    }
    reference_type operator()(size_t i, size_t j) {
      static_assert(N == 2, "Cannot call operator() with 2 argument unless N == 2");
      return data_[i + size_(0)*j];
    }

    const_reference_type operator()(size_t i, size_t j, size_t k) const {
      static_assert(N == 3, "Cannot call operator() with 3 argument unless N == 3");
      return data_[i + size_(0)*j];
    }
    reference_type operator()(size_t i, size_t j, size_t k) {
      static_assert(N == 3, "Cannot call operator() with 3 argument unless N == 3");
      return data_[i + size_(0)*j + size_(0)*size_(1)*k];
    }

    const_reference_type operator()(size_t i, size_t j, size_t k, size_t l) const {
      static_assert(N == 4, "Cannot call operator() with 4 argument unless N == 4");
      return data_[i + size_(0)*j + size_(0)*size_(1)*k + size_(0)*size_(1)*size_(2)*l];
    }
    reference_type operator()(size_t i, size_t j, size_t k, size_t l) {
      static_assert(N == 4, "Cannot call operator() with 4 argument unless N == 4");
      return data_[i + size_(0)*j + size_(0)*size_(1)*k + size_(0)*size_(1)*size_(2)*l];
    }

    const_reference_type operator()(const index_type& index) const {
      return data_[size_.absolute_index_for(index)];
    }

    reference_type operator()(const index_type& index) {
      return data_[size_.absolute_index_for(index)];
    }

    template <typename ... Args>
    const_reference_type operator()(const Args& ... args) const {
      static_assert(sizeof...(args) == N, "Variable argument pack size in operator() must match N");
      return data_[size_.absolute_index_for(index_type(args...))];
    }

    template <typename ... Args>
    reference_type operator()(const Args& ... args) {
      static_assert(sizeof...(args) == N, "Variable argument pack size in operator() must match N");
      return data_[size_.absolute_index_for(index_type(args...))];
    }

    std::ostream& write_to_numpy(std::ostream& os) const {
      for (const auto& val : *this) {
        os.write(reinterpret_cast<const char*>(&val), sizeof(val));
      }
      return os;
    }

    std::istream& read_from_numpy(std::istream& is) {
      for (auto& val : *this) {
        is.read(reinterpret_cast<char*>(&val), sizeof(val));
      }
      return is;
    }

    T min() const {
      calculate_min_max();
      return min_;
    }

    T max() const {
      calculate_min_max();
      return min_;
    }

    const size_type& size() const { return size_; }

    auto begin()       { return data_.begin(); }
    auto begin() const { return data_.begin(); }
    auto end()         { return data_.end();   }
    auto end()   const { return data_.end();   }

  private:
    void calculate_min_max() const {
      if (min_max_calculated_) return;

      min_ = std::numeric_limits<T>::max();
      max_ = std::numeric_limits<T>::min();

      for (const auto& val : *this) {
        if (val < min_) min_ = val;
        if (val > max_) max_ = val;
      }

      min_max_calculated_ = true;
    }
};
