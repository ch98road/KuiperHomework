

#ifndef KUIPER_HW_INCLUDE_RELU_LAYER_HPP_
#define KUIPER_HW_INCLUDE_RELU_LAYER_HPP_
#include "layer.hpp"
#include "ops/relu_op.hpp"

namespace kuiper_infer
{

    class ReluLayer : public Layer
    {

    private:
        std::unique_ptr<ReluOperator> op_;

    public:
        ~ReluLayer() override = default;
        explicit ReluLayer(const std::shared_ptr<Operator> &op);

        // Forwards
        void Forwards(const std::vector<std::shared_ptr<Tensor<float>>> &inputs,
                      std::vector<std::shared_ptr<Tensor<float>>> &outputs) override;
    };
}

#endif // KUIPER_HW_INCLUDE_RELU_LAYER_HPP_