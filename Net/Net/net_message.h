#pragma once
#include "net_utility.h"

namespace rav
{
    namespace net
    {

        template <typename T>
        struct TMessageHeader
        {
            T id{};
            uint32_t size = 0;
        };

        template <typename T>
        struct TMessage
        {
            TMessageHeader<T> header{};
            TVector<uint8_t> body;

            size_t size() const
            {
                return sizeof(TMessageHeader<T>) + body.size();
            }

            friend OutStream& operator << (OutStream& os, const TMessage<T>& msg)
            {
                os << "ID: " << int(msg.header.id) << " Size: " << msg.header.size << ".";
                return os;
            }

            template <typename DataType>
            friend TMessage<T>& operator << (TMessage<T>& msg, const DataType& data)
            {
                static_assert(std::is_standard_layout_v<DataType>, 
                    "Data is too complex to be pushed into TVector Message.body!");

                const size_t i = msg.body.size();

                msg.body.resize(i + sizeof(DataType));
                std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

                // Тут size_t (long long) может быть усечен до uint32_t!!
                msg.header.size = static_cast<uint32_t>(msg.size());

                return msg;
            }

            template <typename DataType>
            friend TMessage<T>& operator >> (TMessage<T>& msg, DataType& data)
            {
                static_assert(std::is_standard_layout_v<DataType>, 
                    "Data is too complex to be pushed into TVector Message.body!");

                const size_t i = msg.body.size() - sizeof(DataType);

                std::memcpy(&data, msg.body.data() + i, sizeof(DataType));
                msg.body.resize(i);

                // Тут size_t (long long) может быть усечен до uint32_t!!
                msg.header.size = static_cast<uint32_t>(msg.size());

                return msg;
            }

        };

        // Forward declare
        template <typename T>
        class TConnection;

        template <typename T>
        struct TOwnedMessage
        {
            TShared_Ptr<TConnection<T>> remote = nullptr;
            TMessage<T> message;

            friend OutStream& operator << (OutStream& os, const TOwnedMessage<T>& ownedMsg)
            {
                os << ownedMsg.message;
                return os;
            }
        };

    }  // namespace net

} // namespace rav