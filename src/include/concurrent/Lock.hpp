#ifndef SMARTBOX_CONCURRENT_LOCK_H_
#define SMARTBOX_CONCURRENT_LOCK_H_

#include "lang/noncopyable.h"
#include <errno.h>
#include <pthread.h>

namespace smartbox {

class MutexLock : NonCopyable {
public:
  MutexLock() { pthread_mutex_init(&lock_, nullptr); }

  ~MutexLock() { pthread_mutex_destroy(&lock_); }

  void Lock() const { pthread_mutex_lock(&lock_); }

  bool TryLock() const {
    int rc = pthread_mutex_trylock(&lock_);
    if (rc == 0) {
      return true;
    } else if (rc == EBUSY) {
      return false;
    }
    // error
    return false;
  }

  void Unlock() const { pthread_mutex_unlock(&lock_); }

private:
  mutable pthread_mutex_t lock_;
};

class ReentrantLock : NonCopyable {
public:
  ReentrantLock() { 
    pthread_mutexattr_init(&attr_);
    pthread_mutexattr_settype(&attr_, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&lock_, &attr_);
  }

  ~ReentrantLock() {
    pthread_mutex_destroy(&lock_);
    pthread_mutexattr_destroy(&attr_);
  }

  void Lock() const { pthread_mutex_lock(&lock_); }

  bool TryLock() const {
    int rc = pthread_mutex_trylock(&lock_);
    if (rc == 0) {
      return true;
    } else if (rc == EBUSY) {
      return false;
    }
    // error
    return false;
  }

  void Unlock() const { pthread_mutex_unlock(&lock_); }

private:
  mutable pthread_mutex_t lock_;
  pthread_mutexattr_t attr_;
};

template <typename T> 
class LockGuard : NonCopyable {
public:
  explicit LockGuard(T &lock, bool try_lock = false)
      : lock_(lock), locked_(true) {
    if (try_lock) {
      locked_ = lock_.tryLock();
    } else {
      lock_.Lock();
    }
  }

  ~LockGuard() {
    if (locked_) {
      lock_.UnLock();
    }
  }

private:
  T &lock_;
  bool locked_;
};


} // namespace smartbox

#endif