#include <armadillo>
#include <glog/logging.h>

int main(){

    LOG(INFO) << "Test Armadillo";

    arma::fmat in_1(32, 32, arma::fill::ones);

    LOG(INFO) << "in_1.n_cols:" << in_1.n_cols;
    LOG(INFO) << "in_1.n_rows:" << in_1.n_rows;
    LOG(INFO) << "in_1.size:" << in_1.size();
    
}