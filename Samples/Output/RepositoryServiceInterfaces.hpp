#pragma once

// This code is generated. It is not recommended to manually manipulate it!
// Generator: RpcTool, 0.0.0.1
// 2019-02-03 21:43:00.307880

#include <cstdint>
#include <functional>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "ExceptionTypes.hpp"
#include "RepositoryTypes.hpp"


namespace Rpc2
{
    namespace someproject
    {
        namespace Repository
        {
            class IRepositoryService
            {
            public:
                virtual ~IRepositoryService() = default;
                
                virtual std::int64_t Open(const std::string& repositoryName) = 0;
                virtual std::vector<char> GetEntry(const std::int64_t& instance, const std::string& name) = 0;
                virtual Meta GetEntryMeta(const std::int64_t& instance, const std::string& name) = 0;
                virtual bool HasEntry(const std::int64_t& instance, const std::string& name) = 0;
                virtual void AddEntry(const std::int64_t& instance, const std::string& name, const std::vector<char>& data) = 0;
                virtual void RemoveEntry(const std::int64_t& instance, const std::string& name) = 0;
                virtual void Close(const std::int64_t& instance) = 0;
                
                virtual void SetOnRepositoryChangedCallback(const std::function<void(const std::int64_t& instance, const RepositoryChange& change, const std::string& name)>& callback) = 0;
            };
            
        }
    }
}