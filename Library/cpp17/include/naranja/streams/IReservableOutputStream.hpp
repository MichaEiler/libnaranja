#pragma once

#include <memory>

namespace naranja
{
    namespace streams
    {
        class IBufferedOutputStream;

        class IReservableOutputStream
        {
        public:
            virtual ~IReservableOutputStream() = default;

            virtual std::shared_ptr<IBufferedOutputStream> Reserve() = 0;
        };
    }
}