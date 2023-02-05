#include "data/tensor.hpp"
#include <glog/logging.h>
#include <memory>

namespace kuiper_infer
{

    Tensor<float>::Tensor(uint32_t channels, uint32_t rows, uint32_t cols)
    {
        data_ = arma::fcube(rows, cols, channels);
    }

    Tensor<float>::Tensor(const Tensor &tensor)
    {
        this->data_ = tensor.data_;
        this->raw_shapes_ = tensor.raw_shapes_;
    }

    Tensor<float> &Tensor<float>::operator=(const Tensor &tensor)
    {
        if (this != &tensor)
        {
            this->data_ = tensor.data_;
            this->raw_shapes_ = tensor.raw_shapes_;
        }
    }

    uint32_t Tensor<float>::rows() const
    {
        CHECK(!this->data_.empty());
        return this->data_.n_rows;
    }

    uint32_t Tensor<float>::cols() const
    {
        CHECK(!this->data_.empty());
        return this->data_.n_cols;
    }

    uint32_t Tensor<float>::channels() const
    {
        CHECK(!this->data_.empty());
        return this->data_.n_slices;
    }

    uint32_t Tensor<float>::size() const
    {
        CHECK(!this->data_.empty());
        return this->data_.size();
    }

    void Tensor<float>::set_data(const arma::fcube &data)
    {
        CHECK(data.n_rows == this->data_.n_rows) << data.n_rows << "!=" << this->data_.n_rows;
        CHECK(data.n_cols == this->data_.n_cols) << data.n_cols << "!=" << this->data_.n_cols;
        CHECK(data.n_slices == this->data_.n_slices) << data.n_slices << "!=" << this->data_.n_slices;
        this->data_ = data;
    }

    bool Tensor<float>::empty() const
    {
        return this->data_.empty();
    }

    float Tensor<float>::index(uint32_t offset) const
    {
        CHECK(offset < this->data_.size());
        return this->data_.at(offset);
    }

    std::vector<uint32_t> Tensor<float>::shapes() const
    {
        CHECK(!this->data_.empty());
        return {this->channels(), this->rows(), this->cols()};
    }

    arma::fcube &Tensor<float>::data()
    {
        return this->data_;
    }

    const arma::fcube &Tensor<float>::data() const
    {
        return this->data_;
    }

    arma::fmat &Tensor<float>::at(uint32_t channel)
    {
        CHECK_LT(channel, this->channels());
        return this->data_.slice(channel);
    }

    const arma::fmat &Tensor<float>::at(uint32_t channel) const
    {
        CHECK_LT(channel, this->channels());
        return this->data_.slice(channel);
    }

    float Tensor<float>::at(uint32_t channel, uint32_t row, uint32_t col) const
    {
        CHECK_LT(channel, this->channels());
        CHECK_LT(row, this->rows());
        CHECK_LT(col, this->cols());
        return this->data_.at(row, col, channel);
    }

    float &Tensor<float>::at(uint32_t channel, uint32_t row, uint32_t col)
    {
        CHECK_LT(channel, this->channels());
        CHECK_LT(row, this->rows());
        CHECK_LT(col, this->cols());
        return this->data_.at(row, col, channel);
    }

    void Tensor<float>::Padding(const std::vector<uint32_t> &pads, float padding_value)
    {
        CHECK(!this->data_.empty());
        CHECK_EQ(pads.size(), 4);

        uint32_t pad_rows1 = pads.at(0); // up
        uint32_t pad_rows2 = pads.at(1); // bottom
        uint32_t pad_cols1 = pads.at(2); // left
        uint32_t pad_cols2 = pads.at(3); // right

        uint32_t new_row_num = pad_rows1 + pad_rows2 + this->rows();
        uint32_t col_row_num = pad_cols1 + pad_cols2 + this->cols();

        auto channel_num = this->channels();
        auto new_data_ = arma::fcube(new_row_num, col_row_num, channel_num, arma::fill::value(padding_value));
        
        for (uint32_t i = 0; i < channel_num; ++i)
        {
            // TODO: for channel, mat = mat
            auto new_slice = new_data_.slice(i);
            auto old_slice = this->data_.slice(i);
        }
    }

    /**
     *
        void Fill(float value);
        void Fill(const std::vector<float> &values);

        void Ones();
        void Rand();
        void Show();
        void Flatten();
     *
    */

}