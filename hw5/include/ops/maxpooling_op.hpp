
#ifndef KUIPER_HW_INCLUDE_MAXPOOLING_OPS_OP_HPP_
#define KUIPER_HW_INCLUDE_MAXPOOLING_OPS_OP_HPP_
#include "op.hpp"
#include <glog/logging.h>
#include <cstdint>

namespace kuiper_infer
{
    class MaxPoolingOperator : public Operator
    {
    public:
        ~MaxPoolingOperator() override = default;
        explicit MaxPoolingOperator(uint32_t pooling_h, uint32_t pooling_w, uint32_t stride_h, uint32_t stride_w, uint32_t padding_h, uint32_t padding_w);

        void set_pooling_h(uint32_t pooling_h);
        uint32_t get_pooling_h() const;

        void set_pooling_w(uint32_t pooling_w);
        uint32_t get_pooling_w() const;

        void set_stride_h(uint32_t stride_h);
        uint32_t get_stride_h() const;

        void set_stride_w(uint32_t stride_w);
        uint32_t get_stride_w() const;

        void set_padding_h(uint32_t padding_h);
        uint32_t get_padding_h() const;

        void set_padding_w(uint32_t padding_w);
        uint32_t get_padding_w() const;

    private:
        uint32_t pooling_h = 1;
        uint32_t pooling_w = 1;
        uint32_t stride_h = 1;
        uint32_t stride_w = 1;
        uint32_t padding_h = 0;
        uint32_t padding_w = 0;
    };
}

#endif // #define KUIPER_HW_INCLUDE_MAXPOOLING_OPS_OP_HPP_
