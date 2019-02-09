// Copyright (C) 2017 Rob Caelers <rob.caelers@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef LOOPP_CORE_HIGHRESTIMER_HPP
#define LOOPP_CORE_HIGHRESTIMER_HPP

#include <string>
#include <functional>

#include <esp_timer.h>

namespace loopp
{
  namespace core
  {
    class HighResTimer
    {
    public:
      using timer_callback = std::function<void()>;

      enum class Type
        {
         OneShot,
         Periodic
        };

      HighResTimer(const std::string &name, timer_callback callback, std::chrono::microseconds duration, Type type = Type::OneShot)
        : name(name),
          callback(callback),
          duration(duration),
          type(type)

      {
        esp_timer_create_args_t args {};
        args.callback = &on_timer;
        args.arg = this;
        args.dispatch_method = ESP_TIMER_TASK;
        args.name = this->name.c_str();

        esp_timer_create(&args, &handle);
      }

      ~HighResTimer()
      {
        cancel();
        esp_timer_delete(handle);
      }

      HighResTimer(const HighResTimer &) = delete;
      HighResTimer &operator=(const HighResTimer &) = delete;

      void start()
      {
        switch (type)
          {
          case Type::OneShot:
            esp_timer_start_once(handle, duration.count());
            break;
          case Type::Periodic:
            esp_timer_start_periodic(handle, duration.count());
            break;
          }
      }

      void cancel()
      {
        esp_timer_stop(handle);
      }


    private:
      static void on_timer(void *arg)
      {
        auto self = static_cast<HighResTimer *>(arg);
        return self->callback();
      }

    private:
      const std::string name;
      timer_callback callback;
      std::chrono::microseconds duration;
      Type type;
      esp_timer_handle_t handle = nullptr;
    };
  } // namespace core
} // namespace loopp

#endif // LOOPP_CORE_HIGHRESTIMER_HPP
