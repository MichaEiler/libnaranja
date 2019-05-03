#pragma once

#include <memory>
#include <mutex>
#include <naranja/core/Exceptions.hpp>

namespace naranja
{
    namespace utils
    {
        template <typename TClass>
        class LockableResource
        {
        public:
            explicit LockableResource(const std::weak_ptr<TClass>& resource)
                : _resource(resource)
                , _mutex(std::make_shared<std::mutex>())
            {

            }

            decltype(auto) Lock() const
            {
                std::unique_lock<std::mutex> lock(*_mutex);

                auto resource = _resource.lock();
                if (!resource)
                {
                    throw naranja::core::ObjectDestroyedException();
                }

                return std::shared_ptr<TClass>(resource.get(), [resource, lock=std::move(lock)](auto*){ });
            }

        private:
            std::weak_ptr<TClass> _resource;
            std::shared_ptr<std::mutex> _mutex;
        };
    }
}