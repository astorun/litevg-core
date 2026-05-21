# litevg-lvgl-expanded Agent Notes

- This repo is the LiteVG Designer LVGL fork. Keep changes narrowly scoped to LVGL behavior needed by LiteVG Designer.
- Preserve the `upstream` remote pointing at `https://github.com/lvgl/lvgl.git` for future LVGL upgrades.
- Use LiteVG branches for custom work. Current active branch is `litevg/v9.5`; `main` is the clean default branch.
- Do not recreate or overload official LVGL tags/branches on this fork. Use namespaced LiteVG tags for releases, such as `litevg-v9.5.0-expanded.1`.
- Keep software-renderer dither work guarded by `LV_USE_DITHER`, default enabled in the template/internal config unless project policy changes.
- Avoid broad LVGL refactors. Prefer small, portable C changes that are easy to reapply to future upstream LVGL versions.
- Validate with the cheapest useful build first. For WASM compatibility, use the sibling `litevg-wasm-generator` runtime build.
