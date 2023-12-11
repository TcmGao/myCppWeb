#ifndef SMARTBOX_LANG_NONCOPYABLE_H_
#define SMARTBOX_LANG_NONCOPYABLE_H_

namespace smartbox {

namespace noncopyable_ {

class NonCopyable {

protected:
  NonCopyable() = default;

  virtual ~NonCopyable() = default;

  NonCopyable(const NonCopyable&) = delete;

  NonCopyable &operator=(const NonCopyable&) = delete;
};

}

using NonCopyable = noncopyable_::NonCopyable;

} // namespace smartbox

#endif