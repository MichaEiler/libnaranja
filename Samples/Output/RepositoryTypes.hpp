#pragma once

// This code is generated. It is not recommended to manually manipulate it!
// Generator: RpcTool, 0.0.0.1
// 2019-02-03 21:43:00.475334

#include <cstdint>
#include <functional>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "ExceptionTypes.hpp"


#pragma pack(push, 1)
namespace Rpc2
{
    namespace someproject
    {
        namespace Repository
        {
            enum class RepositoryChange : std::int32_t
            {
                Undefined = 0,
                EntryAdded = 1,
                EntryRemoved = 2,
            };
            
            struct Meta
            {
                std::int64_t size;
                std::int64_t creationTime;
                std::int64_t modificationTime;
            };
            
        }
    }
}
#pragma pack(pop)