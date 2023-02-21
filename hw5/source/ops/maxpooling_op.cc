#include "ops/maxpooling_op.hpp"
namespace kuiper_infer
{

    MaxPoolingOperator::MaxPoolingOperator(uint32_t pooling_h, uint32_t pooling_w, uint32_t stride_h, uint32_t stride_w, uint32_t padding_h, uint32_t padding_w) : Operator(OpType::kOperatorMaxpooling), pooling_h(pooling_h), pooling_w(pooling_w),
                                                                                                                                                                   stride_h(stride_h), stride_w(stride_w), padding_h(padding_h), padding_w(padding_w)
    {
    }

    void MaxPoolingOperator::set_pooling_h(uint32_t pooling_h)
    {
        this->pooling_h = pooling_h;
    }
    uint32_t MaxPoolingOperator::get_pooling_h() const
    {
        return pooling_h;
    }

    void MaxPoolingOperator::set_pooling_w(uint32_t pooling_w)
    {
        this->pooling_w = pooling_w;
    }
    uint32_t MaxPoolingOperator::get_pooling_w() const
    {
        return pooling_w;
    }

    void MaxPoolingOperator::set_stride_h(uint32_t stride_h)
    {
        this->stride_h = stride_h;
    }
    uint32_t MaxPoolingOperator::get_stride_h() const
    {
        return stride_h;
    }

    void MaxPoolingOperator::set_stride_w(uint32_t stride_w)
    {
        this->stride_w = stride_w;
    }
    uint32_t MaxPoolingOperator::get_stride_w() const
    {
        return stride_w;
    }

    void MaxPoolingOperator::set_padding_h(uint32_t padding_h)
    {
        this->padding_h = padding_h;
    }
    uint32_t MaxPoolingOperator::get_padding_h() const
    {
        return padding_h;
    }

    void MaxPoolingOperator::set_padding_w(uint32_t padding_w)
    {
        this->padding_w = padding_w;
    }
    uint32_t MaxPoolingOperator::get_padding_w() const
    {
        return padding_w;
    }

}