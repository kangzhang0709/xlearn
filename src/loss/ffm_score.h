//------------------------------------------------------------------------------
// Copyright (c) 2016 by contributors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//------------------------------------------------------------------------------

/*
Author: Chao Ma (mctt90@gmail.com)
This file defines the FFMScore (field-aware factorization
machine) class.
*/

#ifndef XLEARN_FFM_SCORE_FILE_SPLITER_H_
#define XLEARN_FFM_SCORE_FILE_SPLITER_H_

#include "src/base/common.h"
#include "src/loss/score_function.h"

namespace xLearn {

//------------------------------------------------------------------------------
// FFMScore is used to implemente field-aware factorization machines,
// in which the socre function is y = wTx + sum[(V_i_fj*V_j_fi)(x_i * x_j)]
//------------------------------------------------------------------------------
class FFMScore : public Score {
public:
 // Constructor and Desstructor
 FFMScore() { }
 ~FFMScore() { }

 // This function needs to be invoked before using this class.
 void Initialize(const HyperParam& hyper_param) {
   CHECK_GT(hyper_param.num_K, 0);
   CHECK_EQ(hyper_param.num_K % _MMX_INCREMENT, 0); // for sse/avx
   CHECK_GT(hyper_param.num_feature, 0);
   CHECK_GT(hyper_param.num_field, 0);
   num_factor_ = hyper_param.num_K;
   num_feature_ = hyper_param.num_feature;
   num_field_ = hyper_param.num_field;
 }

 // Given one exmaple and current model, return the score.
 real_t CalcScore(const SparseRow* row,
                  const std::vector<real_t>* w);

 private:
  index_t num_factor_;
  index_t num_feature_;
  index_t num_field_;

  DISALLOW_COPY_AND_ASSIGN(FFMScore);
};

} // namespace xLearn

#endif // XLEARN_FFM_SCORE_FILE_SPLITER_H_