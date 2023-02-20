
#include "layer/relu_layer.hpp"
#include "ops/relu_op.hpp"
#include <glog/logging.h>
#include "factory/layer_factory.hpp"

namespace kuiper_infer
{
    ReluLayer::ReluLayer(const std::shared_ptr<Operator> &op) : Layer("Relu")
    {
        // check op type
        CHECK(op->op_type_ == OpType::kOperatorRelu) << "Operator has a wrong type: " << int(op->op_type_);

        // get op & check op
        ReluOperator *relu_op = dynamic_cast<ReluOperator *>(op.get());

        CHECK(op != nullptr) << "Relu op is null!";

        // make unique
        this->op_ = std::make_unique<ReluOperator>(relu_op->get_thresh());
    }

    void ReluLayer::Forwards(const std::vector<std::shared_ptr<Tensor<float>>> &inputs,
                             std::vector<std::shared_ptr<Tensor<float>>> &outputs)
    {
        CHECK(this->op_ != nullptr) << "Relu op is null";
        CHECK(this->op_->op_type_ == OpType::kOperatorRelu);

        const uint32_t batch_size = inputs.size();
        for (int i = 0; i < batch_size; ++i)
        {

            // check empty
            CHECK(!inputs.at(i)->empty());

            // get input ele
            const std::shared_ptr<Tensor<float>> &input_data = inputs.at(i);
            std::shared_ptr<Tensor<float>> output_data = input_data->Clone();

            // relu cal
            output_data->data().transform([&](float value)
                                          { return value >= op_->get_thresh() ? value : 0.f; });

            outputs.push_back(output_data);
        }
    }

    // 创建实例
    std::shared_ptr<Layer> ReluLayer::CreateInstance(const std::shared_ptr<Operator> &op)
    {
        std::shared_ptr<Layer> relu_layer = std::make_shared<ReluLayer>(op);
        return relu_layer;
    }

    // 注册算子
    LayerRegisterWrapper kReluLayer(OpType::kOperatorRelu, ReluLayer::CreateInstance);

}
