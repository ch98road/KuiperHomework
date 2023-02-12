

#ifndef KUIPER_HW_INCLUDE_LAYER_HPP_
#define KUIPER_HW_INCLUDE_LAYER_HPP_

#include <string>
#include "data/tensor.hpp"

namespace kuiper_infer
{

    class Layer
    {
    private:
        std::string layer_name_;

    public:
        explicit Layer(const std::string &layer_name);

        virtual void Forwards(const std::vector<std::shared_ptr<Tensor<float>>> &inputs,
                              std::vector<std::shared_ptr<Tensor<float>>> &outputs);

        virtual ~Layer() = default;
    };

}

#endif // KUIPER_HW_INCLUDE_LAYER_HPP_