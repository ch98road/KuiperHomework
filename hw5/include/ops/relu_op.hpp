
#ifndef KUIPER_HW_INCLUDE_RELU_OPS_OP_HPP_
#define KUIPER_HW_INCLUDE_RELU_OPS_OP_HPP_
#include "op.hpp"
#include <glog/logging.h>

namespace kuiper_infer
{
    class ReluOperator : public Operator
    {
    public:
        ~ReluOperator() override = default;
        explicit ReluOperator(float thresh);
        void set_thresh(float thresh);
        float get_thresh() const;

    private:
        float thresh_ = 0.f;
    };
}

#endif // KUIPER_COURSE_INCLUDE_OPS_OP_HPP_
