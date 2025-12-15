// SPDX-License-Identifier: Apache-2.0
// Copyright (C) 2013-2020 Synaptics Incorporated. All rights reserved.


///
/// Sublima HDR image processing
///
#pragma once
#include <memory>
#include <string>
#include <vector>


namespace synaptics {
namespace synap {

/// Convert SDR to HDR using Sublima algorithm
class Sublima {
public:
    Sublima();
    ~Sublima();

    struct JsonHDRInfo {
        uint32_t type{1}; // 1: HDR10, 2: HLG
        float PrimaryChromaticityR_X;
        float PrimaryChromaticityR_Y;
        float PrimaryChromaticityG_X;
        float PrimaryChromaticityG_Y;
        float PrimaryChromaticityB_X;
        float PrimaryChromaticityB_Y;
        float WhitePointChromaticity_X;
        float WhitePointChromaticity_Y;
        float LuminanceMax;
        float LuminanceMin;

        uint32_t MatrixCoefficients;
        uint32_t TransferCharacteristics;
        uint32_t ColorPrimaries;

        uint32_t MaxCLL;
        uint32_t MaxFALL;
    };

    /// Initialize the Sublima HDR processing
    /// @param lut2d: LUT2D file path (the LUT file is in CSV format)
    /// @param model: model file path
    /// @param meta: meta file path (deprecated, will be removed)
    /// @param hdrjson: hdr json parameters file path
    /// @return true if initialization was successful
    bool init(const std::string& lut2d,
              const std::string& model, const std::string& meta = "",
              const std::string& hdrjson = "");


    /// Get hdr parameter information
    /// @return hdr parameter
    JsonHDRInfo hdrinfo();
    
    /// Process the NV12 image to convert it to HDR
    /// @param nv12y: Y plane of the NV12 image
    /// @param nv12uv: UV plane of the NV12 image
    /// @param nv15y: Y plane of the NV15 image
    /// @param nv15uv: UV plane of the NV15 image
    /// @param width: image width
    /// @param height: image height
    /// @param nv15_pad: paddding bytes to be added at the end of each row in the NV15 image
    /// @return true if processing was successful
    bool process(const uint8_t* nv12y, const uint8_t* nv12uv, uint8_t* nv15y, uint8_t* nv15uv,
                 uint32_t width, uint32_t height, uint32_t nv15_pad);

    /// Enable/Disable HDR
    /// @param enable: true to enable HDR output, false to just convert to NV15
    /// @return true if success
    bool set_hdr(bool enable);

    /// Enable/Disable UV Conversion
    /// @param enable: true to disable UV conversion, only Y channel will be processed
    /// @return true if success
    bool set_only_y(bool enable);

    /// Get total processing timings (for debug)
    struct Timings {
        int assign;
        int infer;
        int nv15y;
        int nv15uv;
        int tot;
        int cnt;
    };
    Timings* timings();
    
private:
    // Implementation details
    struct Private;
    std::unique_ptr<Private> d;
};

}  // namespace synap
}  // namespace synaptics


