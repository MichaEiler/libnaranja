#pragma once

#include <cstdint>
#include <mutex>
#include <naranja/core/Exceptions.hpp>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/rpc/IServerSideService.hpp>
#include <naranja/rpc/ClientSideConnection.hpp>
#include <naranja/rpc/ServerSideConnection.hpp>
#include <naranja/utils/Disposer.hpp>
#include <naranja/utils/LockableResource.hpp>
#include <string>

{% for include in document.includes -%}
#include "{{ include.name }}.hpp"
{% endfor %}

namespace naranja
{
    namespace generated
    {
#pragma pack(push, 1)
        {%- for exception in document.exceptions %}
        class {{ exception.name }} : public naranja::core::CustomRpcException
        {
        public:
            {{ exception.name }}() : naranja::core::CustomRpcException() { }

            {%- for arg in exception.args %}
            {{ include("detail/Type.jinja2", type = arg.valueType) }} {{ arg.name }};
            {%- endfor %}
        };
        {% endfor %}

        {%- for enumeration in document.enumerations %}
        enum class {{ enumeration.name }} : std::uint32_t
        {
            {%- for name, value in enumeration.values %}
            {{ name }} = {{ value }},
            {%- endfor %}
        };
        {% endfor %}
        
        {%- for structure in document.structures %}
        struct {{ structure.name }}
        {
            {%- for arg in structure.args %}
            {{ include("detail/Type.jinja2", type = arg.valueType) }} {{ arg.name }};
            {%- endfor %}
        };
        {% endfor %}
#pragma pack(pop)

        {% for service in document.services -%}
        class I{{ service.name }}
        {
        public:
            virtual ~I{{ service.name }}() = default;
            {% for function in service.functions %}
            virtual {{ include("detail/Type.jinja2", type = function.returnType) }} {{ function.name }}({{ include("detail/Args.jinja2", args = function.args) }}) = 0;
            {%- endfor %}
            //{% for callback in service.callbacks %}
            //virtual void Set{{ callback.name }}Callback(const std::function<void({{ include("detail/Args.jinja2", args = callback.args) }})>& callback) = 0;
            //{%- endfor %}
        };

        class {{ service.name }}Protocol
        {
        public:
            {% for function in service.functions %}
            static void Write_{{ function.name }}_Request(protocol::IObjectWriter& objectWriter);
            static void Read_{{ function.name }}_Request(protocol::IObjectReader& objectReader); // TODO args
            static void Write_{{ function.name }}_Response(protocol::IObjectWriter& objectWriter);
            static void Read_{{ function.name }}_Response(protocol::IObjectReader& objectReader);
            {%- endfor %}

            {% for exception in document.exceptions %}
            static void Write_{{ exception.name }}(protocol::IObjectWriter& objectWriter);
            static void Read_{{ exception.name }}(protocol::IObjectReader& objectReader);
            {%- endfor %}

            // TODO: events/callbacks
        };

        class ServerSide{{ service.name }} : public naranja::rpc::IServerSideService, public std::enable_shared_from_this<ServerSide{{ service.name }}>
        {
        public:
            static std::shared_ptr<ServerSide{{ service.name }}> Create(const std::shared_ptr<I{{ service.name }}>& service, const std::shared_ptr<protocol::IProtocol>& protocol)
            {
                return std::shared_ptr<ServerSide{{ service.name }}>(new ServerSide{{ service.name }}(service, protocol));
            }

            void RegisterNewConnection(const std::shared_ptr<rpc::ServerSideConnection>& connection) override;
            
        private:
            explicit ServerSide{{ service.name }}const std::shared_ptr<I{{ service.name }}>& service, const std::shared_ptr<protocol::IProtocol>& protocol);

            void ConnectHandler(const std::shared_ptr<rpc::ServerSideConnection>& connection, const std::string& identifier,
                void (ServerSide{{ service.name }}::*const func)(protocol::IObjectReader&, const naranja::utils::LockableResource<naranja::streams::IBufferedOutputStream>&))
            {
                connection->RegisterFunctionCallHandler(identifier, [weakService = std::weak_ptr<ServerSide{{ service.name }}>(shared_from_this()), func](auto& object, const naranja::utils::LockableResource<naranja::streams::IBufferedOutputStream>& outputStream){
                        auto strongService = weakService.lock();
                        if (strongService)
                        {
                            auto& objectRef = *object;
                            (*strongService.*func)(objectRef, outputStream);
                        }
                    }).Clear();
            }

            {% for function in service.functions %}
            void {{ function.name }}(protocol::IObjectReader& object, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream);
            {%- endfor %}

            std::shared_ptr<protocol::IProtocol> _protocol;
            std::shared_ptr<I{{ service.name }}> _service;
        };

        class ClientSide{{ service.name }} : public I{{ service.name }}, public std::enable_shared_from_this<ClientSide{{ service.name }}>
        {
        public:
            static std::shared_ptr<ClientSide{{ service.name }}> Create(const std::shared_ptr<rpc::ClientSideConnection>& connection,
                const std::shared_ptr<protocol::IProtocol>& protocol)
            {
                return std::shared_ptr<ClientSide{{ service.name }}>(new ClientSide{{ service.name }}(connection, protocol));
            }
            
            {% for function in service.functions %}
            {{ include("detail/Type.jinja2", type = function.returnType) }} {{ function.name }}({{ include("detail/Args.jinja2", args = function.args) }}) override;
            {%- endfor %}

            //naranja::utils::Disposer OnSampleEvent(const std::function<void(const std::string& value)>& eventHandler) override;

        private:
            explicit ClientSide{{ service.name }}(const std::shared_ptr<rpc::ClientSideConnection>& connection,
                const std::shared_ptr<protocol::IProtocol>& protocol);

            std::shared_ptr<rpc::ClientSideConnection> _connection;
            std::shared_ptr<protocol::IProtocol> _protocol;

            std::mutex _eventMutex;

            //naranja::utils::Disposer _sampleEventRegistrationDisposer;
            //std::unordered_map<protocol::ObjectToken, std::function<void(const std::string&)>> _sampleEventListeners;
        };
        {% endfor %}

    }
}
