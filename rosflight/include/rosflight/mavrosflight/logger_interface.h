/*
 * Software License Agreement (BSD-3 License)
 *
 * Copyright (c) 2020 Jacob Willis.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file logger_interface.h
 * @author Jacob Willis <jbwillis272@gmail.com>
 */

#ifndef MAVROSFLIGHT_LOGGER_INTERFACE_H
#define MAVROSFLIGHT_LOGGER_INTERFACE_H

#include <sstream>

#include <stdio.h>

namespace mavrosflight
{
/**
 * \class LoggerInterface
 * \brief Abstract base class for message handler
 *
 * The implementations of this class define how messages are displayed, logged,
 * etc. To create custom behavior, a derived class should implement each of the
 * public functions.
 */
template <typename Derived>
class LoggerInterface
{
public:
  template <typename... T>
  void debug(const char* format, const T&... args)
  {
    Derived& derived = static_cast<Derived&>(*this);
    derived.debug(format, args...);
  }
  template <typename... T>
  void debug_throttle(float period, const char* format, const T&... args)
  {
    Derived& derived = static_cast<Derived&>(*this);
    derived.debug_throttle(period, format, args...);
  }

  template <typename... T>
  void info(const char* format, const T&... args)
  {
    Derived& derived = static_cast<Derived&>(*this);
    derived.info(format, args...);
  }
  template <typename... T>
  void info_throttle(float period, const char* format, const T&... args)
  {
    Derived& derived = static_cast<Derived&>(*this);
    derived.info_throttle(period, format, args...);
  }

  template <typename... T>
  void warn(const char* format, const T&... args)
  {
    Derived& derived = static_cast<Derived&>(*this);
    derived.warn(format, args...);
  }
  template <typename... T>
  void warn_throttle(float period, const char* format, const T&... args)
  {
    Derived& derived = static_cast<Derived&>(*this);
    derived.warn_throttle(period, format, args...);
  }

  template <typename... T>
  void error(const char* format, const T&... args)
  {
    Derived& derived = static_cast<Derived&>(*this);
    derived.error(format, args...);
  }
  template <typename... T>
  void error_throttle(float period, const char* format, const T&... args)
  {
    Derived& derived = static_cast<Derived&>(*this);
    derived.error_throttle(period, format, args...);
  }

  template <typename... T>
  void fatal(const char* format, const T&... args)
  {
    Derived& derived = static_cast<Derived&>(*this);
    derived.fatal(format, args...);
  }
  template <typename... T>
  void fatal_throttle(float period, const char* format, const T&... args)
  {
    Derived& derived = static_cast<Derived&>(*this);
    derived.fatal_throttle(period, format, args...);
  }
};

/**
 * \class DefaultLogger
 * \brief Default logger that outputs to stdout and stderr
 */
class DefaultLogger : public LoggerInterface<DefaultLogger>
{
public:
  template <typename... T>
  inline void debug(const char* format, const T&... args)
  {
    _log(stdout, "DEBUG", format, args...);
  }
  template <typename... T>
  inline void debug_throttle(float period, const char* format, const T&... args)
  {
    debug(format, args...);
  }

  template <typename... T>
  inline void info(const char* format, const T&... args)
  {
    _log(stdout, "INFO", format, args...);
  }
  template <typename... T>
  inline void info_throttle(float period, const char* format, const T&... args)
  {
    info(format, args...);
  }

  template <typename... T>
  inline void warn(const char* format, const T&... args)
  {
    _log(stderr, "WARN", format, args...);
  }
  template <typename... T>
  inline void warn_throttle(float period, const char* format, const T&... args)
  {
    warn(format, args...);
  }

  template <typename... T>
  inline void error(const char* format, const T&... args)
  {
    _log(stderr, "ERROR", format, args...);
  }
  template <typename... T>
  inline void error_throttle(float period, const char* format, const T&... args)
  {
    error(format, args...);
  }

  template <typename... T>
  inline void fatal(const char* format, const T&... args)
  {
    _log(stderr, "FATAL", format, args...);
  }
  template <typename... T>
  inline void fatal_throttle(float period, const char* format, const T&... args)
  {
    fatal(format, args...);
  }

private:
  template <typename... T>
  inline void _log(FILE* fs, const char* name, const char* format, const T&... args)
  {
    std::stringstream ss;
    ss << "[mavrosflight][" << name << "]: " << format << std::endl;
    fprintf(fs, ss.str().c_str(), args...);
  }
};
} // namespace mavrosflight

#endif // MAVROSFLIGHT_LOGGER_INTERFACE_H