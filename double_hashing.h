#ifndef DOUBLE_PROBING_H
#define DOUBLE_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

// Double probing implementation.
template <typename HashedObj>
class HashTableDouble
{
public:
  enum EntryType
  {
    ACTIVE,
    EMPTY,
    DELETED
  };

  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
  {
    MakeEmpty();
  }

  bool Contains(const HashedObj &x) const
  {
    return IsActive(FindPos(x));
  }

  void MakeEmpty()
  {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj &x)
  {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
    {

      return false;
    }

    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
    {
      Rehash();
    }

    return true;
  }

  bool Insert(HashedObj &&x)
  {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
    {

      return false;
    }

    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
    {
      Rehash();
    }

    return true;
  }

  bool Remove(const HashedObj &x)
  {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  /*
  * Returns # of elements in hashmap (N)
  */
  int getElementCount()
  {
    return current_size_;
  }

  /*
  * Returns the size of table (T)
  */
  int getCurrentSize()
  {
    return array_.size();
  }

  /*
  * Returns # of collisions (C)
  */
  int collisionCount()
  {
    return collisionCount_;
  }

  float theLoadFactor()
  {
    float ele = current_size_;
    float size = array_.size();
    return ele / size;
  }
  /*
  * Returns average number of collisions (M=C/N)
  */
  float averageCollisions()
  {
    float col = collisionCount_;
    float ele = current_size_;
    return col / ele;
  }

  /*
  * Set collision count to 0
  */
  int resetCollisionCount()
  {
    return collisionCount_ = 0;
  }

  /*
  * Sets R
  */
  void setR(int x)
  {
    R = x;
  }

private:
  struct HashEntry
  {
    HashedObj element_;
    EntryType info_;

    HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
        : element_{e}, info_{i} {}

    HashEntry(HashedObj &&e, EntryType i = EMPTY)
        : element_{std::move(e)}, info_{i} {}
  };

  std::vector<HashEntry> array_;
  size_t current_size_;
  /*
  * Added Variables for counting
  */
  mutable int collisionCount_ = 0;
  int R = 0;

  bool IsActive(size_t current_pos) const
  {
    return array_[current_pos].info_ == ACTIVE;
  }

  size_t FindPos(const HashedObj &x) const
  {
    size_t offset = InternalSecondHash(x);
    size_t current_pos = InternalHash(x);

    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x)
    {
      collisionCount_++;
      current_pos += offset; // Compute ith probe.
      if (current_pos >= array_.size())
        current_pos -= array_.size();
    }
    return current_pos;
  }

  /*
   *  Rehashing for quadratic probing hash table
  */
  void Rehash()
  {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto &entry : array_)
      entry.info_ = EMPTY;

    // Copy table over.
    current_size_ = 0;
    for (auto &entry : old_array)
      if (entry.info_ == ACTIVE)
        Insert(std::move(entry.element_));
  }

  size_t InternalHash(const HashedObj &x) const
  {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size();
  }

  size_t InternalSecondHash(const HashedObj &x) const
  {
    static std::hash<HashedObj> hf;
    return (R - ((hf(x) % R)) % array_.size());
  }
};

#endif // DOUBLE_PROBING_H
