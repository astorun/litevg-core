# LiteVG Core Project Notes

This repo is the LiteVG Designer LVGL fork with LiteVG-specific additions.

## Repo Relationships

- `litevg-wasm-generator` builds the WASM runtime variant from this repo.
- `litevg-designer` consumes the generated WASM runtime artifacts.
- `upstream` should point to official LVGL at `https://github.com/lvgl/lvgl.git`.

Expected sibling layout:

```text
github-repos/
  litevg-designer/
  litevg-wasm-generator/
  litevg-core/
```

## Upstream Merge Policy

- When merging or cherry-picking from upstream LVGL, preserve this repo's `README.md` unless the user explicitly asks to change it.
- The `upstream` branch is an automated mirror of official LVGL `master`; do not edit it manually.
- Merge or cherry-pick from `upstream` into `main` for LiteVG Core updates.

## Branch And Tag Policy

- `main` is the active LiteVG Core workspace branch.
- `upstream` mirrors official LVGL `master` on an hourly GitHub Actions schedule.
- Create release branches from `main` when preparing a specific LiteVG Core release, then keep those branches stable except for targeted fixes.
- Official LVGL tags are not kept on this fork remote.
- Future custom releases should use namespaced tags, for example:
  - `litevg-v9.5.0-core.1`
  - `litevg-v9.5.0-core.2`

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
