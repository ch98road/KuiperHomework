#include "data/tensor.hpp"
#include <glog/logging.h>
#include <memory>

namespace kuiper_infer
{

    Tensor<float>::Tensor(uint32_t channels, uint32_t rows, uint32_t cols)
    {
        this->data_ = arma::fcube(rows, cols, channels);
        this->raw_shapes_ = std::vector<uint32_t>{rows, cols, channels};
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
        return *this;
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

    float Tensor<float>::index(uint32_t offset)
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
        uint32_t new_col_num = pad_cols1 + pad_cols2 + this->cols();

        auto channel_num = this->channels();
        auto new_data_ = arma::fcube(new_row_num, new_col_num, channel_num, arma::fill::value(padding_value));

        uint32_t first_row = pad_rows1;
        uint32_t last_row = pad_rows1 + this->rows() - 1;
        uint32_t first_col = pad_cols1;
        uint32_t last_col = pad_cols1 + this->cols() - 1;
        uint32_t first_slice = 0;
        uint32_t last_slice = this->channels() - 1;

        new_data_.subcube(arma::span(first_row, last_row), arma::span(first_col, last_col), arma::span(first_slice, last_slice)) = this->data_;
        this->data_ = std::move(new_data_);
        this->raw_shapes_ = std::vector<uint32_t>{new_row_num, new_col_num, channel_num};
    }
    void Tensor<float>::Fill(float value)
    {
        CHECK(!this->data_.empty());
        this->data_.fill(value);
    }

    void Tensor<float>::Fill(const std::vector<float> &values)
    {
        // 只能用slice
        CHECK(!this->data_.empty());
        const uint32_t total_elems = this->data_.size();
        CHECK_EQ(values.size(), total_elems);

        const uint32_t rows = this->rows();
        const uint32_t cols = this->cols();
        const uint32_t planes = rows * cols;
        const uint32_t channels = this->channels();

        for (uint32_t i = 0; i < channels; ++i)
        {
            auto &channels_data = this->data_.slice(i);
            /**
             * 此处是因为arma填充的时候是col优先，
             * 所以要得到(row, col)的mat，需要先构造(col, row)然后列优先填充，
             * 最后.t()转置得到正确的结果
             **/
            const arma::fmat &new_data = arma::fmat(values.data() + i * planes, cols, rows).t();
            channels_data = new_data;
        }
    }

    void Tensor<float>::Ones()
    {
        CHECK(!this->data_.empty());
        this->Fill(1.);
    }

    void Tensor<float>::Rand()
    {
        CHECK(!this->data_.empty());
        this->data_.randn();
    }

    void Tensor<float>::Show()
    {
        LOG(INFO) << "\n"
                  << this->data_;
    }

    void Tensor<float>::Flatten()
    {
        CHECK(!this->data_.empty());
        const uint32_t size = this->data_.size();
        arma::fcube linear_cube = arma::reshape(this->data_, size, 1, 1);
        this->data_ = std::move(linear_cube);
        this->raw_shapes_ = std::vector<uint32_t>{size};
    }

}