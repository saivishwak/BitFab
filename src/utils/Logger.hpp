#pragma once
/*
#include <iostream>
#include <string>
#include <thread>
#include <ctime>


namespace Utils
{
    class Logger
    {

    public:
        Logger();

        template <typename T>
        void info(T format)
        {
            std::cout << format;
        }

        template <typename T>
        void error(T format)
        {
            std::cerr << format;
        }

        template <typename T, typename... Types>
        void info(T value, Types... var)
        {
            //std::lock_guard<std::mutex> lock(mainMut);
            time_t now = time(0);
            std::string dt = Utils::Logger::trim(ctime(&now));
            std::cout << dt << " - LEVEL INFO: " << " : " << value;
            this->info(var...);
            std::cout << std::endl;
            //mainMut.unlock();
        }

        template <typename T, typename... Types>
        void error(T value, Types... var)
        {
            //std::lock_guard<std::mutex> lock(mainMut);
            time_t now = time(0);
            std::string dt = Utils::Logger::trim(ctime(&now));
            std::cout << dt << " - LEVEL ERROR: " << " : " << value ;
            this->info(var...);
            std::cout << std::endl;
            //mainMut.unlock();
        }

        static std::string trim(const std::string &s)
        {
            auto start = s.begin();
            while (start != s.end() && std::isspace(*start))
            {
                start++;
            }

            auto end = s.end();
            do
            {
                end--;
            } while (std::distance(start, end) > 0 && std::isspace(*end));

            return std::string(start, end + 1);
        };
    };
}
*/