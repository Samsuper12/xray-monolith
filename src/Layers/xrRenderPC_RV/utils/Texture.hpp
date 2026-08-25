#pragma once
#include <FS.h>
#include <LocatorAPI.h>
#include <format>
#include <gli/gli.hpp>
#include <ktx.h>
#include <ktxvulkan.h>
#include <optional>
#include <memory>

namespace rv::texture {
inline auto load_dds_image(std::fs::path file, bool VFS = true)
    -> std::optional<gli::texture> {
  bool isValid = VFS ? (bool)FS.exist(file) : std::fs::exists(file);
  if (!isValid)
    std::nullopt;

  if (VFS) {
    auto *fs = FS.r_open(file.c_str());
    return gli::load_dds(static_cast<char *>(fs->pointer()), fs->length());
  }
  return gli::load_dds(file.c_str());
}

static inline void ktxTextureDeleter(ktxTexture2 *ktxTex) {
  if (ktxTex) {
    ktxTexture2_Destroy(ktxTex);
  }
}

using ktxTexsturePtr_t =
    std::shared_ptr<ktxTexture2>;

// TODO: teach FS how to rearn files from the drive the same way
// TODO: update to c++23 and use std::expected
inline auto
load_ktx2_image(std::fs::path file,
                ktx_transcode_fmt_e targetTranscodeFormat = KTX_TTF_BC7_RGBA)
    -> std::pair<std::optional<ktxTexsturePtr_t>, std::string> {
  if (!std::fs::exists(file)) {
    return {std::nullopt,
            std::format("KTX2 image not found: %s", file.c_str())};
  }

  ktxTexture2 *ktxTex = nullptr;
  if (auto result = ktxTexture2_CreateFromNamedFile(
          file.c_str(), KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT, &ktxTex);
      result != KTX_SUCCESS) {
    return {std::nullopt,
            std::format("KTX2 image can't be load: %s. Error code: %d",
                        file.c_str(), static_cast<uint32_t>(result))};
  }

  if (ktxTexture2_NeedsTranscoding(ktxTex)) {
    auto result = ktxTexture2_TranscodeBasis(ktxTex, targetTranscodeFormat, 0);
    if (result != KTX_SUCCESS) {
      return {std::nullopt,
              std::format("KTX2 image can't be transcoded: %s. Error code: %d",
                          file.c_str(), static_cast<uint32_t>(result))};
    }
  }

  return {ktxTexsturePtr_t(ktxTex, ktxTextureDeleter), {}};
}

}; // namespace rv::texture