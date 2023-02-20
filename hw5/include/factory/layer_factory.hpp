#ifndef KUIPER_HW_INCLUDE_FACTORY_LAYER_FACTORY_HPP_
#define KUIPER_HW_INCLUDE_FACTORY_LAYER_FACTORY_HPP_
#include "ops/op.hpp"
#include "layer/layer.hpp"

namespace kuiper_infer
{
    class LayerRegister
    {
    public:
        typedef std::shared_ptr<Layer> (*Creator)(const std::shared_ptr<Operator> &op);
        typedef std::map<OpType, Creator> CreateRegistry;

        static void RegisterCreator(OpType op_type, const Creator &creator);
        static std::shared_ptr<Layer> CreateLayer(const std::shared_ptr<Operator> &op);
        static CreateRegistry &Registry();
    };
    class LayerRegisterWrapper
    {

    public:
        LayerRegisterWrapper(OpType op_type, const LayerRegister::Creator &creator)
        {
            LayerRegister::RegisterCreator(op_type, creator);
        }
    };
}
#endif // KUIPER_HW_INCLUDE_FACTORY_LAYER_FACTORY_HPP_