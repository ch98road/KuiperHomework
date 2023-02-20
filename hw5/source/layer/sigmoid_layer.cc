#include "layer/sigmoid_layer.hpp"
#include "ops/sigmoid_op.hpp"
#include <glog/logging.h>
#include "factory/layer_factory.hpp"

namespace kuiper_infer
{
    SigmoidLayer::SigmoidLayer(const std::shared_ptr<Operator> &op) : Layer("Sigmoid")
    {
        // check op type
        CHECK(op->op_type_ == OpType::kOperatorSigmoid) << "Operator has a wrong type: " << int(op->op_type_);
        // get op & check op
        SigmoidOperator *sigmoid_op = dynamic_cast<SigmoidOperator *>(op.get());

        CHECK(op != nullptr) << "Sigmoid op is null";

        // make unique
        this->op_ = std::make_unique<SigmoidOperator>();
    }

    void SigmoidLayer::Forwards(const std::vector<std::shared_ptr<Tensor<float>>> &inputs,
                                std::vector<std::shared_ptr<Tensor<float>>> &outputs)
    {
        CHECK(this->op_ != nullptr) << "Sigmoid Layer is null";
        CHECK(this->op_->op_type_ == OpType::kOperatorSigmoid);

        const uint32_t batch_size = inputs.size();
        for (int i=0; i<batch_size; ++i){

            // check empty
            CHECK(!inputs.at(i)->empty());

            // get input ele
            const std::shared_ptr<Tensor<float>> &input_data = inputs.at(i);
            
            // 应该是要有个复制的过程，不然就是会出现某些不知名bug，比如输入重用之类的
            std::shared_ptr<Tensor<float>> output_data = input_data->Clone();
            // sigmoid cal
            output_data->data().transform([&](float value){
                return 1 / (1 + std::exp(-value)); 
            });
            outputs.push_back(output_data);


            // // sigmoid cal
            // input_data->data().transform([&](float value){
            //     LOG(INFO) << 1 / (1 + std::exp(-value));
            //     return 1 / (1 + std::exp(-value)); 
            // });
            // outputs.push_back(input_data);
        }

    }

    // create instance 
    std::shared_ptr<Layer> SigmoidLayer::CreateInstance(const std::shared_ptr<Operator> &op){
        std::shared_ptr<Layer> sigmoid_layer = std::make_shared<SigmoidLayer>(op);
        return sigmoid_layer;
    }


    // regist layer 
    LayerRegisterWrapper kSigmoidLayer(OpType::kOperatorSigmoid, SigmoidLayer::CreateInstance);

}
