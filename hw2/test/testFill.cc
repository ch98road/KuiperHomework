#include <armadillo>
#include <glog/logging.h>
#include <iostream>
#include <vector>

template <typename T>
void print(const std::vector<T> &values)
{
    for (auto val : values)
    {
        // 没考虑value不能print的情况
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void Fill(arma::fcube data_, const std::vector<float> &values)
{
    auto channels = data_.n_slices;
    auto row = data_.n_rows;
    auto col = data_.n_cols;
    auto planes = data_.n_rows * data_.n_cols;

    for (uint32_t ind = 0; ind < channels; ++ind)
    {
        auto &channels_data = data_.slice(ind);
        // 相当于做了类型替换（没有复制）
        const arma::fmat &new_data = arma::fmat(values.data() + ind * planes, col, row);
        channels_data = new_data;
    }
    LOG(INFO) << "data:\n"
              << data_;
}

int main()
{

    std::vector<float> values(48, 0);
    for (uint32_t i = 0; i < values.size(); i++)
    {
        values[i] = i + 1;
    }
    print(values);
    arma::fcube data_ = arma::fcube(4, 4, 3, arma::fill::ones);
    Fill(data_, values);


}