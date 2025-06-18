/*
 * NDA AND NEED-TO-KNOW REQUIRED
 *
 * Copyright (C) 2013-2020 Synaptics Incorporated. All rights reserved.
 *
 * This file contains information that is proprietary to Synaptics
 * Incorporated ("Synaptics"). The holder of this file shall treat all
 * information contained herein as confidential, shall use the
 * information only for its intended purpose, and shall not duplicate,
 * disclose, or disseminate any of this information in any manner
 * unless Synaptics has otherwise provided express, written
 * permission.
 *
 * Use of the materials may require a license of intellectual property
 * from a third party or from Synaptics. This file conveys no express
 * or implied licenses to any intellectual property rights belonging
 * to Synaptics.
 *
 * INFORMATION CONTAINED IN THIS DOCUMENT IS PROVIDED "AS-IS", AND
 * SYNAPTICS EXPRESSLY DISCLAIMS ALL EXPRESS AND IMPLIED WARRANTIES,
 * INCLUDING ANY IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE, AND ANY WARRANTIES OF NON-INFRINGEMENT OF ANY
 * INTELLECTUAL PROPERTY RIGHTS. IN NO EVENT SHALL SYNAPTICS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE, OR
 * CONSEQUENTIAL DAMAGES ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OF THE INFORMATION CONTAINED IN THIS DOCUMENT, HOWEVER CAUSED AND
 * BASED ON ANY THEORY OF LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, AND EVEN IF SYNAPTICS WAS
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. IF A TRIBUNAL OF
 * COMPETENT JURISDICTION DOES NOT PERMIT THE DISCLAIMER OF DIRECT
 * DAMAGES OR ANY OTHER DAMAGES, SYNAPTICS' TOTAL CUMULATIVE LIABILITY
 * TO ANY PARTY SHALL NOT EXCEED ONE HUNDRED U.S. DOLLARS.
 */

///
/// Sublima HDR image processing
///

#include <memory>
#include <string>
#include <vector>
#include "synap/sublima.hpp"

namespace synaptics {
namespace synap {

/// Convert SDR to HDR using Sublima algorithm
class SrSublima {
public:
    SrSublima();
    ~SrSublima();


    /// Initialize the SrSublima processing
    /// @param lut2d: LUT2D file path (the LUT file is in CSV format)
    /// @param slmodel: sublima model file path
    /// @param srmodel:super res model file path
    /// @param slmeta: sublima meta file path (deprecated, will be removed)
    /// @param hdrjson: hdr json parameters file path
    /// @param srmeta: super res model meta file path
    /// @param hdr_disable: Enable/Disable HDR
    /// @param only_y: Enable/Disable UV Conversion
    /// @return true if initialization was successful
    bool init(const std::string& lut2d,
              const std::string& slmodel, const std::string& srmodel, const std::string& slmeta = "",
              const std::string& hdrjson = "", const std::string& srmeta = "", bool hdr_disable = false, bool only_y = false);


    /// Process the NV12 image to convert it to HDR
    /// @param nv12y: Y plane of the NV12 image
    /// @param nv12uv: UV plane of the NV12 image
    /// @param nv15y: Y plane of the NV15 image
    /// @param nv15uv: UV plane of the NV15 image
    /// @param width_sr: SuperRes image width
    /// @param height_sr: SuperRes image height
    /// @param width_sl: Sublima image width
    /// @param height_sl: Sublima image height
    /// @return true if processing was successful
    /// @param nv15_pad: paddding bytes to be added at the end of each row in the NV15 image
    bool process(const uint8_t* nv12y, const uint8_t* nv12uv, uint8_t* nv15y, uint8_t* nv15uv,
                 uint32_t width_sr, uint32_t height_sr, uint32_t width_sl, uint32_t height_sl, uint32_t nv15_pad = 0);

    /// Get sublima hdr parameter information
    /// @return hdr parameter
    Sublima::JsonHDRInfo hdrinfo();

    /// Get total processing timings (for debug)
    struct Timings {
        int assign;
        int infer;
        int tot;
        int cnt;
    };
    Timings* superResTimings();
    Sublima::Timings* sublimaTimings();

private:
    // Implementation details
    struct Private;
    std::unique_ptr<Private> p;
};

}  // namespace synap
}  // namespace synaptics
