#ifndef KUIPER_HW_INCLUDE_SIGMOID_LAYER_HPP_
#define KUIPER_HW_INCLUDE_SIGMOID_LAYER_HPP_
#include "layer.hpp"
#include "ops/sigmoid_op.hpp"

namespace kuiper_infer
{

    class SigmoidLayer : public Layer
    {

    private:
        std::unique_ptr<SigmoidOperator> op_;

    public:
        ~SigmoidLayer() override = default;
        explicit SigmoidLayer(const std::shared_ptr<Operator> &op);

        // Forwards
        void Forwards(const std::vector<std::shared_ptr<Tensor<float>>> &inputs,
                      std::vector<std::shared_ptr<Tensor<float>>> &outputs) override;

        static std::shared_ptr<Layer> CreateInstance(const std::shared_ptr<Operator> &op);
    };
}

#endif // KUIPER_HW_INCLUDE_SIGMOID_LAYER_HPP_