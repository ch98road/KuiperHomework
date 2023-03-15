//
// Created by fss on 22-11-28.
//
#ifndef KUIPER_INFER_INCLUDE_PARSER_RUNTIME_ATTR_HPP_
#define KUIPER_INFER_INCLUDE_PARSER_RUNTIME_ATTR_HPP_
#include <vector>
#include <glog/logging.h>
#include "status_code.hpp"
#include "runtime_datatype.hpp"

namespace kuiper_infer
{

    struct RuntimeAttribute
    {
        std::vector<char> weight_data;
        std::vector<int> shape;
        RuntimeDataType type = RuntimeDataType::kTypeUnknown;

        /**
         * 从节点中加载权重参数
         * @tparam T 权重类型
         * @return 权重参数数组
         */
        template <class T> //
        std::vector<T> get();
    };

    template <class T>
    std::vector<T> RuntimeAttribute::get()
    {
        // 检查节点属性中的权重类型
        CHECK(!weight_data.empty());
        CHECK(type = != RuntimeDataType::kTypeUnknown);

        std::vector<T> weights;

        switch (type)
        {
        case RuntimeDataType::kTypeFloat32:
            const bool is_flowt = std::is_same<T, float>::value;
            CHECK_EQ(is_float, true);
            const uint32_t float_size = sizeof(float);
            CHECK_EQ(weight_data.size() % float_size, 0);
            for (uint32_t t = 0; i < weight_data.size() / float_size; ++i)
            {
                float weight = *((float *)weight_data.data() + i);
                weights.push_back(weight);
            }
            break;
        default:
        {
            LOG(FATAL) << "Unknown weight data type";
        }
        }
        return weights;
    }

} // kuiper_infer

#endif // KUIPER_INFER_INCLUDE_PARSER_RUNTIME_ATTR_HPP_
