// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
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

#pragma once

#include "lite/core/context.h"
#include "lite/core/target_wrapper.h"
#include "lite/operators/op_params.h"

namespace paddle {
namespace lite {
namespace arm {
namespace math {
namespace fp16 {
typedef __fp16 float16_t;
#define IM2COL_PARAM(dtype)                                                   \
  const dtype *data_im, int channels, int height, int width, int kernel_h,    \
      int kernel_w, int pad_top, int pad_bottom, int pad_left, int pad_right, \
      int dilation_h, int dilation_w, dtype *data_col

#define CONV_PARAM(dtype)                                                      \
  const dtype *i_data, dtype *o_data, int num, int oc, int oh, int ow, int ic, \
      int ih, int win, const dtype *weights, const dtype *bias,                \
      const operators::ConvParam &param, ARMContext *ctx

#define DEPTHWISE_PARAM(dtype)                                            \
  const dtype *din, dtype *dout, int num, int oc, int oh, int ow, int ic, \
      int ih, int iw, const dtype *weights, const dtype *bias,            \
      const operators::ConvParam &param, ARMContext *ctx

void conv1x1s1_gemm_fp16(CONV_PARAM(float16_t));

void conv_im2col_gemm_fp16(CONV_PARAM(float16_t));

void im2col_fp16(IM2COL_PARAM(float16_t), int stride_h, int stride_w);

void im2col_common_fp16(IM2COL_PARAM(float16_t), int stride_h, int stride_w);

void im2col_s1_fp16(IM2COL_PARAM(float16_t));

void im2col_s2_fp16(IM2COL_PARAM(float16_t));

size_t conv3x3s1_direct_workspace_size(const operators::ConvParam &param,
                                       ARMContext *ctx);

size_t conv3x3s2_direct_workspace_size(const operators::ConvParam &param,
                                       ARMContext *ctx);

void conv_3x3s1_direct_fp16(CONV_PARAM(float16_t));

void conv_3x3s2_direct_fp16(CONV_PARAM(float16_t));

void conv_depthwise_3x3_fp16(CONV_PARAM(float16_t));

}  // namespace fp16
}  // namespace math
}  // namespace arm
}  // namespace lite
}  // namespace paddle
