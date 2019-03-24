#pragma once

// This code is generated. It is not recommended to manually manipulate it!
// Generator: RpcTool, 0.0.0.1
// 2019-02-03 21:43:00.499462

#include <cstdint>
#include <functional>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>



#pragma pack(push, 1)
namespace Rpc2
{
    namespace someproject
    {
        namespace Exception
        {
            class InvalidOperationException : public std::exception
            {
            public:
                std::string description;
            };
            
            class InvalidArgumentException : public std::exception
            {
            public:
                std::string description;
            };
            
            class UnexpectedErrorException : public std::exception
            {
            public:
                std::string description;
            };
            
        }
    }
}
#pragma pack(pop)