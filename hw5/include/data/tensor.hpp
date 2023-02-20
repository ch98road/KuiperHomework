#ifndef KUIPER_HW_INCLUDE_TENSOR_HPP_
#define KUIPER_HW_INCLUDE_TENSOR_HPP_

#include <armadillo>
#include <memory>
#include <vector>

namespace kuiper_infer
{

    template <typename T>
    class Tensor
    {
    }; // Tensor

    template <>
    class Tensor<uint8_t>
    {
    }; // Tensor<uint8_t>

    template <>
    class Tensor<float>
    {
    public:
        explicit Tensor() = default;
        explicit Tensor(uint32_t channels, uint32_t rows, uint32_t cols);
        Tensor(const Tensor &tensor);
        Tensor<float> &operator=(const Tensor &tensor);

        uint32_t rows() const;
        uint32_t cols() const;
        uint32_t channels() const;

        uint32_t size() const;

        void set_data(const arma::fcube &data);

        bool empty() const;
        float index(uint32_t offset) const;
        float index(uint32_t offset);

        std::vector<uint32_t> shapes() const;
        arma::fcube &data();
        const arma::fcube &data() const;

        // 返回的是一个mat，即根据channel index，返回对应channel的mat
        arma::fmat &at(uint32_t channel);
        const arma::fmat &at(uint32_t channel) const;

        // 返回的是一个float，即根据信息计算index
        float at(uint32_t channel, uint32_t row, uint32_t col) const;
        float &at(uint32_t channel, uint32_t row, uint32_t col);

        void Padding(const std::vector<uint32_t> &pads, float padding_value);

        void Fill(float value);
        void Fill(const std::vector<float> &values);

        void Ones();
        void Rand();
        void Show();
        void Flatten();

        std::shared_ptr<Tensor<float>> Clone();
    private:
        // 这玩意好像没怎么用到
        std::vector<uint32_t> raw_shapes_;
        arma::fcube data_;
    }; // Tensor<float>

} // kuiper_infer

#endif // KUIPER_HW_INCLUDE_TENSOR_HPP_