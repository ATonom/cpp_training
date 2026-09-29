#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <optional>
#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdint>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

namespace rav
{
    //using std
    
    template <typename Ty>
    using TShared_Ptr = std::shared_ptr<Ty>;

    template <typename Ty>
    using TUnique_Ptr = std::unique_ptr<Ty>;
    
    template <typename T>
    using TVector = std::vector<T>;

    using String = std::string;

    template <typename T>
    using TDeque = std::deque<T>;

    using OutStream = std::ostream;
    using InStream = std::istream;

    using Mutex = std::mutex;
    using Thread = std::thread;

    using ConditionVariable = std::condition_variable;

    //using asio

    using InOutContext = asio::io_context;
    using SocketType = asio::ip::tcp::socket;
    using ResolverType = asio::ip::tcp::resolver;
    using AcceptorType = asio::ip::tcp::acceptor;

} // namespace net