
#ifndef KUIPER_HW_INCLUDE_OPS_OP_HPP_
#define KUIPER_HW_INCLUDE_OPS_OP_HPP_

namespace kuiper_infer
{

    enum class OpType
    {
        kOperatorUnknown = -1,
        kOperatorRelu = 0,
        kOperatorSigmoid = 1,
        kOperatorMaxpooling = 2,
    };

    class Operator
    {
    public:
        OpType op_type_ = OpType::kOperatorUnknown;

        virtual ~Operator() = default;

        explicit Operator(OpType op_type_);
    };
}

#endif // KUIPER_HW_INCLUDE_OPS_OP_HPP_
