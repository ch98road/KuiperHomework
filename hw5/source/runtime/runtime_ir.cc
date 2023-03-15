
#include "runtime/runtime_ir.hpp"
#include <memory>
#include <iostream>
#include <iomanip>
#include <queue>
#include <deque>
#include <utility>
#include "factory/layer_factory.hpp"

namespace kuiper_infer
{

    // RuntimeGraph::

    RuntimeGraph::RuntimeGraph(std::string param_path, std::string bin_path) : param_path_(param_path), bin_path_(bin_path)
    {
    }

    void RuntimeGraph::set_bin_path(const std::string &bin_path) { this->bin_path_ = bin_path; }

    void RuntimeGraph::set_param_path(const std::string &param_path) { this->param_path_ = param_path; }

    const std::string &RuntimeGraph::param_path() const
    {
        return this->param_path_;
    }

    const std::string &RuntimeGraph::bin_path() const
    {
        return this->bin_path_;
    }

    bool RuntimeGraph::Init()
    {
        // check path
        if (this->bin_path_.empty() || this->param_path_.empty())
        {
            LOG(ERROR) << "The bin path or param path is empty";
            return false;
        }

        // load graph
        this->graph_ = std::make_unique<pnnx::Graph>();
        int load_result = this->graph_->load(param_path_, bin_path_);
        if (load_result != 0)
        {
            LOG(ERROR) << "Load param path and bin path error: " << param_path_ << " " << bin_path_;
            return false;
        }

        // load ops
        std::vector<pnnx::Operator *> operators = this->graph_->ops;
        if (operators.empty())
        {
            LOG(ERROR) << "Can not read the layers' define";
            return false;
        }

        this->operators_.clear();
        // TODO：
        // 根据const pnnx::Operator *op 去赋值std::shared_ptr<RuntimeOperator> runtime_operator
        graph_state_ = GraphState::NeedBuild;
        return true;
    }

} // kuiper_infer