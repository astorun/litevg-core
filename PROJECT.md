# litevg-lvgl-expanded Project Notes

This repo is the LiteVG Designer expanded LVGL fork.

## Repo Relationships

- `litevg-wasm-generator` builds the WASM runtime variant from this repo.
- `litevg-designer` consumes the generated WASM runtime artifacts.
- `upstream` should point to official LVGL at `https://github.com/lvgl/lvgl.git`.

Expected sibling layout:

```text
github-repos/
  litevg-designer/
  litevg-wasm-generator/
  litevg-lvgl-expanded/
```

## Branch And Tag Policy

- Remote branches are intentionally minimal:
  - `main`
  - `litevg/v9.5`
- Current custom work should happen on `litevg/v9.5`.
- Official LVGL tags are not kept on this fork remote.
- Future custom releases should use namespaced tags, for example:
  - `litevg-v9.5.0-expanded.1`
  - `litevg-v9.5.0-expanded.2`

## Current Native Dither Work

The current local working tree contains the first native software-renderer dither implementation pass:

- Shared `lv_dither_dsc_t` descriptor and `LV_USE_DITHER` config.
- Descriptor fields wired into gradients, normal shadow, drop shadow, and blur paths.
- Software renderer helper for deterministic tiled dither behavior.
- Gradient/shadow/blur draw paths partially wired to use the descriptor.

Known follow-up areas:

- Complete vertical gradient dither behavior.
- Add public style setter/property polish.
- Wire LiteVG Designer export/runtime settings into the native LVGL descriptors.
- Add focused determinism tests/examples.
