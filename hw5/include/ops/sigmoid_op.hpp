
#ifndef KUIPER_HW_INCLUDE_SIGMOID_OPS_OP_HPP_
#define KUIPER_HW_INCLUDE_SIGMOID_OPS_OP_HPP_
#include "op.hpp"
#include <glog/logging.h>

namespace kuiper_infer
{
    class SigmoidOperator : public Operator
    {
    public:
        explicit SigmoidOperator();
    };
}

#endif // KUIPER_HW_INCLUDE_SIGMOID_OPS_OP_HPP_
