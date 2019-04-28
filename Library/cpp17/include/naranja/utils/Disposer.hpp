#pragma once

#include <functional>

namespace naranja
{
    namespace utils
    {
        class Disposer
        {
        public:
            explicit Disposer()
                : _action()
            {

            }

            explicit Disposer(std::function<void()>&& action)
                : _action(action)
            {

            }

            explicit Disposer(Disposer&& other)
            {
                this->operator=(std::move(other));
            }

            Disposer(const Disposer& other) = delete;

            Disposer& operator=(const Disposer& other) = delete;

            Disposer& operator=(Disposer&& other)
            {
                _action = std::move(other._action);
                other._action = std::function<void()>();
            }

            void Set(const std::function<void()>& action)
            {
                _action = action;
            }

            void Set(std::function<void()>&& action)
            {
                _action = std::move(action);
            }

            void Reset()
            {
                _action = std::function<void()>();
            }

            ~Disposer()
            {
                if (_action)
                {
                    _action();
                }
            }

        private:
            std::function<void()> _action;
        };
    }
}