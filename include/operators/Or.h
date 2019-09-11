// Copyright 2018 The AITS DNNC Authors.All Rights Reserved.
//
// Licensed to the Apache Software Foundation(ASF) under one
// or more contributor license agreements.See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.See the License for the
// specific language governing permissionsand limitations
// under the License.
//
// This file is part of AITS DNN compiler maintained at
// https://github.com/ai-techsystems/dnnCompiler
//

#pragma once
#include "operators/baseOperator.h"
#include <string>

using namespace Eigen;

namespace dnnc {
template <typename T> class Or : public baseOperator<T> {
  //  Or attributes
public:
  Or(std::string name = "opOr") : baseOperator<T>(opOr, name) {}

  // bool getAttribute<int>(OPATTR attrName, int& obj) ;
  /*! Element wise Or-Function*/
  static bool or_function(T x, T y) { return (x || y); }

  tensor<T> compute(tensor<T> a, tensor<T> b) {

    std::vector<DIMENSION> resultShape = binaryBroadcastReShape(a, b);
    tensor<T> result(resultShape);

    if (!(this->template type_check<bool>()))
      throw std::invalid_argument(
          "Constrain input and output types to bool tensors.");

    DNNC_EIGEN_ARRAY_MAP(eigenVectorA, a);
    DNNC_EIGEN_ARRAY_MAP(eigenVectorB, b);

    DNNC_EIGEN_VECTOR_CTOR(bool) eResult;

    eResult.array() =
        eigenVectorA.array().binaryExpr(eigenVectorB.array(), &or_function);
    result.load(eResult.data());

    return result;
  }
};
} // namespace dnnc
