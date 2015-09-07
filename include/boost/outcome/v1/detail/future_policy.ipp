/* future_policy.ipp
Non-allocating constexpr future-promise
(C) 2015 Niall Douglas http://www.nedprod.com/
File Created: July 2015


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef BOOST_OUTCOME_FUTURE_NAME_POSTFIX
#error BOOST_OUTCOME_FUTURE_NAME_POSTFIX needs to be defined
#endif
#define BOOST_OUTCOME_GLUE2(a, b) a ## b
#define BOOST_OUTCOME_GLUE(a, b) BOOST_OUTCOME_GLUE2(a, b)
#ifndef BOOST_OUTCOME_PROMISE_NAME
#define BOOST_OUTCOME_PROMISE_NAME BOOST_OUTCOME_GLUE(promise, BOOST_OUTCOME_FUTURE_NAME_POSTFIX)
#endif
#ifndef BOOST_OUTCOME_FUTURE_NAME
#define BOOST_OUTCOME_FUTURE_NAME BOOST_OUTCOME_GLUE(future, BOOST_OUTCOME_FUTURE_NAME_POSTFIX)
#endif
#ifndef BOOST_OUTCOME_SHARED_FUTURE_NAME
#define BOOST_OUTCOME_SHARED_FUTURE_NAME BOOST_OUTCOME_GLUE(shared_, BOOST_OUTCOME_FUTURE_NAME)
#endif
#ifndef BOOST_OUTCOME_FUTURE_POLICY_NAME
#define BOOST_OUTCOME_FUTURE_POLICY_NAME BOOST_OUTCOME_GLUE(BOOST_OUTCOME_FUTURE_NAME, _policy)
#endif
#ifndef BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME
#define BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME BOOST_OUTCOME_GLUE(BOOST_OUTCOME_SHARED_FUTURE_NAME, _policy)
#endif
#ifndef BOOST_OUTCOME_FUTURE_POLICY_BASE_NAME
#define BOOST_OUTCOME_FUTURE_POLICY_BASE_NAME BOOST_OUTCOME_GLUE(BOOST_OUTCOME_FUTURE_NAME, _policy_base)
#endif
#ifndef BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME
#define BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME BOOST_OUTCOME_GLUE(BOOST_OUTCOME_SHARED_FUTURE_NAME, _policy_base)
#endif

namespace detail
{
  //! [future_policy]
  template<class future_storage, class _value_type, class error_type=void, class exception_type=void> struct BOOST_OUTCOME_FUTURE_POLICY_BASE_NAME;
  template<class future_storage, class _value_type, class error_type=void, class exception_type=void> struct BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME;

  template<typename R> struct BOOST_OUTCOME_FUTURE_POLICY_NAME
  {
    using monad_type = basic_monad<BOOST_OUTCOME_FUTURE_POLICY_NAME>;
    // In a monad policy, this is identical to monad_type. Not here.
    using implementation_type = basic_future<BOOST_OUTCOME_FUTURE_POLICY_NAME>;
    using value_type = R;
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
    using error_type = BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE;
#else
    using error_type = void;
#endif
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
    using exception_type = BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE;
#else
    using exception_type = void;
#endif
    // The wait implementation to use for waits and timed waits
    using wait_implementation = detail::stl_wait_implementation<stl11::promise<void>, stl11::future<void>>;
    // Future.get() locks, so define our own monad base type.
    using base = BOOST_OUTCOME_FUTURE_POLICY_BASE_NAME<basic_future_storage<value_type, error_type, exception_type, wait_implementation>, value_type, error_type, exception_type>;
    using other_base = BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME<basic_future_storage<value_type, error_type, exception_type, wait_implementation>, value_type, error_type, exception_type>;
    template<typename U> using rebind = basic_future<BOOST_OUTCOME_FUTURE_POLICY_NAME<U>>;
    template<typename U> using rebind_policy = BOOST_OUTCOME_FUTURE_POLICY_NAME<U>;

    // Does getting this future's state consume it?
    static constexpr bool is_consuming=true;
    // Is this future managed by shared_basic_future_ptr?
    static constexpr bool is_shared=false;
    // The type of future_errc to use for issuing errors
    using future_errc = stl11::future_errc;
    // The type of future exception to use for issuing exceptions
    using future_error = stl11::future_error;
    // The type of future status to use
    using future_status = stl11::future_status;
    // The category of error code to use
    static const stl11::error_category &future_category() noexcept { return stl11::future_category(); }
    // How many spins of yield to do waiting to be signalled before allocating a wait_implementation
    static constexpr size_t wait_spin_count = 1000;
  };
  template<typename R> struct BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME
  {
    using monad_type = basic_monad<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME>;
    // In a monad policy, this is identical to monad_type. Not here.
    using implementation_type = basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME>;
    using value_type = R;
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
    using error_type = BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE;
#else
    using error_type = void;
#endif
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
    using exception_type = BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE;
#else
    using exception_type = void;
#endif
    // The wait implementation to use for waits and timed waits
    using wait_implementation = detail::stl_wait_implementation<stl11::promise<void>, stl11::future<void>>;
    // Future.get() locks, so define our own monad base type.
    using base = BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME<basic_future_storage<value_type, error_type, exception_type, wait_implementation>, value_type, error_type, exception_type>;
    using other_base = BOOST_OUTCOME_FUTURE_POLICY_BASE_NAME<basic_future_storage<value_type, error_type, exception_type, wait_implementation>, value_type, error_type, exception_type>;
    template<typename U> using rebind = basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<U>>;
    template<typename U> using rebind_policy = BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<U>;

    // Does getting this future's state consume it?
    static constexpr bool is_consuming=false;
    // Is this future managed by shared_basic_future_ptr?
    static constexpr bool is_shared=true;
    // shared_basic_future_ptr needs to know what promise type to report
    using promise_type = basic_promise<BOOST_OUTCOME_FUTURE_POLICY_NAME<R>>;
    // The type of future_errc to use for issuing errors
    using future_errc = stl11::future_errc;
    // The type of future exception to use for issuing exceptions
    using future_error = stl11::future_error;
    // The type of future status to use
    using future_status = stl11::future_status;
    // The category of error code to use
    static const stl11::error_category &future_category() noexcept { return stl11::future_category(); }
    // How many spins of yield to do waiting to be signalled before allocating a wait_implementation
    static constexpr size_t wait_spin_count = 1000;
  };


  // Inherited from publicly by basic_monad, so whatever you expose here you expose in basic_monad
  template<class future_storage, class _value_type, class error_type, class exception_type> struct BOOST_OUTCOME_FUTURE_POLICY_BASE_NAME : public future_storage
  {
    template<class... Args> constexpr BOOST_OUTCOME_FUTURE_POLICY_BASE_NAME(Args &&... args) : future_storage(std::forward<Args>(args)...) { }
  protected:
    using implementation_type = basic_future<BOOST_OUTCOME_FUTURE_POLICY_NAME<_value_type>>;
    static BOOST_OUTCOME_FUTURE_MSVC_HELP bool _throw_error(monad_errc ec)
    {
      switch(ec)
      {
        case monad_errc::already_set:
          throw stl11::future_error(stl11::error_code(static_cast<int>(stl11::future_errc::promise_already_satisfied), stl11::future_category()));
        case monad_errc::no_state:
          throw stl11::future_error(stl11::error_code(static_cast<int>(stl11::future_errc::no_state), stl11::future_category()));
        default:
          abort();
      }
    }
    using value_type = typename std::conditional<future_storage::value_storage_type::is_referenceable, typename future_storage::value_type, _value_type>::type;
  public:
    BOOST_OUTCOME_FUTURE_MSVC_HELP typename future_storage::value_storage_type get_state() &
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      return this->_storage;
    }    
    BOOST_OUTCOME_FUTURE_MSVC_HELP typename future_storage::value_storage_type get_state() &&
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      return std::move(this->_storage);
    }    
    // Note we always return value_type by value.
    BOOST_OUTCOME_FUTURE_MSVC_HELP value_type get() &
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
#if defined(BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE) || defined(BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE)
      if(this->has_error() || this->has_exception())
      {
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
        if(this->has_error())
        {
          auto &category=this->_storage.error.category();
          //! \todo Is there any way of making which exception type to throw from an error_category user extensible? Seems daft this isn't in the STL :(
          if(category==stl11::future_category())
          {
            stl11::future_error e(this->_storage.error);
            this->clear();
            throw e;
          }
          /*else if(category==std::iostream_category())
          {
            std::ios_base::failure e(std::move(this->_storage.error));
            this->clear();
            throw e;
          }*/
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
          else
          {
            stl11::system_error e(this->_storage.error);
            this->clear();
            throw e;
          }
#endif
        }
#endif
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
        if(this->has_exception())
        {
          std::exception_ptr e(this->_storage.exception);
          this->clear();
          std::rethrow_exception(e);
        }
#endif
      }
#endif
      value_type v(std::move(this->_storage.value));
      this->clear();
      return v;
    }
    BOOST_OUTCOME_FUTURE_MSVC_HELP value_type get() && { return this->get(); }
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
    BOOST_OUTCOME_FUTURE_MSVC_HELP error_type get_error() &
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      if(this->has_error())
      {
        error_type ec(this->_storage.error);
        this->clear();
        return ec;
      }
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
      if(this->has_exception())
        return error_type((int) monad_errc::exception_present, monad_category());
#endif
      return error_type();
    }
#else
    BOOST_OUTCOME_FUTURE_MSVC_HELP error_type get_error() &;
#endif
    BOOST_OUTCOME_FUTURE_MSVC_HELP error_type get_error() && { return this->get_error(); }
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
    BOOST_OUTCOME_FUTURE_MSVC_HELP exception_type get_exception() &
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      if(!this->has_error() && !this->has_exception())
        return exception_type();
      if(this->has_error())
      {
        exception_type e(std::make_exception_ptr(stl11::system_error(this->_storage.error)));
        this->clear();
        return e;
      }
      if(this->has_exception())
      {
        exception_type e(this->_storage.exception);
        this->clear();
        return e;
      }
      return exception_type();
    }
#else
    BOOST_OUTCOME_FUTURE_MSVC_HELP exception_type get_exception() &;
#endif
    BOOST_OUTCOME_FUTURE_MSVC_HELP exception_type get_exception() && { return this->get_exception(); }
    // Makes share() available on this future.
    BOOST_OUTCOME_FUTURE_MSVC_HELP shared_basic_future_ptr<basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<_value_type>>> share()
    {
      using rettype=basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<_value_type>>;
      return shared_basic_future_ptr<rettype>(rettype(nullptr, std::move(*static_cast<implementation_type *>(this))));
    }
  };
  template<class future_storage, class error_type, class exception_type> struct BOOST_OUTCOME_FUTURE_POLICY_BASE_NAME<future_storage, void, error_type, exception_type> : public future_storage
  {
    template<class... Args> constexpr BOOST_OUTCOME_FUTURE_POLICY_BASE_NAME(Args &&... args) : future_storage(std::forward<Args>(args)...) { }
  protected:
    using implementation_type = basic_future<BOOST_OUTCOME_FUTURE_POLICY_NAME<void>>;
    static BOOST_OUTCOME_FUTURE_MSVC_HELP bool _throw_error(monad_errc ec)
    {
      switch(ec)
      {
        case monad_errc::already_set:
          throw stl11::future_error(stl11::error_code(static_cast<int>(stl11::future_errc::promise_already_satisfied), stl11::future_category()));
        case monad_errc::no_state:
          throw stl11::future_error(stl11::error_code(static_cast<int>(stl11::future_errc::no_state), stl11::future_category()));
        default:
          abort();
      }
    }
  public:
    BOOST_OUTCOME_FUTURE_MSVC_HELP typename future_storage::value_storage_type get_state() &
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      return this->_storage;
    }    
    BOOST_OUTCOME_FUTURE_MSVC_HELP typename future_storage::value_storage_type get_state() &&
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      return std::move(this->_storage);
    }    
    // Note we always return value_type by value.
    BOOST_OUTCOME_FUTURE_MSVC_HELP void get() &
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
#if defined(BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE) || defined(BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE)
      if(this->has_error() || this->has_exception())
      {
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
        if(this->has_error())
        {
          auto &category=this->_storage.error.category();
          //! \todo Is there any way of making which exception type to throw from an error_category user extensible? Seems daft this isn't in the STL :(
          if(category==stl11::future_category())
          {
            stl11::future_error e(this->_storage.error);
            this->clear();
            throw e;
          }
          /*else if(category==std::iostream_category())
          {
            std::ios_base::failure e(std::move(this->_storage.error));
            this->clear();
            throw e;
          }*/
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
          else
          {
            stl11::system_error e(this->_storage.error);
            this->clear();
            throw e;
          }
#endif
        }
#endif
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
        if(this->has_exception())
        {
          std::exception_ptr e(this->_storage.exception);
          this->clear();
          std::rethrow_exception(e);
        }
#endif
      }
#endif
      this->clear();
    }
    BOOST_OUTCOME_FUTURE_MSVC_HELP void get() && { return this->get(); }
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
    BOOST_OUTCOME_FUTURE_MSVC_HELP error_type get_error() &
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      if(this->has_error())
      {
        error_type ec(this->_storage.error);
        this->clear();
        return ec;
      }
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
      if(this->has_exception())
        return error_type((int) monad_errc::exception_present, monad_category());
#endif
      return error_type();
    }
#else
    BOOST_OUTCOME_FUTURE_MSVC_HELP error_type get_error() &;
#endif
    BOOST_OUTCOME_FUTURE_MSVC_HELP error_type get_error() && { return this->get_error(); }
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
    BOOST_OUTCOME_FUTURE_MSVC_HELP exception_type get_exception() &
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      if(!this->has_error() && !this->has_exception())
        return exception_type();
      if(this->has_error())
      {
        exception_type e(std::make_exception_ptr(stl11::system_error(this->_storage.error)));
        this->clear();
        return e;
      }
      if(this->has_exception())
      {
        exception_type e(this->_storage.exception);
        this->clear();
        return e;
      }
      return exception_type();
    }
#else
    BOOST_OUTCOME_FUTURE_MSVC_HELP exception_type get_exception() &;
#endif
    BOOST_OUTCOME_FUTURE_MSVC_HELP exception_type get_exception() && { return this->get_exception(); }
    // Makes share() available on this future.
    BOOST_OUTCOME_FUTURE_MSVC_HELP shared_basic_future_ptr<basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<void>>> share();
  };
  template<class future_storage, class _value_type, class error_type, class exception_type> struct BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME : public future_storage
  {
    template<class... Args> constexpr BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME(Args &&... args) : future_storage(std::forward<Args>(args)...) { }
  protected:
    typedef basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<_value_type>> implementation_type;
    static BOOST_OUTCOME_FUTURE_MSVC_HELP bool _throw_error(monad_errc ec)
    {
      switch(ec)
      {
        case monad_errc::already_set:
          throw stl11::future_error(stl11::error_code(static_cast<int>(stl11::future_errc::promise_already_satisfied), stl11::future_category()));
        case monad_errc::no_state:
          throw stl11::future_error(stl11::error_code(static_cast<int>(stl11::future_errc::no_state), stl11::future_category()));
        default:
          abort();
      }
    }
    // If storage is packed into a byte, it cannot be referenced
    using const_lvalue_type = typename std::conditional<future_storage::value_storage_type::is_referenceable, const typename future_storage::value_type &, _value_type>::type;
  public:
    BOOST_OUTCOME_FUTURE_MSVC_HELP typename future_storage::value_storage_type get_state() &
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      return this->_storage;
    }    
    BOOST_OUTCOME_FUTURE_MSVC_HELP typename future_storage::value_storage_type get_state() &&
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      return std::move(this->_storage);
    }    
    // Note we always return value_type by const lvalue ref.
    BOOST_OUTCOME_FUTURE_MSVC_HELP const_lvalue_type get() const
    {
      static_cast<const implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(const_cast<BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME *>(this));
      static_cast<const implementation_type *>(this)->_check_validity();
#if defined(BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE) || defined(BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE)
      if(this->has_error() || this->has_exception())
      {
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
        if(this->has_error())
        {
          auto &category=this->_storage.error.category();
          //! \todo Is there any way of making which exception type to throw from an error_category user extensible? Seems daft this isn't in the STL :(
          if(category==stl11::future_category())
          {
            stl11::future_error e(this->_storage.error);
            throw e;
          }
          /*else if(category==std::iostream_category())
          {
            std::ios_base::failure e(std::move(this->_storage.error));
            throw e;
          }*/
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
          else
          {
            stl11::system_error e(this->_storage.error);
            throw e;
          }
#endif
        }
#endif
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
        if(this->has_exception())
        {
          std::exception_ptr e(this->_storage.exception);
          std::rethrow_exception(e);
        }
#endif
      }
#endif
      return this->_storage.value;
    }
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
    BOOST_OUTCOME_FUTURE_MSVC_HELP error_type get_error() const
    {
      static_cast<const implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(const_cast<BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME *>(this));
      static_cast<const implementation_type *>(this)->_check_validity();
      if(this->has_error())
      {
        error_type ec(this->_storage.error);
        return ec;
      }
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
      if(this->has_exception())
        return error_type((int) monad_errc::exception_present, monad_category());
#endif
      return error_type();
    }
#else
    BOOST_OUTCOME_FUTURE_MSVC_HELP error_type get_error() const;
#endif
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
    BOOST_OUTCOME_FUTURE_MSVC_HELP exception_type get_exception() const
    {
      static_cast<const implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(const_cast<BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME *>(this));
      static_cast<const implementation_type *>(this)->_check_validity();
      if(!this->has_error() && !this->has_exception())
        return exception_type();
      if(this->has_error())
      {
        exception_type e(std::make_exception_ptr(stl11::system_error(this->_storage.error)));
        return e;
      }
      if(this->has_exception())
      {
        exception_type e(this->_storage.exception);
        return e;
      }
      return exception_type();
    }
#else
    BOOST_OUTCOME_FUTURE_MSVC_HELP exception_type get_exception() const;
#endif
    BOOST_OUTCOME_FUTURE_MSVC_HELP shared_basic_future_ptr<basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<_value_type>>> share() const = delete;
  };
  template<class future_storage, class error_type, class exception_type> struct BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME<future_storage, void, error_type, exception_type> : public future_storage
  {
    template<class... Args> constexpr BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME(Args &&... args) : future_storage(std::forward<Args>(args)...) { }
  protected:
    typedef basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<void>> implementation_type;
    static BOOST_OUTCOME_FUTURE_MSVC_HELP bool _throw_error(monad_errc ec)
    {
      switch(ec)
      {
        case monad_errc::already_set:
          throw stl11::future_error(stl11::error_code(static_cast<int>(stl11::future_errc::promise_already_satisfied), stl11::future_category()));
        case monad_errc::no_state:
          throw stl11::future_error(stl11::error_code(static_cast<int>(stl11::future_errc::no_state), stl11::future_category()));
        default:
          abort();
      }
    }
  public:
    BOOST_OUTCOME_FUTURE_MSVC_HELP typename future_storage::value_storage_type get_state() &
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      return this->_storage;
    }    
    BOOST_OUTCOME_FUTURE_MSVC_HELP typename future_storage::value_storage_type get_state() &&
    {
      static_cast<implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(this);
      static_cast<implementation_type *>(this)->_check_validity();
      return std::move(this->_storage);
    }    
    BOOST_OUTCOME_FUTURE_MSVC_HELP void get() const
    {
      static_cast<const implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(const_cast<BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME *>(this));
      static_cast<const implementation_type *>(this)->_check_validity();
#if defined(BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE) || defined(BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE)
      if(this->has_error() || this->has_exception())
      {
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
        if(this->has_error())
        {
          auto &category=this->_storage.error.category();
          //! \todo Is there any way of making which exception type to throw from an error_category user extensible? Seems daft this isn't in the STL :(
          if(category==stl11::future_category())
          {
            stl11::future_error e(this->_storage.error);
            throw e;
          }
          /*else if(category==std::iostream_category())
          {
            std::ios_base::failure e(std::move(this->_storage.error));
            throw e;
          }*/
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
          else
          {
            stl11::system_error e(this->_storage.error);
            throw e;
          }
#endif
        }
#endif
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
        if(this->has_exception())
        {
          std::exception_ptr e(this->_storage.exception);
          std::rethrow_exception(e);
        }
#endif
      }
#endif
    }
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
    BOOST_OUTCOME_FUTURE_MSVC_HELP error_type get_error() const
    {
      static_cast<const implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(const_cast<BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME *>(this));
      static_cast<const implementation_type *>(this)->_check_validity();
      if(this->has_error())
      {
        error_type ec(this->_storage.error);
        return ec;
      }
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
      if(this->has_exception())
        return error_type((int) monad_errc::exception_present, monad_category());
#endif
      return error_type();
    }
#else
    BOOST_OUTCOME_FUTURE_MSVC_HELP error_type get_error() const;
#endif
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
    BOOST_OUTCOME_FUTURE_MSVC_HELP exception_type get_exception() const
    {
      static_cast<const implementation_type *>(this)->wait();
      typename implementation_type::lock_guard_type h(const_cast<BOOST_OUTCOME_SHARED_FUTURE_POLICY_BASE_NAME *>(this));
      static_cast<const implementation_type *>(this)->_check_validity();
      if(!this->has_error() && !this->has_exception())
        return exception_type();
      if(this->has_error())
      {
        exception_type e(std::make_exception_ptr(stl11::system_error(this->_storage.error)));
        return e;
      }
      if(this->has_exception())
      {
        exception_type e(this->_storage.exception);
        return e;
      }
      return exception_type();
    }
#else
    BOOST_OUTCOME_FUTURE_MSVC_HELP exception_type get_exception() const;
#endif
    BOOST_OUTCOME_FUTURE_MSVC_HELP shared_basic_future_ptr<basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<void>>> share() const = delete;
  };

  template<class future_storage, class error_type, class exception_type> BOOST_OUTCOME_FUTURE_MSVC_HELP shared_basic_future_ptr<basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<void>>> BOOST_OUTCOME_FUTURE_POLICY_BASE_NAME<future_storage, void, error_type, exception_type>::share()
  {
    using rettype=basic_future<BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<void>>;
    return shared_basic_future_ptr<rettype>(rettype(nullptr, std::move(*static_cast<implementation_type *>(this))));
  }

}

//! \brief A predefined promise convenience type \ingroup future_promise
template<typename R> using BOOST_OUTCOME_PROMISE_NAME = basic_promise<detail::BOOST_OUTCOME_FUTURE_POLICY_NAME<R>>;
//! \brief A predefined future convenience type \ingroup future_promise
template<typename R> using BOOST_OUTCOME_FUTURE_NAME = basic_future<detail::BOOST_OUTCOME_FUTURE_POLICY_NAME<R>>;

#define BOOST_OUTCOME_MAKE_READY_FUTURE_NAME BOOST_OUTCOME_GLUE(make_ready_, BOOST_OUTCOME_FUTURE_NAME)
//! \brief A predefined make ready future convenience function \ingroup future_promise
template<typename R> inline BOOST_OUTCOME_FUTURE_NAME<typename std::decay<R>::type> BOOST_OUTCOME_MAKE_READY_FUTURE_NAME(R &&v)
{
  return BOOST_OUTCOME_FUTURE_NAME<typename std::decay<R>::type>(std::forward<R>(v));
}
#undef BOOST_OUTCOME_MAKE_READY_FUTURE_NAME
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
#define BOOST_OUTCOME_MAKE_READY_FUTURE_NAME BOOST_OUTCOME_GLUE(make_errored_, BOOST_OUTCOME_FUTURE_NAME)
//! \brief A predefined make errored future convenience function \ingroup future_promise
template<typename R> inline BOOST_OUTCOME_FUTURE_NAME<R> BOOST_OUTCOME_MAKE_READY_FUTURE_NAME(BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE v)
{
  return BOOST_OUTCOME_FUTURE_NAME<R>(std::move(v));
}
#undef BOOST_OUTCOME_MAKE_READY_FUTURE_NAME
#endif
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
#define BOOST_OUTCOME_MAKE_READY_FUTURE_NAME BOOST_OUTCOME_GLUE(make_exceptional_, BOOST_OUTCOME_FUTURE_NAME)
//! \brief A predefined make excepted future convenience function \ingroup future_promise
template<typename R> inline BOOST_OUTCOME_FUTURE_NAME<R> BOOST_OUTCOME_MAKE_READY_FUTURE_NAME(BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE v)
{
  return BOOST_OUTCOME_FUTURE_NAME<R>(std::move(v));
}
#undef BOOST_OUTCOME_MAKE_READY_FUTURE_NAME
#endif

//! \brief A predefined shared future convenience type \ingroup future_promise
template<typename R> using BOOST_OUTCOME_SHARED_FUTURE_NAME = shared_basic_future_ptr<basic_future<detail::BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME<R>>>;

#define BOOST_OUTCOME_MAKE_READY_FUTURE_NAME BOOST_OUTCOME_GLUE(make_ready_, BOOST_OUTCOME_SHARED_FUTURE_NAME)
//! \brief A predefined make ready shared future convenience function \ingroup future_promise
template<typename R> inline BOOST_OUTCOME_SHARED_FUTURE_NAME<typename std::decay<R>::type> BOOST_OUTCOME_MAKE_READY_FUTURE_NAME(R &&v)
{
  return BOOST_OUTCOME_SHARED_FUTURE_NAME<typename std::decay<R>::type>(std::forward<R>(v));
}
#undef BOOST_OUTCOME_MAKE_READY_FUTURE_NAME
#ifdef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
#define BOOST_OUTCOME_MAKE_READY_FUTURE_NAME BOOST_OUTCOME_GLUE(make_errored_, BOOST_OUTCOME_SHARED_FUTURE_NAME)
//! \brief A predefined make errored shared future convenience function \ingroup future_promise
template<typename R> inline BOOST_OUTCOME_SHARED_FUTURE_NAME<R> BOOST_OUTCOME_MAKE_READY_FUTURE_NAME(BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE v)
{
  return BOOST_OUTCOME_SHARED_FUTURE_NAME<R>(std::move(v));
}
#undef BOOST_OUTCOME_MAKE_READY_FUTURE_NAME
#endif
#ifdef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
#define BOOST_OUTCOME_MAKE_READY_FUTURE_NAME BOOST_OUTCOME_GLUE(make_exceptional_, BOOST_OUTCOME_SHARED_FUTURE_NAME)
//! \brief A predefined make excepted shared future convenience function \ingroup future_promise
template<typename R> inline BOOST_OUTCOME_SHARED_FUTURE_NAME<R> BOOST_OUTCOME_MAKE_READY_FUTURE_NAME(BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE v)
{
  return BOOST_OUTCOME_SHARED_FUTURE_NAME<R>(std::move(v));
}
#undef BOOST_OUTCOME_MAKE_READY_FUTURE_NAME
#endif

#undef BOOST_OUTCOME_FUTURE_NAME_POSTFIX
#undef BOOST_OUTCOME_GLUE
#undef BOOST_OUTCOME_PROMISE_NAME
#undef BOOST_OUTCOME_FUTURE_NAME
#undef BOOST_OUTCOME_SHARED_FUTURE_NAME
#undef BOOST_OUTCOME_FUTURE_POLICY_NAME
#undef BOOST_OUTCOME_SHARED_FUTURE_POLICY_NAME
#undef BOOST_OUTCOME_FUTURE_POLICY_ERROR_TYPE
#undef BOOST_OUTCOME_FUTURE_POLICY_EXCEPTION_TYPE
