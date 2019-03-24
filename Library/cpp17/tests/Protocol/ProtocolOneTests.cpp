#include <cstdint>
#include <gmock/gmock.h>
#include <memory>

#include <variant>

class ProtocolOneTestFixture : public testing::Test
{
};

TEST_F(ProtocolOneTestFixture, test1)
{
    //auto protocol = std::make_unique<Rpc2::Protocol::One::Protocol>();
    //const auto token = protocol->CreateToken();
    //auto object = protocol->WriteObject(nullptr, Rpc2::Protocol::ObjectType::FunctionCall, "Function_Foobar", token);
    //auto value = Rpc2::Protocol::ObjectValue::Reference(std::uint16_t());
    //object->WriteValue(value);
}

/*TEST_F(ProtocolOneTestFixture, stdVariant)
{
    std::variant<std::uint64_t*, std::uint32_t*, std::uint16_t*, std::uint8_t*> var;
    std::uint8_t val = 1;
    var = &val;


}*/

