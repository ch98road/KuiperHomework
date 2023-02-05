#include <armadillo>
#include <glog/logging.h>
#include <iostream>
#include <vector>

bool DEBUG = true;

arma::fcube &Padding(arma::fcube data_, const std::vector<uint32_t> &pads, float padding_value)
{
    auto channels = data_.n_slices;
    auto cols = data_.n_cols;
    auto rows = data_.n_rows;
    uint32_t pad_rows1 = pads.at(0); // up
    uint32_t pad_rows2 = pads.at(1); // bottom
    uint32_t pad_cols1 = pads.at(2); // left
    uint32_t pad_cols2 = pads.at(3); // right
    if (DEBUG)
    {
        LOG(INFO) << (cols);
        LOG(INFO) << (rows + pad_rows1 + pad_rows2);
        LOG(INFO) << pad_rows1 << " : " << pad_rows1 + rows;
    }

    arma::fcube new_cube(rows + pad_rows1 + pad_rows2, cols + pad_cols1 + pad_cols2, channels, arma::fill::value(padding_value));

    uint32_t first_row = pad_rows1;
    uint32_t last_row = pad_rows1 + rows - 1;
    uint32_t first_col = pad_cols1;
    uint32_t last_col = pad_cols1 + cols - 1;
    uint32_t first_slice = 0;
    uint32_t last_slice = channels - 1;

    new_cube.subcube(arma::span(first_row, last_row), arma::span(first_col, last_col), arma::span(first_slice, last_slice)) = data_;
    if (DEBUG)
        LOG(INFO) << "new_cube \n"
                  << new_cube;
    return new_cube;
}

int main()
{
    LOG(INFO) << "Test Armadillo Padding";
    arma::fmat in_1(4, 4, arma::fill::ones);
    arma::fmat in_2(6, 6, arma::fill::zeros);

    auto in_3 = in_2.submat(arma::span(1, 4), arma::span(1, 4));

    LOG(INFO) << "mat in_1\n"
              << in_1;
    LOG(INFO) << "mat in_2\n"
              << in_2;
    LOG(INFO) << "mat in_3\n"
              << in_3;
    in_3 = in_1;
    LOG(INFO) << "mat in_2\n"
              << in_2;

    arma::fcube data_ = arma::fcube(4, 4, 3, arma::fill::ones);
    std::vector<uint32_t> pads(4, 2);
    // Segmentation fault;
    // auto data_2 = Padding(data_, pads, 0);
    auto& data_2 = Padding(data_, pads, 0);
    // arma::fcube &data_2 = Padding(data_, pads, 2);

}