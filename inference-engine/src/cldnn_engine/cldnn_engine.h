﻿// Copyright (C) 2018-2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <map>
#include <string>
#include <memory>
#include <api/engine.hpp>
#include <cpp_interfaces/impl/ie_plugin_internal.hpp>
#include "cldnn_remote_context.h"

namespace CLDNNPlugin {

using CLDNNCustomLayerPtr = std::shared_ptr<class CLDNNCustomLayer>;

class clDNNEngine : public InferenceEngine::InferencePluginInternal,
    public gpu::details::param_map_obj_getter {
    struct impl;
    std::shared_ptr<impl> _impl;

    // key: device_id, value: cldnn device
    std::map<std::string, cldnn::device> device_map;
    std::mutex engine_mutex;

    CLDNNRemoteCLContext::Ptr m_defaultContext;

    cldnn::device_info GetDeviceInfo(const std::map<std::string, std::string> &config) const;
    InferenceEngine::ICNNNetwork::Ptr CloneAndTransformNetwork(const InferenceEngine::ICNNNetwork& network) const;
public:
    clDNNEngine();

    InferenceEngine::ExecutableNetworkInternal::Ptr LoadExeNetworkImpl(const InferenceEngine::ICNNNetwork &network,
                                                                       const std::map<std::string, std::string> &config) override;

    InferenceEngine::ExecutableNetworkInternal::Ptr LoadExeNetworkImpl(const InferenceEngine::ICNNNetwork &network,
                                                                       InferenceEngine::RemoteContext::Ptr context,
                                                                       const std::map<std::string, std::string> &config) override;

    void SetConfig(const std::map<std::string, std::string> &config) override;
    InferenceEngine::Parameter GetConfig(const std::string& name, const std::map<std::string, InferenceEngine::Parameter>& options) const override;
    InferenceEngine::Parameter GetMetric(const std::string& name, const std::map<std::string, InferenceEngine::Parameter>& options) const override;
    InferenceEngine::QueryNetworkResult QueryNetwork(const InferenceEngine::ICNNNetwork& network,
                                                     const std::map<std::string, std::string>& config) const override;

    InferenceEngine::RemoteContext::Ptr CreateContext(const InferenceEngine::ParamMap& params) override;
    InferenceEngine::RemoteContext::Ptr GetDefaultContext() override;
};

};  // namespace CLDNNPlugin
