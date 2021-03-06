/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrConstColorProcessor.fp; do not modify.
 **************************************************************************************************/
#ifndef GrConstColorProcessor_DEFINED
#define GrConstColorProcessor_DEFINED

#include "include/core/SkM44.h"
#include "include/core/SkTypes.h"

#include "src/gpu/GrCoordTransform.h"
#include "src/gpu/GrFragmentProcessor.h"

class GrConstColorProcessor : public GrFragmentProcessor {
public:
    enum class InputMode { kIgnore = 0, kLast = 2, kModulateA = 2, kModulateRGBA = 1 };

    static const int kInputModeCnt = (int)InputMode::kLast + 1;

    SkPMColor4f constantOutputForConstantInput(const SkPMColor4f& inColor) const override {
        switch (mode) {
            case InputMode::kIgnore: {
                return color;
            }
            case InputMode::kModulateA: {
                SkPMColor4f input = this->numChildProcessors()
                                            ? ConstantOutputForConstantInput(
                                                      this->childProcessor(inputFP_index), inColor)
                                            : inColor;
                return color * input.fA;
            }
            case InputMode::kModulateRGBA: {
                SkPMColor4f input = this->numChildProcessors()
                                            ? ConstantOutputForConstantInput(
                                                      this->childProcessor(inputFP_index), inColor)
                                            : inColor;
                return color * input;
            }
        }
        SkUNREACHABLE;
    }
    static std::unique_ptr<GrFragmentProcessor> Make(std::unique_ptr<GrFragmentProcessor> inputFP,
                                                     SkPMColor4f color,
                                                     InputMode mode) {
        return std::unique_ptr<GrFragmentProcessor>(
                new GrConstColorProcessor(std::move(inputFP), color, mode));
    }
    GrConstColorProcessor(const GrConstColorProcessor& src);
    std::unique_ptr<GrFragmentProcessor> clone() const override;
    const char* name() const override { return "ConstColorProcessor"; }
    int inputFP_index = -1;
    SkPMColor4f color;
    InputMode mode;

private:
    GrConstColorProcessor(std::unique_ptr<GrFragmentProcessor> inputFP,
                          SkPMColor4f color,
                          InputMode mode)
            : INHERITED(kGrConstColorProcessor_ClassID,
                        (OptimizationFlags)(inputFP ? ProcessorOptimizationFlags(inputFP.get())
                                                    : kAll_OptimizationFlags) &
                                (kConstantOutputForConstantInput_OptimizationFlag |
                                 ((mode != InputMode::kIgnore)
                                          ? kCompatibleWithCoverageAsAlpha_OptimizationFlag
                                          : kNone_OptimizationFlags) |
                                 ((color.isOpaque()) ? kPreservesOpaqueInput_OptimizationFlag
                                                     : kNone_OptimizationFlags)))
            , color(color)
            , mode(mode) {
        if (inputFP) {
            inputFP_index = this->registerChild(std::move(inputFP));
        }
    }
    GrGLSLFragmentProcessor* onCreateGLSLInstance() const override;
    void onGetGLSLProcessorKey(const GrShaderCaps&, GrProcessorKeyBuilder*) const override;
    bool onIsEqual(const GrFragmentProcessor&) const override;
    GR_DECLARE_FRAGMENT_PROCESSOR_TEST
    typedef GrFragmentProcessor INHERITED;
};
#endif
