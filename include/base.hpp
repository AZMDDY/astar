#ifndef ASTAR_BASE_HPP_
#define ASTAR_BASE_HPP_
#include <iostream>

#define UNUSED(expr) (void)(expr)

#define ALOG() astar::details::LogStream() << "[E: " << __TIME__ << " " << __FILE__ << ":" << __LINE__ << "] "

namespace astar {
namespace details {
    class LogStream {
    public:
        LogStream() = default;
        LogStream(LogStream&) = delete;
        LogStream& operator=(const LogStream&) = delete;

        template<class T>
        LogStream& operator<<(T value)
        {
            data += std::to_string(value);
            return *this;
        }

        LogStream& operator<<(const std::string& value)
        {
            data += value;
            return *this;
        }

        LogStream& operator<<(const char* value)
        {
            data += value;
            return *this;
        }

        LogStream& operator<<(char* value)
        {
            data += value;
            return *this;
        }

        ~LogStream() { std::cerr << data << std::endl; }

    private:
        std::string data;
    };
}  // namespace details
}  // namespace astar

#endif  // ASTAR_BASE_HPP_