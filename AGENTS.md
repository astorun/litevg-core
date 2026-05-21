# LiteVG Core Agent Notes

- This repo is the LiteVG Designer LVGL fork. Keep changes narrowly scoped to LVGL behavior needed by LiteVG Designer.
- Preserve the `upstream` remote pointing at `https://github.com/lvgl/lvgl.git` for future LVGL upgrades.
- When merging or cherry-picking from upstream LVGL, keep the LiteVG Core `README.md` unchanged unless the user explicitly asks to edit it.
- Use `main` for active LiteVG Core workspace development.
- Keep the `upstream` branch as an automated mirror of official LVGL `master`; do not edit it manually.
- Create release branches from `main` when stabilizing a specific version, then avoid routine development on those release branches.
- Do not recreate or overload official LVGL tags/branches on this fork. Use namespaced LiteVG tags for releases, such as `litevg-v9.5.0-core.1`.
- Keep software-renderer dither work guarded by `LV_USE_DITHER`, default enabled in the template/internal config unless project policy changes.
- Avoid broad LVGL refactors. Prefer small, portable C changes that are easy to reapply to future upstream LVGL versions.
- Validate with the cheapest useful build first. For WASM compatibility, use the sibling `litevg-wasm-generator` runtime build.
