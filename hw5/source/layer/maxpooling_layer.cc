
#include "layer/maxpooling_layer.hpp"
#include "ops/maxpooling_op.hpp"
#include <glog/logging.h>
#include "factory/layer_factory.hpp"
#include <memory>

namespace kuiper_infer
{
    MaxPoolingLayer::MaxPoolingLayer(const std::shared_ptr<Operator> &op) : Layer("MaxPooling")
    {
        // check op type
        CHECK(op->op_type_ == OpType::kOperatorMaxpooling) << "Operator has a wrong type: " << int(op->op_type_);

        // get op & check op
        MaxPoolingOperator *maxpooling_op = dynamic_cast<MaxPoolingOperator *>(op.get());

        CHECK(op != nullptr) << "MaxPooling op is null!";

        // make unique
        this->op_ = std::make_unique<MaxPoolingOperator>(*maxpooling_op);
    }

    void MaxPoolingLayer::Forwards(const std::vector<std::shared_ptr<Tensor<float>>> &inputs,
                                   std::vector<std::shared_ptr<Tensor<float>>> &outputs)
    {
        CHECK(this->op_ != nullptr) << "MaxPooling op is null";
        CHECK(this->op_->op_type_ == OpType::kOperatorMaxpooling);
        CHECK(!inputs.empty());

        const uint32_t padding_h = this->op_->get_padding_h();
        const uint32_t padding_w = this->op_->get_padding_w();
        const uint32_t kernel_h = this->op_->get_pooling_h();
        const uint32_t kernel_w = this->op_->get_pooling_w();
        const uint32_t stride_h = this->op_->get_stride_h();
        const uint32_t stride_w = this->op_->get_stride_w();

        uint32_t output_h = 0;
        uint32_t output_w = 0;
        uint32_t output_c = 0;
        const uint32_t batch_size = inputs.size();

        for (int i = 0; i < batch_size; ++i)
        {
            // check empty
            CHECK(!inputs.at(i)->empty());

            // get input ele
            const std::shared_ptr<Tensor<float>> &input_data = inputs.at(i)->Clone();
            input_data->Padding({padding_h, padding_h, padding_w, padding_w}, 0);
            const uint32_t input_h = input_data->rows();
            const uint32_t input_w = input_data->cols();
            const uint32_t input_c = input_data->channels();

            if (output_h == 0 || output_w == 0)
            {
                output_h = (input_h - kernel_h) / stride_h + 1;
                output_w = (input_w - kernel_w) / stride_w + 1;
                output_c = input_c;
            }
            CHECK(output_h > 0 && output_w > 0);
            std::shared_ptr<Tensor<float>> output_data = std::make_shared<Tensor<float>>(output_c, output_h, output_w);

            LOG(INFO) << "output_h: " << output_h;
            for (uint32_t ic = 0; ic < input_c; ++ic)
            {
                const arma::fmat &input_channel = input_data->at(ic);
                arma::fmat &output_channel = output_data->at(ic);
                for (uint32_t r = 0; r < output_h; ++r)
                {
                    for (uint32_t c = 0; c < output_w; ++c)
                    {
                        const arma::fmat &region = input_channel.submat(r * stride_h, c * stride_w, r * stride_h + kernel_h - 1, c * stride_w + kernel_w - 1);
                        // LOG(INFO) << r << " " << c << "\n"
                        //           << region << region.max();
                        output_channel.at(r, c) = region.max();
                    }
                }
            }
            outputs.push_back(output_data);
        }
    }

    // 创建实例
    std::shared_ptr<Layer> MaxPoolingLayer::CreateInstance(const std::shared_ptr<Operator> &op)
    {
        std::shared_ptr<Layer> maxpooling_layer = std::make_shared<MaxPoolingLayer>(op);
        return maxpooling_layer;
    }

    // 注册算子
    LayerRegisterWrapper kMaxPoolingLayer(OpType::kOperatorMaxpooling, MaxPoolingLayer::CreateInstance);
}
