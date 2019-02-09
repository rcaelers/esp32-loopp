// Copyright (C) 2018 Rob Caelers <rob.caelers@gmail.com>
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

#ifndef LOOPP_NET_STREAM_BUFFER_HPP
#define LOOPP_NET_STREAM_BUFFER_HPP

#include <cstring>
#include <stdexcept>
#include <streambuf>
#include <vector>

namespace loopp
{
  namespace net
  {
    class StreamBuffer : public std::streambuf
    {
    public:
      explicit StreamBuffer(std::size_t max_buffer_size = DEFAULT_MAX_BUFFER_SIZE);

      std::size_t max_size() const noexcept;
      char *produce_data(std::size_t n);
      void produce_commit(std::size_t n);
      char *consume_data() const noexcept;
      std::size_t consume_size() const noexcept;
      void consume_commit(std::size_t n);

    private:
      int_type underflow();
      int_type overflow(int_type ch);
      void reserve(std::size_t n);

    private:
      std::size_t max_buffer_size;
      std::vector<char> buffer;

      static constexpr std::size_t BUFFER_INCREASE_SIZE = 100;
      static constexpr std::size_t DEFAULT_MAX_BUFFER_SIZE = 10 * 1024;
    };
  } // namespace net
} // namespace loopp

#endif // LOOPP_NET_STREAM_BUFFER_HPP
