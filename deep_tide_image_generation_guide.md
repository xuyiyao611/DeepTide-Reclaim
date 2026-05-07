# 深潮回收站全量美术生图执行手册

> 版本：`v1.0`
>  
> 项目代号：`深潮回收站`
>  
> 文档用途：把《海底采集游戏原创复刻方案》与《深潮回收站文档说明》里涉及的场景、角色、资源、敌对单位、基地、界面、图鉴、特效和演示素材，统一整理成一份可直接执行的生图 `Markdown` 手册。
>  
> 使用目标：
> 1. 你按阶段生成，不会乱。
> 2. 你每次知道先生成什么、后生成什么。
> 3. 你能直接把提示词喂给 AI。
> 4. 整个游戏的风格统一，不会像拼贴。
> 5. 产出的图适合后续切图、导出、放进 Qt 2D 游戏。

---

## 14. 阶段 7：基地与功能界面场景

### 14.1 阶段目标

- 锁定用户会频繁看到的功能场景。
- 基地、结算、升级、图鉴、海域选择必须属于同一套界面世界。
- 每个功能页都要有自己的用途感，不只是换背景色。

### 14.2 阶段操作顺序

1. 先做开始菜单。
2. 再做基地主界面。
3. 再做结算与升级。
4. 再做图鉴、海域选择、失败与成功页。
5. 最后补存档与教学说明页。

### 14.3 本阶段总建议

- 场景底图统一 `16:9`。
- 这些图默认不是抠图资产。
- 要预留大量 UI 叠加区。
- 不要在底图上直接烙文字。

### 14.4 阶段条目

#### 阶段7-01 开始菜单背景
- 用途：游戏启动页主视觉。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_menu_start`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：要有标题承载空间，不要把中心做满。
- 提示词：
```text
Use case: ui-mockup
Asset type: full-screen menu background for "Deep Tide Station"
Primary request: create a start-menu background that introduces the game's world clearly and elegantly
Scene/backdrop: sea-surface recovery station at dusk or cool daylight, player sub silhouette, distant ocean platform details, and a clean central title space
Subject: an inviting but industrial deep-sea salvage title-screen environment
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: calm atmospheric light with subtle industrial glow and readable menu-space contrast
Palette: blue gray, steel blue, teal, pale cyan glow, restrained orange safety accents
Composition: wide scene with obvious empty title-safe area and uncluttered button-safe area
Output expectation: one production-ready title background supporting menu overlays
Constraints: no text, no watermark, no logo baked in, no overcrowded center, no poster clutter
Negative prompt: photorealistic, game cover poster, fantasy harbor, cyberpunk skyline, copied menu background design
```
- 后处理：中心与下方按钮区必须留净空。

#### 阶段7-02 基地主界面背景
- 用途：玩家返航后常驻的基地页。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_base_main`.
- 生图顺序：开始菜单之后。
- 统一风格检查点：要像“工作台面+停靠区+状态面板”。
- 提示词：
```text
Use case: ui-mockup
Asset type: full-screen base scene background for "Deep Tide Station"
Primary request: create the main recovery-station base interface background
Scene/backdrop: docked player sub, crane arm, storage racks, repair platform, settlement counter, and clear panel-safe zones for UI overlays
Subject: practical industrial sea-surface base used between dive missions
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: overcast marine light with subtle equipment glow and readable work-zone separation
Palette: steel gray, blue-gray, teal, cyan indicators, small orange safety lines
Composition: wide scene with left-right functional separation and clear top/bottom HUD-safe areas
Output expectation: one base background supporting gold, upgrades, codex, and launch buttons
Constraints: no text, no watermark, no crowd of workers, no cityscape overload, no poster composition
Negative prompt: photorealistic, futuristic city dock, fantasy harbor, copied base management screen art, clutter
```
- 后处理：右侧和顶部要留足功能按钮区。

#### 阶段7-03 结算台背景
- 用途：返航结算与售卖资源界面。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_settlement_counter`.
- 生图顺序：基地页之后。
- 统一风格检查点：必须像“清点、扫描、入账”的地方。
- 提示词：
```text
Use case: ui-mockup
Asset type: settlement scene background for "Deep Tide Station"
Primary request: create a settlement-counter environment for sorting and selling dive loot
Scene/backdrop: scan table, tray rails, modular storage bins, holographic display pads without text, and practical industrial accounting layout
Subject: a clear salvage-sorting and settlement area for post-dive results
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: focused workspace light with soft ambient industrial glow
Palette: dark blue-gray, steel, cyan scan lights, muted teal, small orange caution accents
Composition: wide interface background with central list-safe area and side control-safe areas
Output expectation: one settlement background for loot summary and selling interaction
Constraints: no text, no watermark, no cluttered pile of items, no poster style, no human focus
Negative prompt: photorealistic, shop counter realism, fantasy merchant desk, copied sci-fi sorting bay, clutter
```
- 后处理：中部要留清单区，左右留按钮和价格区。

#### 阶段7-04 升级工坊背景
- 用途：升级界面底图。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_upgrade_workshop`.
- 生图顺序：结算台之后。
- 统一风格检查点：要有模块、拆装、调试感。
- 提示词：
```text
Use case: ui-mockup
Asset type: workshop scene background for "Deep Tide Station"
Primary request: create the upgrade workshop environment where submersible modules are improved
Scene/backdrop: modular benches, hanging tools, parts racks, upgrade modules, maintenance lights, and clear card-safe display areas
Subject: a practical industrial workshop dedicated to deep-sea recovery gear upgrades
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: focused bench lighting and controlled equipment glow
Palette: gray steel, blue-gray, cyan indicators, muted teal, orange caution stripes
Composition: wide interior scene with distinct module-display zone and action-button-safe areas
Output expectation: one upgrade workshop background for module cards and purchase interactions
Constraints: no text, no watermark, no weapon armory vibe, no environment clutter, no crowd
Negative prompt: photorealistic, military armory, sci-fi mech garage, fantasy forge, copied upgrade-lab art
```
- 后处理：不要做成武器工坊，要像维护升级间。

#### 阶段7-05 图鉴室背景
- 用途：资源与生物图鉴页。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_codex_room`.
- 生图顺序：升级工坊之后。
- 统一风格检查点：信息研究感强，但不过度学术实验室化。
- 提示词：
```text
Use case: ui-mockup
Asset type: codex scene background for "Deep Tide Station"
Primary request: create the codex or archive room where collected resources and life forms are cataloged
Scene/backdrop: display drawers, scan screens without text, sample capsules, shelving, and clear card-safe areas
Subject: a compact archive-and-analysis room inside the recovery station
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: controlled archive lighting with cool screen glow and soft overhead work light
Palette: dark steel blue, muted teal, cyan display light, pale white highlights, tiny orange labels
Composition: wide interior scene with a large central codex-safe display region
Output expectation: one codex background for resource and creature entries
Constraints: no text, no watermark, no giant science lab complexity, no clutter, no poster framing
Negative prompt: photorealistic, biotech lab horror, fantasy library, copied codex chamber art, visual noise
```
- 后处理：卡片区和缩略图区要能自然叠加。

#### 阶段7-06 海域选择界面背景
- 用途：进入不同海域前的地图选择页。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_zone_select`.
- 生图顺序：图鉴室之后。
- 统一风格检查点：更像深度航线规划，不像世界地图页。
- 提示词：
```text
Use case: ui-mockup
Asset type: zone-select background for "Deep Tide Station"
Primary request: create a sea-zone selection interface background themed around dive route planning and depth permission
Scene/backdrop: navigation console, depth chart displays without text, route lights, access markers, and large selection-safe card areas
Subject: a deep-sea mission planning station inside the recovery base
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: dim planning-room light with cyan display emphasis
Palette: navy, steel gray, cyan route lights, muted teal, subtle orange warning accents
Composition: wide interface scene with multiple card-safe zones for selectable sea areas
Output expectation: one mission-planning background for zone selection
Constraints: no text, no watermark, no fantasy overworld map, no crowded hologram chaos, no clutter
Negative prompt: photorealistic, GPS dashboard realism, fantasy atlas, copied mission-select UI background, neon overload
```
- 后处理：要明显有“深度许可证”与“海域入口”气氛。

#### 阶段7-07 暂停菜单背景
- 用途：游戏中暂停时的模糊底板或降噪背景。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_pause_overlay`.
- 生图顺序：海域选择之后。
- 统一风格检查点：低干扰、可覆盖，不应喧宾夺主。
- 提示词：
```text
Use case: ui-mockup
Asset type: pause-menu background plate for "Deep Tide Station"
Primary request: create a subdued pause-menu background plate consistent with the game's industrial UI
Scene/backdrop: soft abstracted station-panel backdrop with underwater tech framing, subtle equipment silhouettes, and central menu-safe space
Subject: a non-distracting pause-layer visual for a deep-sea salvage game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: low-intensity interface glow with soft contrast
Palette: navy, muted teal, dim cyan, blue-gray, tiny orange accents if needed
Composition: quiet wide backdrop with large central readable menu-safe area
Output expectation: one pause screen plate that supports overlays without distraction
Constraints: no text, no watermark, no busy illustrations, no character focus, no poster energy
Negative prompt: photorealistic, high-contrast poster, fantasy menu art, cyberpunk clutter, copied pause screens
```
- 后处理：比主界面底图更安静，方便用户集中看菜单。

#### 阶段7-08 失败界面背景
- 用途：氧尽、耐久归零或失败结算页。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_fail_screen`.
- 生图顺序：暂停页之后。
- 统一风格检查点：要传达损失与危险，但不做恐怖图。
- 提示词：
```text
Use case: ui-mockup
Asset type: fail-screen background for "Deep Tide Station"
Primary request: create a failure-screen environment that communicates mission loss without breaking the game's tone
Scene/backdrop: dim damaged panel view, weakened sub silhouette, warning lights, scattered small sparks, and strong central message-safe area
Subject: a controlled failure mood for a deep-sea recovery mission
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: darker base light with restrained warning red-orange and cold blue contrast
Palette: navy, steel blue, dim cyan, muted gray, controlled warning orange-red
Composition: wide scene with obvious center-safe area for fail information and retry buttons
Output expectation: one readable failure background for game-over states
Constraints: no text, no watermark, no gore, no horror corpse imagery, no chaos overload
Negative prompt: photorealistic, disaster movie frame, body horror, copied fail-screen drama art, clutter
```
- 后处理：不能比终局背景更黑，否则文字压不住。

#### 阶段7-09 成功返航界面背景
- 用途：完成一次完整闭环后的正反馈页面。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_return_success`.
- 生图顺序：失败页之后。
- 统一风格检查点：高兴但克制，不像庆典海报。
- 提示词：
```text
Use case: ui-mockup
Asset type: success-screen background for "Deep Tide Station"
Primary request: create a successful return background that feels rewarding and safe without becoming a flashy celebration poster
Scene/backdrop: docked sub, calm station lights, sorted cargo silhouettes, subtle glow, and clear result-message-safe area
Subject: a reassuring post-dive success mood for the recovery station
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft welcoming station light with controlled cyan highlights and gentle warmth
Palette: blue-gray, steel, teal, cyan glow, tiny warm-orange welcome accents
Composition: wide scene with a stable center panel-safe area and calm positive atmosphere
Output expectation: one positive success background for post-mission transitions
Constraints: no text, no watermark, no fireworks, no confetti, no poster hero shot
Negative prompt: photorealistic, celebration poster, fantasy victory screen, copied reward scene art, clutter
```
- 后处理：成功氛围主要通过稳定、明亮、整洁表达。

#### 阶段7-10 深度许可证界面背景
- 用途：海域解锁与许可证领取页。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_depth_license_screen`.
- 生图顺序：成功返航页之后。
- 统一风格检查点：正规、授权、设备感强。
- 提示词：
```text
Use case: ui-mockup
Asset type: progression-screen background for "Deep Tide Station"
Primary request: create a depth-license issuance interface background for unlocking deeper sea zones
Scene/backdrop: authorization console, pressure-grade document bay, secure light strips, and a clear central certificate-safe area
Subject: a formal industrial permission system inside the recovery station
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: focused console light with secure cold glow and restrained access indicators
Palette: navy, steel gray, cyan, pale teal, tiny orange security accents
Composition: wide official-looking interface layout with certificate-safe center and side controls
Output expectation: one progression background for unlock and license moments
Constraints: no text, no watermark, no fantasy seal, no corporate office realism, no clutter
Negative prompt: photorealistic, office document desk, magic scroll screen, copied clearance UI background, clutter
```
- 后处理：必须比普通菜单更“正式”。

#### 阶段7-11 存档界面背景
- 用途：存档、继续游戏、读取进度页。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_save_screen`.
- 生图顺序：许可证页之后。
- 统一风格检查点：平稳、可靠、不抢戏。
- 提示词：
```text
Use case: ui-mockup
Asset type: save-load screen background for "Deep Tide Station"
Primary request: create a calm and reliable save/load interface background
Scene/backdrop: archive terminals, compact storage racks, slot-safe panels, and subdued station equipment in the background
Subject: a dependable progress-management scene within the recovery station
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft controlled room lighting with subtle archival display glow
Palette: muted navy, blue-gray, teal, dim cyan, tiny warm details
Composition: wide quiet interface scene with multiple slot-safe regions and low distraction
Output expectation: one save/load background that supports slot cards and actions
Constraints: no text, no watermark, no dramatic focal scene, no poster composition, no clutter
Negative prompt: photorealistic, server-room realism, fantasy archive hall, copied load-screen UI art, neon overload
```
- 后处理：这是功能页，不是世界观展示页。

#### 阶段7-12 教学说明界面背景
- 用途：开始前玩法说明、操作说明页。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase7_tutorial_screen`.
- 生图顺序：本阶段最后。
- 统一风格检查点：必须干净，给说明文字腾位置。
- 提示词：
```text
Use case: ui-mockup
Asset type: tutorial screen background for "Deep Tide Station"
Primary request: create a clean tutorial background for controls and gameplay explanation
Scene/backdrop: simplified station panel framing, soft sub silhouette hints, clean overlay regions, and minimal visual distraction
Subject: a readable instructional interface background for a deep-sea salvage game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft low-intensity interface glow with clean readability
Palette: navy, blue-gray, muted teal, dim cyan, tiny orange accents
Composition: broad empty center-left or center-right regions suitable for instructional text and diagrams
Output expectation: one teaching-friendly interface background for onboarding screens
Constraints: no text, no watermark, no busy scene, no dramatic focal object, no clutter
Negative prompt: photorealistic, poster background, cyberpunk visual noise, copied tutorial art, heavy contrast
```
- 后处理：能放大量说明内容，说明这张图才合格。

---

## 15. 阶段 8：HUD 与 UI 控件

### 15.1 阶段目标

- 锁定所有高频交互层。
- HUD、按钮、图标、卡片必须同一套边框与光效逻辑。
- 小尺寸下也要可读。

### 15.2 阶段操作顺序

1. 先做核心信息组件。
2. 再做按钮与交互提示。
3. 再做卡片和背包。
4. 最后做锁定、稀有度和升级卡片。

### 15.3 本阶段总建议

- 尽量用透明背景。
- 元素之间间距要大，方便后续切图。
- 颜色系统完全服从阶段 0 的 UI 母图。

### 15.4 阶段条目

#### 阶段8-01 HUD 图标组
- 用途：氧气、耐久、金币、背包、深度等主图标。
- 建议生成数量：一组 5 到 8 个图标，初稿 3 组，保留 1 组。
- 建议画幅：4:3。
- 背景：透明背景风格提示，实际可先用纯 `#00ff00`。
- 命名建议：`phase8_hud_icon_set`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：线性语言与体积感要统一。
- 提示词：
```text
Use case: ui-mockup
Asset type: HUD icon set for "Deep Tide Station"
Primary request: create a cohesive icon set for oxygen, durability, gold, cargo, depth, upgrade, codex, and return functions
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a unified set of small industrial sci-fi icons designed for a deep-sea salvage game HUD
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: subtle icon glow and edge light only, built for small-size clarity
Palette: steel blue, cyan, teal, pale white, tiny orange warning accents
Composition: evenly spaced icon set with consistent stroke weight, framing logic, and readable silhouettes
Output expectation: one clean HUD icon family for cutting into individual UI assets
Constraints: no text, no watermark, no app-store icon style, no glossy emoji look, no clutter
Negative prompt: photorealistic, phone app icons, fantasy icons, cartoon stickers, copied HUD icon packs
```
- 后处理：最终要逐个切图，确认小尺寸下不糊。

#### 阶段8-02 氧气条
- 用途：游戏中最高频数值条。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：4:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_bar_oxygen`.
- 生图顺序：图标组之后。
- 统一风格检查点：默认青蓝、低氧变黄、极低变红的逻辑要预留。
- 提示词：
```text
Use case: ui-mockup
Asset type: HUD progress bar for "Deep Tide Station"
Primary request: create an oxygen bar design suitable for normal, warning, and danger states
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a compact industrial deep-sea oxygen meter bar with frame, fill area, and readable warning-state structure
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: subtle interface glow and crisp edge readability
Palette: navy frame, cyan fill, teal accents, reserved yellow-orange-red warning space
Composition: horizontal bar with modular segment feel and HUD-safe proportions
Output expectation: one oxygen meter design ready for state recolor and slicing
Constraints: no text, no watermark, no mobile health-bar style, no fantasy ornament, no clutter
Negative prompt: photorealistic, phone battery icon, MMO fantasy UI, copied sci-fi meter, glossy app UI
```
- 后处理：做条形框体与填充层分离更方便后续程序控制。

#### 阶段8-03 耐久条
- 用途：结构耐久或生命条。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：4:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_bar_durability`.
- 生图顺序：氧气条之后。
- 统一风格检查点：与氧气条同家族，但语义不同。
- 提示词：
```text
Use case: ui-mockup
Asset type: HUD durability bar for "Deep Tide Station"
Primary request: create a durability or hull-integrity bar visually related to the oxygen bar but clearly distinct
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a reinforced industrial status bar for vehicle integrity with a harder mechanical frame language
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: minimal interface glow with a stronger frame emphasis than the oxygen bar
Palette: steel blue frame, cyan-teal fill, pale white highlights, orange-red reserve warning logic
Composition: horizontal status bar with a slightly heavier structure than the oxygen meter
Output expectation: one hull-integrity bar design consistent with the full HUD
Constraints: no text, no watermark, no fantasy HP bar, no glossy phone UI, no clutter
Negative prompt: photorealistic, app health bar, MMO fantasy meter, copied sci-fi HUD pack
```
- 后处理：氧气条更轻，耐久条更硬，这个差异要保住。

#### 阶段8-04 深度显示框
- 用途：右上深度数值承载框。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：2:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_depth_frame`.
- 生图顺序：耐久条之后。
- 统一风格检查点：应该看起来像读数仪，不是按钮。
- 提示词：
```text
Use case: ui-mockup
Asset type: numeric display frame for "Deep Tide Station"
Primary request: create a depth-readout frame for showing current sea depth
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a compact industrial depth display frame with pressure-gauge influence and clean numeric-safe space
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: subtle instrument glow and crisp panel-edge highlights
Palette: navy, steel blue, cyan indicator edges, muted teal, tiny warning orange details
Composition: centered UI frame with clear interior space for dynamic numeric text
Output expectation: one depth-display frame matching the HUD language
Constraints: no text, no watermark, no button-like big bevel, no fantasy trim, no clutter
Negative prompt: photorealistic, dashboard photo, calculator screen, copied HUD widget, mobile app panel
```
- 后处理：内部数字区域要大，别把装饰吃掉内容空间。

#### 阶段8-05 背包格子
- 用途：资源格、物品格、升级材料格。
- 建议生成数量：初稿 3 组，保留 1 组。
- 建议画幅：1:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_inventory_slot`.
- 生图顺序：深度框之后。
- 统一风格检查点：格子要明显能叠加稀有度边框。
- 提示词：
```text
Use case: ui-mockup
Asset type: inventory slot UI asset for "Deep Tide Station"
Primary request: create a base inventory slot design for cargo, materials, and codex-adjacent item display
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a modular square item slot with industrial frame logic and clean inner item-safe area
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: subtle panel glow and clean frame highlights
Palette: steel blue, navy, muted teal, cyan corner-light accents
Composition: centered UI slot with clear margins, tidy corners, and scalable structure
Output expectation: one reusable inventory-slot base for many systems
Constraints: no text, no watermark, no fantasy inventory square, no toy-like thick bevel, no clutter
Negative prompt: photorealistic, mobile app tile, RPG fantasy slot, copied inventory UI pack, glossy cartoon panel
```
- 后处理：格子内缘不要太粗，避免遮掉资源图标。

#### 阶段8-06 稀有度边框三种
- 用途：普通、稀有、珍贵资源外框。
- 建议生成数量：一组三种边框，初稿 3 组，保留 1 组。
- 建议画幅：1:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_rarity_frames`.
- 生图顺序：背包格之后。
- 统一风格检查点：框体结构一致，只换强调色和小细节。
- 提示词：
```text
Use case: ui-mockup
Asset type: rarity-frame set for "Deep Tide Station"
Primary request: create three coordinated rarity frames for common, rare, and precious items
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a matched trio of item frames sharing one structure while differing through accent color and micro-detail intensity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: subtle frame glow with controlled rarity highlights
Palette: common uses pale cyan-blue, rare uses teal-green emphasis, precious uses controlled bright premium accent while staying inside the game's palette
Composition: three aligned square frames with identical proportions and family resemblance
Output expectation: one full rarity-frame set for inventory and codex use
Constraints: no text, no watermark, no full rainbow rarity scheme, no fantasy gem corners, no clutter
Negative prompt: photorealistic, mobile loot-box UI, fantasy MMORPG frame, copied rarity border packs, oversaturated neon
```
- 后处理：珍贵框不要把整个物品淹没。

#### 阶段8-07 主按钮四状态
- 用途：开始、出航、确认、升级等主行动按钮。
- 建议生成数量：默认/悬停/按下/禁用 四状态，初稿 3 组，保留 1 组。
- 建议画幅：3:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_button_primary`.
- 生图顺序：稀有度边框之后。
- 统一风格检查点：状态变化明确，但结构统一。
- 提示词：
```text
Use case: ui-mockup
Asset type: button-state set for "Deep Tide Station"
Primary request: create a primary action button family with default, hover, pressed, and disabled states
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: an industrial sci-fi rectangular action button with rounded corners, pressure-grade frame logic, and clear state variations
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: controlled interface glow with state-driven brightness changes
Palette: navy and steel blue base, cyan active glow, muted teal secondary edge, dimmed disabled state
Composition: four aligned button states with identical structure and readable visual transitions
Output expectation: one main-button state family for high-priority actions
Constraints: no text, no watermark, no mobile glossy app button, no fantasy ornament, no clutter
Negative prompt: photorealistic, app-store button, candy UI, cyberpunk neon overload, copied UI button kit
```
- 后处理：按下态最好更暗更紧，不要只是更亮。

#### 阶段8-08 次按钮四状态
- 用途：返回、取消、次要入口按钮。
- 建议生成数量：四状态一组，初稿 3 组，保留 1 组。
- 建议画幅：3:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_button_secondary`.
- 生图顺序：主按钮之后。
- 统一风格检查点：同家族，但弱于主按钮。
- 提示词：
```text
Use case: ui-mockup
Asset type: secondary button-state set for "Deep Tide Station"
Primary request: create a secondary action button family with default, hover, pressed, and disabled states
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a quieter industrial interface button derived from the primary button style but visually lower priority
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: restrained interface glow with subtler state changes than the primary button
Palette: blue-gray base, muted cyan edges, limited teal accent, dim disabled state
Composition: four aligned button states with consistent structure and lower visual weight
Output expectation: one secondary-button family for low-priority actions
Constraints: no text, no watermark, no app-store button look, no fantasy trim, no clutter
Negative prompt: photorealistic, sugary UI, copied menu button pack, cyberpunk overload, glossy mobile design
```
- 后处理：主按钮和次按钮必须一眼分优先级。

#### 阶段8-09 海域锁定标记
- 用途：未解锁海域遮罩标识。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_lock_zone`.
- 生图顺序：按钮之后。
- 统一风格检查点：是工业许可锁，不是童话锁头。
- 提示词：
```text
Use case: ui-mockup
Asset type: lock icon asset for "Deep Tide Station"
Primary request: create a zone-locked marker with a deep-sea industrial authorization feel
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a rugged lock or access-restriction symbol integrated with pressure-gate and permit-system design language
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: subtle secure-access glow with clear icon readability
Palette: steel blue, navy, cyan line accents, muted teal, tiny orange security marks
Composition: centered lock symbol with strong simple readability at small scale
Output expectation: one lock-state icon for blocked zone cards and buttons
Constraints: no text, no watermark, no cartoon padlock, no fantasy seal, no clutter
Negative prompt: photorealistic, app lock icon, medieval padlock, copied access-denied icon set, glossy mobile UI
```
- 后处理：小尺寸下要比一般图标更醒目。

#### 阶段8-10 采集交互提示
- 用途：资源可采集时的按键提示底板。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：2:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_prompt_collect`.
- 生图顺序：锁定标记之后。
- 统一风格检查点：短促、明显、别像弹窗。
- 提示词：
```text
Use case: ui-mockup
Asset type: interaction prompt asset for "Deep Tide Station"
Primary request: create a collection-interaction prompt frame for when the player is near a collectible resource
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a compact prompt plate with key-hint-safe area and industrial sci-fi interaction language
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: small interface glow with crisp edge clarity
Palette: navy, blue-gray, cyan edge lights, muted teal, small orange attention accents
Composition: horizontal compact prompt frame with obvious icon-safe and text-safe zones
Output expectation: one interaction prompt base for collect actions
Constraints: no text, no watermark, no giant dialog box, no fantasy ornament, no clutter
Negative prompt: photorealistic, mobile tooltip, copied game prompt UI, glossy app banner, over-detailed panel
```
- 后处理：尽量瘦长，别挡玩家视线。

#### 阶段8-11 返航提示
- 用途：进入返航区或建议返航时的提示底板。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：2:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_prompt_return`.
- 生图顺序：采集提示之后。
- 统一风格检查点：和采集提示同家族，但语义更强。
- 提示词：
```text
Use case: ui-mockup
Asset type: interaction prompt asset for "Deep Tide Station"
Primary request: create a return-to-base prompt frame that is more urgent and directional than the collect prompt
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a compact return prompt plate with directional identity and stronger mission-safety emphasis
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: subtle interface glow with slightly stronger attention highlights than the collect prompt
Palette: navy, steel blue, cyan, muted teal, tiny orange attention accents
Composition: horizontal prompt frame with icon-safe and message-safe space, clearly built for urgent guidance
Output expectation: one return-warning prompt base for navigation and safety moments
Constraints: no text, no watermark, no full-screen warning box, no fantasy frame, no clutter
Negative prompt: photorealistic, app notification banner, copied warning prompt UI, neon overload, glossy mobile style
```
- 后处理：最好能一眼分出“建议返航”和“普通交互”。

#### 阶段8-12 升级卡片底板
- 用途：升级项显示卡片。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：3:4。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase8_upgrade_card`.
- 生图顺序：本阶段最后。
- 统一风格检查点：可同时容纳模块图、等级、价格、按钮。
- 提示词：
```text
Use case: ui-mockup
Asset type: upgrade card frame for "Deep Tide Station"
Primary request: create an upgrade-card base for showing module image, level, cost, and action button
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a vertical industrial card frame with clear image area, stat area, and action area
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: controlled card-edge glow with crisp modular framing
Palette: steel blue, navy, cyan edge accents, muted teal, minimal orange highlights
Composition: vertical card with obvious top-image zone, mid-info zone, and bottom-action-safe zone
Output expectation: one reusable upgrade card base for all module types
Constraints: no text, no watermark, no fantasy tarot-card styling, no clutter, no glossy mobile look
Negative prompt: photorealistic, collectible card game frame, copied upgrade card UI, app-store card, neon overload
```
- 后处理：卡片必须支持主图和文字同时存在。

---

## 16. 阶段 9：特效与动画参考

### 16.1 阶段目标

- 锁定反馈层。
- 把采集、警报、推进、放电、返航这些高频反馈统一成一套语言。
- 特效本体和主资产必须分层。

### 16.2 阶段操作顺序

1. 先做核心交互特效。
2. 再做危险与受击特效。
3. 再做环境特效。
4. 最后做碎片和动画参考。

### 16.3 本阶段总建议

- 绝大部分素材建议透明背景。
- 先做单体特效，不要先做整场景粒子雨。
- 控制特效面积，别压住主体。

### 16.4 阶段条目

#### 阶段9-01 采集成功闪光
- 用途：资源采集完成反馈。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_collect_flash`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：短、亮、集中，不要爆炸烟花。
- 提示词：
```text
Use case: stylized-concept
Asset type: effect asset for "Deep Tide Station"
Primary request: create a compact collection-success flash effect
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a small concentrated burst of cyan-teal energy and particles indicating successful resource pickup
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: bright but localized effect lighting with clean soft edges
Palette: cyan, teal, pale white, minimal blue haze
Composition: centered compact effect with clear core and controlled particle spread
Output expectation: one reusable pickup-flash effect for many resource interactions
Constraints: no text, no watermark, no explosion smoke, no firework spread, no environment
Negative prompt: photorealistic, magic spell blast, fantasy loot burst, copied particle effect sheet, clutter
```
- 后处理：不要超出资源本体太多。

#### 阶段9-02 低氧警报环
- 用途：低氧时围绕 HUD 或角色的警报表现。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_low_oxygen`.
- 生图顺序：采集闪光之后。
- 统一风格检查点：科技警报感，非魔法圈。
- 提示词：
```text
Use case: stylized-concept
Asset type: HUD effect asset for "Deep Tide Station"
Primary request: create a low-oxygen warning ring or alert overlay effect
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a restrained circular or semi-circular warning effect built from scan lines, alert arcs, and pressure-alarm light logic
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: urgent controlled warning glow with crisp tech edges
Palette: orange-red warning light, dim cyan support lines, steel-blue interface traces
Composition: centered warning ring with a clear readable form and no excessive fill
Output expectation: one oxygen-danger overlay effect for HUD and momentary alerts
Constraints: no text, no watermark, no fantasy magic circle, no full-screen chaos, no environment
Negative prompt: photorealistic, magical rune circle, rave neon ring, copied HUD alarm art, clutter
```
- 后处理：红色不能压倒整个冷色系统，只作警告点亮。

#### 阶段9-03 受击电火花
- 用途：主角或敌人受电击、撞击时的反馈。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_hit_spark`.
- 生图顺序：低氧环之后。
- 统一风格检查点：不能过于真实焊接火花。
- 提示词：
```text
Use case: stylized-concept
Asset type: hit effect asset for "Deep Tide Station"
Primary request: create a compact electric hit spark effect for collisions and damage events
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a short-lived burst of blue-white electrical sparks and tiny fragments with a clean game-friendly silhouette
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: sharp localized spark light with minimal residual haze
Palette: cold white, cyan, pale blue, tiny gray fragments
Composition: centered effect with directional energy and limited spread
Output expectation: one damage-feedback effect for player and hazards
Constraints: no text, no watermark, no explosion smoke, no realistic welding shower, no environment
Negative prompt: photorealistic, fireworks, fantasy lightning spell, copied electric impact sheet, clutter
```
- 后处理：确保与电弧鳐的放电特效层级不同。

#### 阶段9-04 推进尾流
- 用途：移动感与速度感表现。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：2:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_thruster_trail`.
- 生图顺序：受击电火花之后。
- 统一风格检查点：是水下推进，不是火箭火焰。
- 提示词：
```text
Use case: stylized-concept
Asset type: movement effect asset for "Deep Tide Station"
Primary request: create an underwater propulsion trail effect for the player submersible
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a directional cyan-teal thrust stream with bubbles and soft water-energy flow rather than fire
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft luminous trail core with fading edges
Palette: cyan, teal, pale white, faint blue transparency
Composition: horizontal directional effect with clear source and tail fade
Output expectation: one reusable movement-trail effect for the submersible
Constraints: no text, no watermark, no rocket flame, no smoke plume, no environment
Negative prompt: photorealistic, spaceship exhaust, fire jet, copied engine trail effects, clutter
```
- 后处理：方向性要强，便于左右翻转使用。

#### 阶段9-05 扫描脉冲圈
- 用途：扫描升级、发现资源、探测动作反馈。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_scan_pulse`.
- 生图顺序：推进尾流之后。
- 统一风格检查点：科技扫描感，不要法术波纹感。
- 提示词：
```text
Use case: stylized-concept
Asset type: scan effect asset for "Deep Tide Station"
Primary request: create a scanning pulse effect for resource detection and area sweeps
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a crisp expanding scan ring or directional wave built from clean industrial interface energy lines
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: subtle glow with clean ring definition and minimal haze
Palette: cyan, pale teal, cold white, dim blue frame accents
Composition: centered scan-wave effect with obvious source and outward movement language
Output expectation: one reusable scan pulse effect for modules and UI moments
Constraints: no text, no watermark, no magic circle, no fantasy rune wave, no environment
Negative prompt: photorealistic, sonar photo, magical ripple spell, copied scan HUD effect, clutter
```
- 后处理：尽量做圆环与扇形两用感。

#### 阶段9-06 热泉气泡柱
- 用途：热泉危险喷发特效。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：2:3。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_vent_bubbles`.
- 生图顺序：扫描圈之后。
- 统一风格检查点：热泉是局部危险，不要像烟囱全屏白雾。
- 提示词：
```text
Use case: stylized-concept
Asset type: environment effect asset for "Deep Tide Station"
Primary request: create a vertical thermal vent bubble-column effect
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a readable column of white bubbles and faint warm-vent shimmer rising from a focused source
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft bubble translucency with very restrained warm undertone
Palette: pale white, faint cyan, tiny warm orange haze near the source
Composition: vertical effect with narrow base and upward spread suitable for hazard placement
Output expectation: one reusable vent-bubble effect layer for thermal hazards
Constraints: no text, no watermark, no giant steam cloud, no fire plume, no environment
Negative prompt: photorealistic, boiling steam realism, fantasy geyser magic, copied vent effect sheet, clutter
```
- 后处理：这层要能叠在热泉喷口之上。

#### 阶段9-07 冷流拖尾
- 用途：冷流区方向风格化特效。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：2:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_current_trail`.
- 生图顺序：热泉气泡柱之后。
- 统一风格检查点：像冷流切过，不像烟带。
- 提示词：
```text
Use case: stylized-concept
Asset type: environment effect asset for "Deep Tide Station"
Primary request: create a directional cold-current streak effect for canyon zones
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a smooth blue-cyan current trail with directional flow lines and low-turbulence clarity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: faint cold luminosity with soft directional fade
Palette: pale cyan, cold blue, faint teal, white edge streaks
Composition: horizontal directional effect with clean start and fade zones
Output expectation: one reusable current-flow effect for environmental movement cues
Constraints: no text, no watermark, no storm smoke, no magical wind ribbon, no environment
Negative prompt: photorealistic, cloud streak, fantasy spell ribbon, copied flow effect sheets, clutter
```
- 后处理：尽量左右翻转都好用。

#### 阶段9-08 放电爆闪
- 用途：电弧鳐攻击或电气危险瞬发特效。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_electric_burst`.
- 生图顺序：冷流拖尾之后。
- 统一风格检查点：比受击电火花更强，但不能淹没战场。
- 提示词：
```text
Use case: stylized-concept
Asset type: attack effect asset for "Deep Tide Station"
Primary request: create a compact electric discharge burst effect for enemy attacks
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a stronger localized electric burst made of branching arcs, bright core, and sharp readable energy silhouette
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: intense localized electric light with quick fade and minimal haze
Palette: bright cyan, cold white, pale blue, tiny dark gap contrast
Composition: centered compact burst with readable core and contained spread
Output expectation: one reusable enemy-electric-burst effect for high-threat moments
Constraints: no text, no watermark, no giant thunderstorm cloud, no environment, no silhouette chaos
Negative prompt: photorealistic, superhero lightning blast, fantasy thunder spell, copied combat FX, clutter
```
- 后处理：确保可与主敌动作图分层叠加。

#### 阶段9-09 返航高光柱
- 用途：返航点成功触发反馈。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：2:3。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_return_beam`.
- 生图顺序：放电爆闪之后。
- 统一风格检查点：安全、完成、引导感明显。
- 提示词：
```text
Use case: stylized-concept
Asset type: event effect asset for "Deep Tide Station"
Primary request: create a return-to-base activation beam or highlight effect
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a vertical guidance beam with calm cyan-white glow and success-oriented particle lift
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: bright but soft success glow with clear vertical structure
Palette: cyan, pale white, teal, faint blue haze
Composition: tall vertical effect with narrow base and readable beam core
Output expectation: one success-trigger effect for return zones and station guidance
Constraints: no text, no watermark, no magic portal beam, no environment, no giant fireworks
Negative prompt: photorealistic, fantasy teleport column, heaven-light cliché, copied sci-fi teleport FX, clutter
```
- 后处理：成功感靠柔和提升，不靠炫光爆炸。

#### 阶段9-10 稀有资源掉落光
- 用途：稀有资源出现或采集后的价值提示。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_rare_glow`.
- 生图顺序：返航高光柱之后。
- 统一风格检查点：高级感明显，但不能脱离冷色系统。
- 提示词：
```text
Use case: stylized-concept
Asset type: reward effect asset for "Deep Tide Station"
Primary request: create a premium rare-item glow effect for valuable resource appearances
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a small premium aura with cyan-teal core and restrained high-value highlight language
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: focused collectible glow with clean falloff and minimal spark debris
Palette: bright cyan, teal, cold white, tiny premium accent if needed
Composition: centered reward aura effect sized for item overlay use
Output expectation: one reusable rare-item effect for precious pickups
Constraints: no text, no watermark, no gold treasure explosion, no fantasy spark shower, no environment
Negative prompt: photorealistic, loot-box shine, fantasy legendary aura, copied reward FX, clutter
```
- 后处理：不要用大面积金色。

#### 阶段9-11 爆裂碎片特效
- 用途：容器破开、裂壳螺破碎、设施损坏。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_shatter`.
- 生图顺序：稀有光之后。
- 统一风格检查点：碎片要可控，不是烟花。
- 提示词：
```text
Use case: stylized-concept
Asset type: impact-break effect asset for "Deep Tide Station"
Primary request: create a compact shatter effect for containers, shells, and brittle props
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: a controlled burst of hard fragments, small chips, and sharp directional breakup without smoke dominance
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: crisp fragment highlights with short-lived energy accents if needed
Palette: blue-gray fragments, pale white highlights, tiny cyan edge glints
Composition: centered burst with clear outward direction and contained radius
Output expectation: one reusable breakage effect for props and enemy shell states
Constraints: no text, no watermark, no explosion flame, no smoke wall, no environment
Negative prompt: photorealistic, debris simulation, action-movie blast, copied break FX, clutter
```
- 后处理：材质差异可后续通过着色调节，不必全写死。

#### 阶段9-12 水下颗粒环境特效
- 用途：场景氛围、海域层次感。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：纯 `#00ff00` 或透明。
- 命名建议：`phase9_fx_underwater_particles`.
- 生图顺序：本阶段最后。
- 统一风格检查点：只是氛围层，不是遮罩层。
- 提示词：
```text
Use case: stylized-concept
Asset type: ambient effect layer for "Deep Tide Station"
Primary request: create a reusable underwater particle layer for ambient depth and movement
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout and later transparency extraction
Subject: sparse suspended particles, tiny drifting motes, and soft current-carried specks suitable for layering over gameplay
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: very soft low-intensity particle glow and translucency
Palette: pale cyan, faint teal, near-white motes, light blue haze
Composition: wide ambient layer with even spread and no dominant focal cluster
Output expectation: one reusable particle atmosphere layer for many sea zones
Constraints: no text, no watermark, no snowstorm density, no heavy fog wall, no environment object silhouettes
Negative prompt: photorealistic, dust photo overlay, glitter wallpaper, copied particle layer, clutter
```
- 后处理：密度宁可少，不可多。

---

## 17. 阶段 10：图鉴与宣传图

### 17.1 阶段目标

- 把游戏资产延伸到展示层。
- 图鉴卡、封面图、视频封面、宣传海报都不能脱离游戏内风格。
- 展示图要比游戏图更完整，但不能变成另一套美术。

### 17.2 阶段操作顺序

1. 先做资源图鉴卡。
2. 再做生物图鉴卡。
3. 再做横竖版封面。
4. 最后做商店头图、视频封面和总海报。

### 17.3 本阶段总建议

- 图鉴卡推荐 `3:4`。
- 横版封面推荐 `16:9`。
- 竖版封面推荐 `4:5`。
- 宣传图可以更完整，但仍要遵守统一色板。

### 17.4 阶段条目

#### 阶段10-01 图鉴卡：荧团浮体
- 用途：资源图鉴、演示 PPT、报告插图。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：3:4。
- 背景：完整构图。
- 命名建议：`phase10_codex_glow_cluster`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：图鉴展示更完整，但仍是游戏内物种说明风。
- 提示词：
```text
Use case: stylized-concept
Asset type: codex card illustration for "Deep Tide Station"
Primary request: create a codex-style presentation illustration for Glow Cluster
Scene/backdrop: clean scientific-display-like background with soft framing, subtle scan-panel feel, and clear central subject area, no text
Subject: the Glow Cluster resource shown clearly as a cataloged deep-sea floating material specimen
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft specimen-display lighting with readable glow emphasis
Palette: cyan, teal, blue-gray, pale white, restrained cool accents
Composition: vertical card illustration with centered specimen, clean margin, and codex presentation feel
Output expectation: one codex-card-ready image for the Glow Cluster entry
Constraints: no text, no watermark, no fantasy specimen jar, no poster clutter, no copied encyclopedic design
Negative prompt: photorealistic, scientific photo card, fantasy bestiary page, copied codex UI art, clutter
```
- 后处理：比地图资源图更完整，但不改物种本体。

#### 阶段10-02 图鉴卡：壳晶矿
- 用途：资源图鉴展示。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：3:4。
- 背景：完整构图。
- 命名建议：`phase10_codex_shell_crystal`.
- 生图顺序：荧团浮体图鉴卡之后。
- 统一风格检查点：突出附着型结构和晶体核心。
- 提示词：
```text
Use case: stylized-concept
Asset type: codex card illustration for "Deep Tide Station"
Primary request: create a codex-style presentation illustration for Shell Crystal Ore
Scene/backdrop: clean archive-display background with subtle scan framing and specimen presentation space, no text
Subject: the Shell Crystal Ore shown clearly as an attached deep-sea mineral specimen with readable shell and crystal parts
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft display lighting with crystal core emphasis and shell readability
Palette: gray shell, cyan-teal crystal glow, blue-gray supports, pale white highlights
Composition: vertical codex-card layout with centered specimen and clear surrounding negative space
Output expectation: one codex-card-ready image for Shell Crystal Ore
Constraints: no text, no watermark, no fantasy gem-book style, no poster clutter, no copied codex layout
Negative prompt: photorealistic, mineral museum photo, fantasy jewel card, copied encyclopedia art, clutter
```
- 后处理：壳与晶的材质区分必须比地图中更清楚。

#### 阶段10-03 图鉴卡：冷凝胶
- 用途：资源图鉴展示。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：3:4。
- 背景：完整构图。
- 命名建议：`phase10_codex_condense_gel`.
- 生图顺序：壳晶矿图鉴卡之后。
- 统一风格检查点：透明感提升，但轮廓依然明确。
- 提示词：
```text
Use case: stylized-concept
Asset type: codex card illustration for "Deep Tide Station"
Primary request: create a codex-style presentation illustration for Condense Gel
Scene/backdrop: clean analysis-display background with subtle tech framing and specimen-safe space, no text
Subject: Condense Gel presented as a dense cold deep-sea material specimen with readable translucency and internal flow
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft display lighting emphasizing inner flow and controlled translucency
Palette: ice blue, cyan, teal, cold white, muted blue-gray support hues
Composition: vertical codex presentation with centered specimen and calm analytic atmosphere
Output expectation: one codex-card-ready image for Condense Gel
Constraints: no text, no watermark, no fantasy slime bestiary look, no poster clutter, no copied codex page
Negative prompt: photorealistic, goo photo, slime monster card, copied laboratory card art, clutter
```
- 后处理：透明边缘要干净。

#### 阶段10-04 图鉴卡：旧时代零件
- 用途：资源图鉴展示。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：3:4。
- 背景：完整构图。
- 命名建议：`phase10_codex_old_parts`.
- 生图顺序：冷凝胶图鉴卡之后。
- 统一风格检查点：呈现“遗留科技部件”而不是杂乱废品。
- 提示词：
```text
Use case: stylized-concept
Asset type: codex card illustration for "Deep Tide Station"
Primary request: create a codex-style presentation illustration for Old-Era Parts
Scene/backdrop: clean archive-display background with subtle engineering framing and specimen-safe layout, no text
Subject: a curated high-readability presentation of Old-Era Parts as preserved deep-sea salvage technology fragments
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: controlled showcase lighting with crisp industrial edge highlights
Palette: steel gray, dark blue metal, cyan ports, muted teal, small orange markings
Composition: vertical codex layout with a clearly centered mechanical specimen and open margins
Output expectation: one codex-card-ready image for Old-Era Parts
Constraints: no text, no watermark, no junkyard clutter, no poster composition, no copied codex design
Negative prompt: photorealistic, scrap catalog photo, fantasy relic card, copied technology archive art, clutter
```
- 后处理：比资源掉落图更完整、更整齐。

#### 阶段10-05 图鉴卡：电弧鳐
- 用途：敌对生物图鉴展示。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：3:4。
- 背景：完整构图。
- 命名建议：`phase10_codex_arc_ray`.
- 生图顺序：资源图鉴卡完成后。
- 统一风格检查点：危险感与物种展示要平衡。
- 提示词：
```text
Use case: stylized-concept
Asset type: codex card illustration for "Deep Tide Station"
Primary request: create a codex-style presentation illustration for Arc Ray
Scene/backdrop: clean analysis-display background with subtle hazard-study framing and a specimen-safe composition, no text
Subject: Arc Ray presented as a cataloged hostile deep-sea species with visible electric anatomy cues
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: controlled specimen-display lighting with focused electric-edge highlights
Palette: deep teal, navy, bright cyan electric accents, pale white sparks
Composition: vertical codex layout with the creature centered and fully readable as a study subject
Output expectation: one codex-card-ready image for Arc Ray
Constraints: no text, no watermark, no horror anatomy page, no gore, no copied bestiary design
Negative prompt: photorealistic, aquarium poster, alien horror catalog, copied creature card art, clutter
```
- 后处理：更像“记录对象”，不是“战斗海报”。

#### 阶段10-06 图鉴卡：裂壳螺
- 用途：敌对生物图鉴展示。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：3:4。
- 背景：完整构图。
- 命名建议：`phase10_codex_crack_snail`.
- 生图顺序：电弧鳐图鉴卡之后。
- 统一风格检查点：突出壳体与危险机制。
- 提示词：
```text
Use case: stylized-concept
Asset type: codex card illustration for "Deep Tide Station"
Primary request: create a codex-style presentation illustration for Crack Shell Snail
Scene/backdrop: clean archive-study background with subtle hazard framing and centered specimen-safe area, no text
Subject: Crack Shell Snail presented as a cataloged ambush organism with shell fracture patterns and attack-readiness cues
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft specimen light with shell-readability emphasis and restrained seam glow
Palette: shell gray, dark teal, blue-gray, faint cyan seam highlights
Composition: vertical codex layout with the heavy shell creature clearly centered and readable
Output expectation: one codex-card-ready image for Crack Shell Snail
Constraints: no text, no watermark, no gore, no body-horror study sheet, no copied codex art
Negative prompt: photorealistic, mollusk photo board, horror parasite page, copied creature-card design, clutter
```
- 后处理：壳裂纹要成为识别点。

#### 阶段10-07 图鉴卡：脉冲水母群
- 用途：敌对生物图鉴展示。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：3:4。
- 背景：完整构图。
- 命名建议：`phase10_codex_pulse_jelly`.
- 生图顺序：裂壳螺图鉴卡之后。
- 统一风格检查点：强调群体感。
- 提示词：
```text
Use case: stylized-concept
Asset type: codex card illustration for "Deep Tide Station"
Primary request: create a codex-style presentation illustration for Pulse Jelly Group
Scene/backdrop: clean analysis-display background with subtle bio-luminescent study framing and no text
Subject: Pulse Jelly Group shown as a clustered hazardous species rather than a single giant specimen
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft display lighting with synchronized pulse emphasis and transparent edge readability
Palette: pale cyan, blue, muted violet-blue, cold white pulse highlights
Composition: vertical codex layout with the grouped specimen centered and clearly collective
Output expectation: one codex-card-ready image for Pulse Jelly Group
Constraints: no text, no watermark, no single giant jellyfish hero shot, no horror tendril focus, no copied card design
Negative prompt: photorealistic, aquarium exhibit photo, alien horror swarm, copied bestiary page, clutter
```
- 后处理：图鉴上也必须是“一群”，不能偷懒画成一只。

#### 阶段10-08 横版游戏封面
- 用途：README、仓库头图、展示封面。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整构图。
- 命名建议：`phase10_cover_landscape`.
- 生图顺序：图鉴卡之后。
- 统一风格检查点：包含主角、资源、海域、风险，但不堆满。
- 提示词：
```text
Use case: ads-marketing
Asset type: landscape cover art for "Deep Tide Station"
Primary request: create a wide cover image summarizing the game's core fantasy: dive, collect, return, upgrade
Scene/backdrop: player sub in a readable deep-sea scene, glowing resources, industrial ruins, layered underwater terrain, and subtle hostile presence
Subject: a premium but still game-consistent cover image for an original deep-sea salvage title
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: polished cover-art lighting while remaining consistent with underwater diffuse logic
Palette: navy, teal, cyan glow, blue-gray terrain, tiny orange warning accents
Composition: cinematic but controlled wide composition with clear title-safe zone and readable focal hierarchy
Output expectation: one landscape key art suitable for repository cover and presentations
Constraints: no text, no watermark, no copied box-art layout, no overstuffed collage, no fantasy tone
Negative prompt: photorealistic, movie poster, copied indie game cover, cyberpunk neon overload, clutter
```
- 后处理：要能代表游戏，但不能脱离游戏内审美。

#### 阶段10-09 竖版游戏封面
- 用途：PPT 首页、展示板、竖版宣传。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：4:5。
- 背景：完整构图。
- 命名建议：`phase10_cover_portrait`.
- 生图顺序：横版封面之后。
- 统一风格检查点：竖版更聚焦主角与深度层次。
- 提示词：
```text
Use case: ads-marketing
Asset type: portrait cover art for "Deep Tide Station"
Primary request: create a portrait-oriented cover image centered on descending into deeper waters
Scene/backdrop: the player sub descending through layered sea zones with resource glow, industrial remnants, and depth pressure increasing downward
Subject: a vertical key art expressing progression from surface operations into the deep
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: polished cover-art lighting with a readable vertical depth gradient
Palette: navy, deep blue, teal, cyan highlights, muted gray, tiny orange guidance accents
Composition: strong vertical descent composition with title-safe upper area and readable focal subject
Output expectation: one portrait key art for slides, posters, and report covers
Constraints: no text, no watermark, no movie-poster exaggeration, no collage overload, no fantasy temple vibe
Negative prompt: photorealistic, blockbuster poster, copied indie game portrait art, neon overload, clutter
```
- 后处理：重点放在“向下探索”的纵向叙事。

#### 阶段10-10 商店页头图
- 用途：资源站、展示页面横幅、封面图。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整构图。
- 命名建议：`phase10_store_header`.
- 生图顺序：竖版封面之后。
- 统一风格检查点：简洁、抓眼、标题安全区大。
- 提示词：
```text
Use case: ads-marketing
Asset type: store header image for "Deep Tide Station"
Primary request: create a clean promotional header image for storefront-like or project showcase use
Scene/backdrop: a readable underwater salvage scene with the player sub, one or two iconic resources, and a controlled industrial backdrop
Subject: a concise promotional banner for the game's identity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: polished but restrained underwater showcase lighting
Palette: navy, steel blue, teal, cyan glow, limited orange accents
Composition: wide banner with a large title-safe area and a single strong focal cluster
Output expectation: one storefront-style header image that remains faithful to the game art
Constraints: no text, no watermark, no clutter, no movie-poster collage, no copied banner style
Negative prompt: photorealistic, ad-banner stock art, fantasy key art, copied storefront images, neon overload
```
- 后处理：右侧或左侧预留标题区。

#### 阶段10-11 视频封面图
- 用途：课程讲解视频封面、B 站或网盘预览图。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整构图。
- 命名建议：`phase10_video_thumb`.
- 生图顺序：商店头图之后。
- 统一风格检查点：强缩略图识别力。
- 提示词：
```text
Use case: ads-marketing
Asset type: video thumbnail art for "Deep Tide Station"
Primary request: create a high-readability thumbnail image for a project demo or explanation video
Scene/backdrop: player sub in a striking but readable underwater salvage moment with one strong resource glow and one environmental risk cue
Subject: a thumbnail-friendly key frame representing the game clearly at small size
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: slightly stronger focal contrast while preserving the game's underwater logic
Palette: deep blue, teal, cyan glow, steel gray, minimal orange warning accents
Composition: wide thumbnail composition with one dominant focal subject and title-safe area
Output expectation: one thumbnail-ready promotional frame for video use
Constraints: no text, no watermark, no clutter, no micro-detail dependence, no copied thumbnail style
Negative prompt: photorealistic, clickbait poster, fantasy battle art, copied game thumbnail, visual noise
```
- 后处理：缩到小图时仍要看得出潜水器和资源。

#### 阶段10-12 宣传总海报
- 用途：最终展示、大作业答辩、项目汇总图。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：4:5 或 16:9。
- 背景：完整构图。
- 命名建议：`phase10_master_poster`.
- 生图顺序：本阶段最后。
- 统一风格检查点：是总海报，但不能像拼贴墙。
- 提示词：
```text
Use case: ads-marketing
Asset type: master poster art for "Deep Tide Station"
Primary request: create a final poster-style image summarizing the world, player vehicle, resources, danger, and recovery-station identity
Scene/backdrop: layered underwater salvage composition with the player sub, key resources, industrial ruins, and subtle hostile silhouettes arranged cleanly
Subject: a premium master poster for an original deep-sea salvage game project
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: polished presentation lighting while preserving consistent underwater atmosphere
Palette: navy, teal, cyan glow, steel gray, controlled orange accents
Composition: polished multi-layer composition with clear focal hierarchy and presentation-safe negative space
Output expectation: one final showcase poster suitable for report covers and project presentation
Constraints: no text, no watermark, no movie-poster chaos, no copied key-art layout, no overcrowding
Negative prompt: photorealistic, blockbuster poster, fantasy splash art, copied indie game poster, visual overload
```
- 后处理：这是总展示图，但必须还能看出游戏真实风格，而非完全脱离实机。

---

## 18. 最终统一质检标准

每张图都按以下项目检查：

1. 是否属于 `深潮回收站` 世界。
2. 是否保持 2D 横版侧视可读性。
3. 是否仍在统一色板里。
4. 是否仍然使用统一材质语言。
5. 是否没有出现明显现成 IP 既视感。
6. 是否能在缩小后读出轮廓。
7. 是否能和 UI、场景、资源一起共存。
8. 是否没有过量发光。
9. 是否没有不必要的复杂纹理。
10. 是否预留了功能使用空间。

### 18.1 主角类检查

- 待机、移动、受击、返航是否是同一机体。
- 灯光变化是否清楚但不过量。
- 推进器是否像水下推进而不是火箭。
- 升级状态是否只是功能变化，不是整机换模型。

### 18.2 资源类检查

- 普通、稀有、珍贵是否是同一家族。
- 稀有度差异是否主要靠发光、结构完整度、细节强调。
- 是否能在地图尺寸下快速看懂。
- 是否不会和地形混在一起。

### 18.3 场景类检查

- 是否预留玩家移动区域。
- 是否预留 HUD 与文字覆盖区域。
- 是否存在前中后景分层。
- 是否不会把资源和敌人吃掉。

### 18.4 UI 类检查

- 是否与 UI 母图一致。
- 主按钮与次按钮是否一眼能区分。
- 图标是否小尺寸可读。
- 稀有度边框是否不遮挡主图。

### 18.5 特效类检查

- 特效大小是否合理。
- 是否会淹没主体。
- 是否和同类特效区分清楚。
- 是否仍属于工业科幻水下语义。

### 18.6 宣传图检查

- 是否还是这个游戏的风格。
- 是否不需要依赖文字也能看懂主题。
- 是否比实机图更完整但不过分夸张。
- 是否可用于课程展示而不显得抄袭现成作品。

---

## 19. 常见返工原因

### 19.1 最常见的 10 个返工点

1. 风格母图没先锁，后面全漂。
2. 资源发光太强，进场景后像 UI。
3. 地形细节太多，玩家轮廓被吃掉。
4. 主角每个状态都像另一台载具。
5. 热泉区被画成火山熔岩世界。
6. 冷流区被画成纯黑恐怖片。
7. UI 太像手机 APP。
8. 敌人太 horror，不适合课程展示。
9. 宣传图比游戏内风格还另起一套。
10. 提示词没有统一风格锚点。

### 19.2 看到这些现象就该重做

- 出现紫色主导霓虹赛博风。
- 出现大量金色、暖色主导。
- 出现现代军武潜艇感。
- 出现写实照片纹理。
- 出现日漫角色脸。
- 出现过多发光烟雾。
- 出现魔法阵、法术环、奇幻符文。
- 出现明显像某个现成游戏角色或敌人。

---

## 20. 资产命名建议

### 20.1 阶段命名法

- `phase0_`
- `phase1_`
- `phase2_`
- `phase3_`
- `phase4_`
- `phase5_`
- `phase6_`
- `phase7_`
- `phase8_`
- `phase9_`
- `phase10_`

### 20.2 推荐文件命名例子

- `phase1_player_sub_idle.png`
- `phase2_glow_cluster_common.png`
- `phase2_glow_cluster_rare.png`
- `phase4_zone2_main_a.png`
- `phase6_arc_ray_attack.png`
- `phase8_button_primary_hover.png`
- `phase9_fx_collect_flash.png`
- `phase10_master_poster.png`

### 20.3 版本命名法

- 初稿：`_v1`
- 调整版：`_v2`
- 最终版：`_final`

### 20.4 推荐目录

```text
assets/
  images/
    concept/
    player/
    resources/
    upgrades/
    backgrounds/
    props/
    enemies/
    ui/
    effects/
    promo/
```

---

## 21. 最后执行建议

### 21.1 真正的执行顺序

如果你现在就要开始跑图，不要从 132 个条目一起开工，先这样：

1. 阶段0-01 到 阶段0-12 全做完。
2. 阶段1-01、阶段1-03、阶段1-04 先做。
3. 阶段2-01、阶段2-04、阶段2-07、阶段2-10 先做普通版。
4. 阶段4-03 先做第一海域主背景 A。
5. 阶段7-02 先做基地主界面背景。
6. 阶段8-01、阶段8-02、阶段8-07 先做 HUD 与主按钮。

### 21.2 第一批最小可用资产

最小可用包建议只先生成这些：

- 风格母图 A
- UI 母图
- 主角潜水器待机
- 主角潜水器推进
- 荧团浮体普通
- 壳晶矿普通
- 冷凝胶普通
- 旧时代零件普通
- 浅海断层区主背景 A
- 基地主界面背景
- HUD 图标组
- 氧气条

### 21.3 第一批确认后再批量扩展

只有当下面条件都满足，你才进入第二批：

- 主角风格稳定
- 资源风格稳定
- 背景风格稳定
- UI 风格稳定
- 颜色没有漂
- 轮廓没有糊

### 21.4 你之后怎么把需求发给我最省事

你后面每次直接按这个模板发：

```text
请按《deep_tide_image_generation_guide.md》里的统一风格生成：
1. 阶段编号：
2. 资产编号：
3. 数量：
4. 是否要透明背景：
5. 是否要一张图内含多变体：
6. 是否沿用已确认母风格：
7. 是否要我直接帮你出图：
```

例子：

```text
请按《deep_tide_image_generation_guide.md》里的统一风格生成：
1. 阶段编号：2
2. 资产编号：阶段2-01 到 阶段2-03
3. 数量：每个 1 张，共 3 张
4. 是否要透明背景：是
5. 是否要一张图内含多变体：否
6. 是否沿用已确认母风格：是
7. 是否要我直接帮你出图：是
```

---

## 22. 文档结论

这份文档的核心不是“给你 132 条散乱提示词”，而是把整个项目的美术生产流程固定下来：

1. 先锁母风格。
2. 再锁主角与资源。
3. 再锁场景与风险。
4. 再锁 UI 与特效。
5. 最后做图鉴与宣传图。

只要你严格按这个顺序做，整个《深潮回收站》的美术就不会散。

---

## 23. 附录 A：批量生图工单模板

这一部分不是新的资产清单，而是给你后续批量跑图时直接复制粘贴的工单模板。

你可以把下面每一段直接发给我，或者直接喂给你使用的 AI 生图工具。

### 23.1 阶段 0 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 0 的风格锁定图。
项目名：深潮回收站
阶段：0
目标：锁定全项目统一风格
优先级：最高
需要生成的资产：
1. 风格母图 A
2. 风格母图 B
3. 统一色板图
4. 材质语言图
5. 轮廓语言图
6. 水下光照体积感图
7. 基地气质参考图
8. 浅海断层区气质图
9. 热泉区气质图
10. 冷流峡谷区气质图
11. 风险生物群气质图
12. UI 风格母图
统一风格锚点：原创 2D 横版侧视深海回收站游戏，半风格化工业科幻，深蓝冷青主色，荧光青绿发光点缀，少量安全橙，清晰轮廓，克制纹理，可读性优先
统一限制：不要文字，不要水印，不要 logo，不要抄任何现成游戏，不要写实照片感，不要像电影海报，不要奇幻魔法风
输出要求：每个资产先出 4 张初稿，再从中选 1 张精修
```

### 23.2 阶段 1 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 1 的主角与潜水器资产。
项目名：深潮回收站
阶段：1
目标：锁定主角潜水器系列
优先级：最高
需要生成的资产：
1. 主角潜水器基础待机图
2. 主角潜水器前灯开启图
3. 主角潜水器推进状态图
4. 主角潜水器受击状态图
5. 主角潜水器低氧警报状态图
6. 主角潜水器满载货舱状态图
7. 机械臂展开状态图
8. 扫描器展开状态图
9. 返航状态图
10. 海面停靠状态图
11. 潜航员剪影备用图
12. 潜水器概念页
统一风格锚点：原创深海工业小型回收潜水器，2D 侧视，可爱但可靠，功能明确，不像军用潜艇，不像机甲
统一限制：除概念页外全部使用纯 #00ff00 背景用于抠图，不要场景，不要额外角色，不要写实军武感
输出要求：所有状态必须是同一台潜水器，不允许每张都换设计
```

### 23.3 阶段 2 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 2 的资源体系。
项目名：深潮回收站
阶段：2
目标：锁定四大核心资源与稀有度体系
优先级：高
需要生成的资产：
1. 荧团浮体普通版
2. 荧团浮体稀有版
3. 荧团浮体珍贵版
4. 壳晶矿普通版
5. 壳晶矿稀有版
6. 壳晶矿珍贵版
7. 冷凝胶普通版
8. 冷凝胶稀有版
9. 冷凝胶珍贵版
10. 旧时代零件普通版
11. 旧时代零件稀有版
12. 旧时代零件珍贵版
统一风格锚点：原创深海资源，轮廓大，发光克制，普通版弱、稀有版强、珍贵版最完整，但必须保持同家族结构
统一限制：全部使用纯 #00ff00 背景，不要场景，不要文字，不要拟人化，不要怪物化
输出要求：同类资源三档一起做，避免风格漂移
```

### 23.4 阶段 3 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 3 的升级模块与工具。
项目名：深潮回收站
阶段：3
目标：锁定成长反馈视觉
优先级：高
需要生成的资产：
1. 压缩气瓶模块
2. 推进器模块
3. 货舱扩展模块
4. 机械臂效率模块
5. 扫描阵列模块
6. 耐压外壳模块
7. 备用氧包
8. 修复焊枪
9. 声呐标记浮标
10. 返航信标
11. 深度许可证芯片
12. 工坊零件包
统一风格锚点：工业科幻深海作业工具，模块化，功能明确，适合放进升级界面和图标卡片
统一限制：纯 #00ff00 背景，不要武器感，不要现代商店产品图，不要军火库风格
输出要求：永久模块和一次性工具在尺度、结构和复杂度上要分层
```

### 23.5 阶段 4 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 4 的海域背景。
项目名：深潮回收站
阶段：4
目标：锁定海域推进视觉层次
优先级：高
需要生成的资产：
1. 海面基地远景
2. 出航转场海面图
3. 浅海断层区主背景 A
4. 浅海断层区主背景 B
5. 热泉区主背景 A
6. 热泉区主背景 B
7. 冷流峡谷区主背景 A
8. 冷流峡谷区主背景 B
9. 深渊遗迹区主背景 A
10. 深渊遗迹区主背景 B
11. 海底远景装饰层
12. 海底近景遮罩层
统一风格锚点：2D 侧视游戏背景，前中后景分明，玩法区域清楚，不做电影海报式满屏细节
统一限制：不要文字，不要 UI，不要把画面中心塞满，不要过度黑暗，不要奇幻遗迹
输出要求：同海域至少两张不同结构背景，确保路线感和地标差异
```

### 23.6 阶段 5 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 5 的地形与场景道具。
项目名：深潮回收站
阶段：5
目标：锁定可拼接地图元素与交互道具
优先级：中高
需要生成的资产：
1. 岩壁块
2. 断裂平台
3. 壳晶附着岩面
4. 热泉喷口
5. 冷流喷口
6. 深裂缝
7. 废弃金属梁
8. 回收容器箱
9. 浮标灯塔
10. 海底管道残骸
11. 黑暗区边缘标识
12. 可交互遗迹容器
统一风格锚点：模块化 2D 地形与工业遗迹道具，轮廓清晰，可拼可叠，可配碰撞盒
统一限制：单体用纯 #00ff00 背景，不要一整张场景，不要写实垃圾堆质感
输出要求：优先做能重复使用的基础件
```

### 23.7 阶段 6 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 6 的危险生物与风险体。
项目名：深潮回收站
阶段：6
目标：锁定主危险单位与状态变化
优先级：中高
需要生成的资产：
1. 电弧鳐巡游态
2. 电弧鳐蓄电态
3. 电弧鳐放电态
4. 裂壳螺闭壳态
5. 裂壳螺攻击态
6. 裂壳螺破碎态
7. 脉冲水母群静态
8. 脉冲水母群脉冲态
9. 脉冲水母群追随态
10. 危险浮游刺群
11. 异常机械寄生体
12. 深渊观测眼
统一风格锚点：深海异常生物，危险但不恐怖，不血腥，不克苏鲁化，工业世界兼容
统一限制：纯 #00ff00 背景，不要场景，不要 gore，不要恶心口器特写
输出要求：同一生物状态必须保持同一轮廓家族
```

### 23.8 阶段 7 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 7 的基地与功能界面场景。
项目名：深潮回收站
阶段：7
目标：锁定功能界面世界观
优先级：高
需要生成的资产：
1. 开始菜单背景
2. 基地主界面背景
3. 结算台背景
4. 升级工坊背景
5. 图鉴室背景
6. 海域选择界面背景
7. 暂停菜单背景
8. 失败界面背景
9. 成功返航界面背景
10. 深度许可证界面背景
11. 存档界面背景
12. 教学说明界面背景
统一风格锚点：海面回收站内部外部空间，工业科幻工作区，界面叠加安全区清楚
统一限制：不要直接把文字印在底图上，不要把中心做满，不要做成人物插画页
输出要求：每张背景都要预留信息展示区
```

### 23.9 阶段 8 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 8 的 HUD 与 UI 控件。
项目名：深潮回收站
阶段：8
目标：锁定高频信息层和交互层
优先级：高
需要生成的资产：
1. HUD 图标组
2. 氧气条
3. 耐久条
4. 深度显示框
5. 背包格子
6. 稀有度边框三种
7. 主按钮四状态
8. 次按钮四状态
9. 海域锁定标记
10. 采集交互提示
11. 返航提示
12. 升级卡片底板
统一风格锚点：回收站设备 UI，工业科技感，结构清楚，不像手机 APP，不像奇幻游戏 HUD
统一限制：推荐透明背景或纯 #00ff00 抠图底，不要文字，不要表情包风格
输出要求：所有 UI 元素要同一边角、同一高光、同一阴影逻辑
```

### 23.10 阶段 9 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 9 的特效与动画参考。
项目名：深潮回收站
阶段：9
目标：锁定交互反馈层
优先级：中高
需要生成的资产：
1. 采集成功闪光
2. 低氧警报环
3. 受击电火花
4. 推进尾流
5. 扫描脉冲圈
6. 热泉气泡柱
7. 冷流拖尾
8. 放电爆闪
9. 返航高光柱
10. 稀有资源掉落光
11. 爆裂碎片特效
12. 水下颗粒环境特效
统一风格锚点：工业科幻水下反馈特效，短促、集中、清楚，服务玩法，不抢主体
统一限制：推荐透明背景或纯 #00ff00 抠图底，不要烟花，不要魔法，不要全屏炫光
输出要求：效果本体与主资产分层
```

### 23.11 阶段 10 批量工单模板

```text
请按《deep_tide_image_generation_guide.md》的统一风格规则，批量生成阶段 10 的图鉴与宣传图。
项目名：深潮回收站
阶段：10
目标：锁定展示层与汇报层
优先级：中
需要生成的资产：
1. 图鉴卡：荧团浮体
2. 图鉴卡：壳晶矿
3. 图鉴卡：冷凝胶
4. 图鉴卡：旧时代零件
5. 图鉴卡：电弧鳐
6. 图鉴卡：裂壳螺
7. 图鉴卡：脉冲水母群
8. 横版游戏封面
9. 竖版游戏封面
10. 商店页头图
11. 视频封面图
12. 宣传总海报
统一风格锚点：比实机图更完整、更展示化，但仍然属于同一项目，不另起一套美术
统一限制：不要文字，不要水印，不要像商品包装，不要像电影海报
输出要求：重点保证和游戏内实际素材风格连贯
```

---

## 24. 附录 B：二次修图短指令库

这一部分用于你第一次生图不满意时的二次追加提示词。

你可以把这些短句直接加在原提示词末尾。

### 24.1 轮廓修正短句

- 请把主体轮廓做得更大更清楚。
- 请减少边缘碎细节，让轮廓更完整。
- 请让主体在缩小后仍然易读。
- 请增强大中小体块关系。
- 请减少细长触手与零碎外伸结构。
- 请让外轮廓更稳定，不要锯齿状破碎。
- 请让顶部和底部方向更明确。
- 请让结构更适合 2D 横版侧视使用。
- 请减少不必要的内部纹理，让主要轮廓先成立。
- 请让主体更像游戏资产，不像插画局部。

### 24.2 颜色修正短句

- 请回到深蓝、冷青、青绿主色系统。
- 请减少暖色面积。
- 请把橙色限制在警示细节上。
- 请降低高饱和霓虹感。
- 请减少紫色倾向。
- 请让颜色更克制，更偏工业水下设备。
- 请降低彩虹色变化，只保留核心色板。
- 请让发光色更偏冷白青，而不是纯白或纯绿。
- 请让背景更降饱和，主体更清晰。
- 请让资源和场景的颜色分离更明显。

### 24.3 发光修正短句

- 请减少整体泛光，只保留局部发光核心。
- 请让发光更集中，不要铺满主体。
- 请让发光边缘更干净。
- 请减少 bloom。
- 请让发光成为价值提示，而不是照明主来源。
- 请让普通版发光弱一些。
- 请让稀有版发光增强但不扩大主体体积。
- 请让珍贵版更像高纯度核心，而不是发光烟雾团。
- 请减少场景背景中的发光点密度。
- 请让 UI 发光更克制，避免像霓虹招牌。

### 24.4 材质修正短句

- 请减少照片贴图感。
- 请让金属表面更简洁。
- 请让岩石块面更明确。
- 请让晶体和壳体材质区分更明显。
- 请让凝胶更“凝”，不要像液体泼洒。
- 请让表面磨损更轻，不要脏污过度。
- 请减少随机噪点。
- 请让材质更偏手绘游戏资产，而不是写实扫描件。
- 请让工业件更像深海设备，不像现代家电零件。
- 请减少镜面反射。

### 24.5 主角修正短句

- 请保持与基础待机版完全同一机体比例。
- 请不要换掉主角潜水器的主体结构。
- 请保留前灯、机械臂、氧气仓和推进器的逻辑位置。
- 请让主角更小巧，不要变成大型军用潜艇。
- 请让主角更像回收作业载具，而不是战斗载具。
- 请减少武器感。
- 请让升级版只增加功能件，不改变主机轮廓家族。
- 请让推进状态更像水下推进而不是火箭喷射。
- 请让受击状态更轻，不要做成爆炸损坏。
- 请让返航状态的导航感更强。

### 24.6 资源修正短句

- 请让它更像资源，不像生物。
- 请让它更像附着型矿物，不像独立怪物。
- 请让它更像深海胶质材料，不像玩具果冻。
- 请让它更像回收零件，不像垃圾堆。
- 请保留同类资源不同稀有度的家族关系。
- 请让普通版更朴素。
- 请让稀有版更完整。
- 请让珍贵版更高级，但不要重画成另一类资源。
- 请减小资源尺寸感，方便地图摆放。
- 请确保资源与地形颜色拉开差异。

### 24.7 场景修正短句

- 请给玩家活动区域留更多空白。
- 请减少背景细节密度。
- 请拉开前中后景层次。
- 请让中景更适合玩法。
- 请减少中心区域视觉噪声。
- 请把主要地标移到侧方或边缘。
- 请让海域差异更明显。
- 请让第一海域更友好。
- 请让第二海域更危险但仍然清楚。
- 请让第三海域更压迫但不要变黑。
- 请让遗迹区更像工业遗迹而不是古神殿。
- 请让近景遮罩不要挡住角色。

### 24.8 UI 修正短句

- 请让 UI 更像设备面板，不像手机应用。
- 请减少 glossy 质感。
- 请让按钮状态变化更明确。
- 请让主按钮和次按钮拉开优先级。
- 请让图标更适合小尺寸显示。
- 请让卡片留出更多文字区域。
- 请让数字显示区更大。
- 请减少装饰边框厚度。
- 请减少不必要的高光层。
- 请保持圆角和边框结构统一。

### 24.9 特效修正短句

- 请让特效更短促。
- 请让特效更集中。
- 请减少扩散半径。
- 请不要覆盖主体轮廓。
- 请减少烟雾和雾化。
- 请让特效更像工业反馈而不是魔法。
- 请让推进尾流更像水流。
- 请让扫描波更像科技探测。
- 请让电击更清晰但不要满屏闪。
- 请让返航高光更柔和、更安全。

### 24.10 宣传图修正短句

- 请让宣传图更接近游戏内实际风格。
- 请减少海报拼贴感。
- 请保留标题安全区。
- 请减少过度电影感。
- 请让主角更突出。
- 请让资源和风险作为辅助信息，不要平均分散注意力。
- 请让深海工业感更强。
- 请减少不属于实机世界的额外元素。
- 请让纵向深度叙事更清楚。
- 请让缩略图识别度更高。

---

## 25. 附录 C：人工筛图打分表

你每出一批图，都可以按这个表手动打分。

每项 `0-5` 分。

总分建议：

- `45 分以下`：直接重做
- `46-60 分`：可修
- `61-75 分`：可用
- `76 分以上`：可定稿

### 25.1 通用评分项

1. 轮廓清晰度
2. 小尺寸可读性
3. 色板一致性
4. 材质统一性
5. 发光控制
6. 原创辨识度
7. 与项目世界观一致性
8. 是否适合 2D 侧视使用
9. 是否方便切图
10. 是否没有多余背景干扰

### 25.2 主角类评分项

1. 是否像同一台潜水器
2. 是否不像军武潜艇
3. 是否不像机甲
4. 是否有明确功能结构
5. 是否有主角感
6. 是否可爱但不过幼
7. 是否推进逻辑明确
8. 是否受击反馈明确
9. 是否灯光层级合理
10. 是否适合做多个状态变体

### 25.3 资源类评分项

1. 是否一眼能认出是资源
2. 是否和敌人不混
3. 是否和地形不混
4. 是否三档稀有度差异清楚
5. 是否同家族统一
6. 是否发光不过量
7. 是否可以叠图标框
8. 是否切图安全
9. 是否放进地图会醒目
10. 是否不需要文字解释就能看懂价值层次

### 25.4 场景类评分项

1. 是否有前中后景
2. 是否有路线感
3. 是否给主角留活动空间
4. 是否给资源留摆放空间
5. 是否给 UI 留覆盖空间
6. 是否色彩不过黑
7. 是否细节不过量
8. 是否地标可记忆
9. 是否符合对应海域定位
10. 是否与其他海域差异明显

### 25.5 UI 类评分项

1. 是否像回收站设备 UI
2. 是否不手机化
3. 是否不奇幻化
4. 是否按钮优先级清楚
5. 是否图标清晰
6. 是否卡片布局合理
7. 是否能承载后续文字
8. 是否高频阅读不累
9. 是否和背景不打架
10. 是否风格稳定可批量扩展

### 25.6 特效类评分项

1. 是否不压主体
2. 是否时长感明确
3. 是否方向感明确
4. 是否高亮集中
5. 是否冷色体系稳定
6. 是否危险感或反馈感清楚
7. 是否可分层
8. 是否便于程序播放
9. 是否不魔法化
10. 是否足够干净

### 25.7 宣传图评分项

1. 是否一眼看出主题
2. 是否主角突出
3. 是否资源可见
4. 是否环境有代表性
5. 是否风险提示适度
6. 是否保留标题区
7. 是否不拼贴过度
8. 是否与实机风格统一
9. 是否适合课程展示
10. 是否有成品感

---

## 26. 附录 D：最终批量执行建议

### 26.1 如果你只有一天

只做这些：

- 阶段 0 全部
- 阶段 1 的 1、3、4
- 阶段 2 的四个普通版
- 阶段 4 的浅海断层区主背景 A
- 阶段 7 的基地主界面背景
- 阶段 8 的图标组和氧气条

### 26.2 如果你有三天

做这些：

- 阶段 0 全部
- 阶段 1 全部
- 阶段 2 全部
- 阶段 4 的第一、第二海域
- 阶段 5 的基础地形
- 阶段 7 的菜单、基地、结算、升级
- 阶段 8 的全部

### 26.3 如果你有一周

做这些：

- 阶段 0 到 阶段 9 全部
- 阶段 10 至少做图鉴卡与横版封面

### 26.4 如果你想让我直接开始生图

最推荐的第一轮实操顺序是：

1. 阶段0-01 风格母图 A
2. 阶段0-12 UI 风格母图
3. 阶段1-01 主角潜水器基础待机图
4. 阶段2-01 荧团浮体普通版
5. 阶段2-04 壳晶矿普通版
6. 阶段2-07 冷凝胶普通版
7. 阶段2-10 旧时代零件普通版
8. 阶段4-03 浅海断层区主背景 A
9. 阶段7-02 基地主界面背景
10. 阶段8-01 HUD 图标组

### 26.5 第一轮通过后再生这些

1. 阶段1-03 推进状态
2. 阶段1-04 受击状态
3. 阶段2 全部稀有版与珍贵版
4. 阶段6 的三大主敌
5. 阶段9 的核心特效

### 26.6 最后再生这些

1. 阶段4 其余背景
2. 阶段5 全部拼接道具
3. 阶段7 的其余功能界面
4. 阶段10 的图鉴卡与宣传图

---

## 27. 附录 E：快速替换词库

这一部分用于你不改整条提示词，只替换其中某一小段时使用。

### 27.1 可替换的主体定位词

- compact recovery submersible
- industrial deep-sea utility vehicle
- floating gel-like resource
- attached shell-crystal ore
- dense cold-current gel mass
- preserved old-era salvage module
- compact upgrade module
- navigation beacon device
- pressure-resistant structural part
- hostile electric ray creature
- ambush shell creature
- clustered pulse jelly group
- modular underwater terrain piece
- industrial station background
- codex presentation card
- compact UI icon set
- focused pickup flash effect
- controlled electric discharge effect

### 27.2 可替换的环境词

- shallow fault area
- thermal vent zone
- cold-current canyon
- abyssal ruins
- sea-surface recovery station
- salvage workshop
- settlement counter
- archive room
- mission planning station
- dim equipment corridor
- underwater open lane
- pressure-gate chamber

### 27.3 可替换的风险等级词

- safe-looking early-zone readability
- moderate mid-zone tension
- advanced late-zone pressure
- high-value danger cue
- ambush-grade threat
- swarm-level hazard
- environmental navigation risk
- controlled emergency warning
- late-game special threat
- rare progression pressure

### 27.4 可替换的轮廓词

- broad readable silhouette
- compact stable silhouette
- low-profile hazard silhouette
- tall signal-like silhouette
- dense heavy silhouette
- soft rounded silhouette
- layered modular silhouette
- premium refined silhouette
- narrow directional silhouette
- grouped collective silhouette

### 27.5 可替换的材质词

- restrained hand-painted metal
- soft translucent gel
- layered shell crust
- reinforced pressure-grade casing
- weathered but readable steel
- smooth deep-sea ceramic coating
- compact industrial rubber seals
- cold luminous crystal core
- matte blue-gray rock surface
- controlled brushed alloy finish

### 27.6 可替换的发光词

- faint inner cyan glow
- localized electric edge glow
- concentrated premium core glow
- subtle warning-light glow
- restrained scan-line glow
- small guidance-beam glow
- pulse-synced luminous core
- mild bioluminescent accent
- controlled instrument glow
- limited hazard-orange glow

### 27.7 可替换的构图词

- centered single subject
- wide side-view composition
- large title-safe area
- large card-safe area
- clear numeric-safe space
- clean icon-safe spacing
- route-safe open center
- left-right functional separation
- top-heavy vertical descent composition
- uncluttered middle gameplay space

### 27.8 可替换的画面密度词

- low visual density
- moderate structural density
- sparse support detail
- compact high-value detail
- restrained decoration
- gameplay-first spacing
- minimal background noise
- controlled secondary detail
- uncluttered negative space
- tidy production-friendly detail level

### 27.9 可替换的主色短语

- cool cyan-blue palette
- navy and teal palette
- blue-gray industrial palette
- deep navy with cyan glow
- steel blue and muted teal palette
- pale cyan with cold white highlights
- dark blue and gray structural palette
- controlled orange-warning accents

### 27.10 可替换的光照短语

- soft underwater diffuse light
- calm marine overcast light
- focused workshop task light
- subtle archive display light
- dim pressure-zone light
- controlled warning-state light
- premium showcase lighting
- low-intensity interface glow

### 27.11 可替换的限制短语

- no text
- no watermark
- no logo
- no copied franchise design
- no photorealism
- no fantasy ornament
- no app-store UI style
- no mobile glossy look
- no clutter
- no poster overload
- no gore
- no horror anatomy
- no giant bloom
- no full-screen smoke
- no environment
- no redesign of the base shape

### 27.12 可替换的稀有度短语

- common-tier version
- rare-tier version
- precious-tier version
- early-game collectible
- mid-value upgrade material
- premium late-game salvage
- high-purity variant
- preserved intact module

### 27.13 可替换的功能语义词

- built for collection interaction
- built for return guidance
- built for scan detection
- built for cargo expansion
- built for integrity upgrades
- built for oxygen support
- built for rare discovery feedback
- built for zone unlock progression

### 27.14 可替换的修图语义词

- make it cleaner
- make it more readable
- reduce detail density
- strengthen silhouette
- lower the glow intensity
- return to the cool palette
- reduce warm color usage
- make the structure feel more industrial
- make it more compact
- keep the same family design

### 27.15 推荐的追加句式

- keep the same core silhouette as the approved version
- make the rare version brighter but not larger
- keep the premium version more refined, not more chaotic
- reduce visual noise in the center area
- reserve a clean area for UI overlay
- make the object easier to cut out from the background
- keep the design suitable for a 2D side-view game
- avoid any resemblance to known commercial game assets

### 27.16 常用的组合模板一

```text
Please keep the same family silhouette as the approved version.
Reduce unnecessary detail.
Strengthen the main shape readability.
Return to the cool cyan-blue palette.
Keep glow localized and controlled.
Make it feel more industrial and less fantastical.
```

### 27.17 常用的组合模板二

```text
Please preserve the exact same base structure.
Only change the state expression.
Do not redesign the object.
Make the warning feel clearer.
Do not let the effect overpower the silhouette.
Keep it game-ready and easy to cut out.
```

### 27.18 常用的组合模板三

```text
Please make the scene more readable for gameplay.
Open more central movement space.
Reduce background clutter.
Keep the midground clear.
Preserve the underwater industrial atmosphere.
Do not turn this into a poster-like composition.
```

### 27.19 常用的组合模板四

```text
Please make the UI feel more like industrial equipment.
Reduce glossy mobile-app styling.
Keep the frame structure clean.
Make the button states more distinct.
Preserve the same corner language and glow logic.
```

### 27.20 常用的组合模板五

```text
Please make the effect shorter, tighter, and more focused.
Reduce spread radius.
Keep the effect readable on top of the main asset.
Avoid fantasy spell aesthetics.
Stay within the same cool color family.
```

---

## 10. 阶段 3：升级模块与工具

### 10.1 阶段目标

- 锁定成长反馈的视觉来源。
- 升级不只显示数值，也要能看见“装置升级了”。
- 所有模块都必须看起来属于同一套回收站工业体系。

### 10.2 阶段操作顺序

1. 先做基础永久升级模块。
2. 再做消耗品。
3. 再做功能道具。
4. 最后做许可证与工坊材料包。

### 10.3 本阶段总建议

- 单体资产统一纯 `#00ff00` 背景。
- 模块尽量保持正交侧视，方便 UI 或图鉴使用。
- 结构清晰大于细节炫技。

### 10.4 阶段条目

#### 阶段3-01 压缩气瓶模块
- 用途：对应氧气升级项。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_module_oxygen_tank`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：看起来像深海工业气瓶，不像现代潜店装备。
- 提示词：
```text
Use case: stylized-concept
Asset type: upgrade module cutout asset for "Deep Tide Station"
Primary request: create a compressed oxygen tank module used as a core permanent upgrade
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: compact industrial deep-sea oxygen compression unit with reinforced casing, pipes, valve logic, and readable upgrade-value silhouette
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with readable metal edges and restrained accent glow
Palette: steel blue, dark gray, cyan indicator light, muted teal, tiny orange safety labels
Composition: centered side-view module, isolated and easy to read in UI or workshop scenes
Output expectation: one production-friendly oxygen upgrade module consistent with the game world
Constraints: no text, no watermark, no modern scuba store look, no clutter, no environment
Negative prompt: photorealistic, real-world scuba tank photo, generic industrial prop, copied sci-fi oxygen canister
```
- 后处理：确认它单独放进升级面板时也能看清。

#### 阶段3-02 推进器模块
- 用途：对应移动速度或冲刺升级项。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_module_thruster`.
- 生图顺序：压缩气瓶之后。
- 统一风格检查点：必须像潜水器外接推进器，不像航天喷口。
- 提示词：
```text
Use case: stylized-concept
Asset type: upgrade module cutout asset for "Deep Tide Station"
Primary request: create a compact propulsion upgrade module for the player submersible
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a practical underwater thruster unit with intake, nozzle, protective housing, and industrial serviceable parts
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with controlled metallic highlights and faint energy accents
Palette: dark blue metal, gray housing, cyan power detail, teal edge lights, tiny orange markers
Composition: centered module with a stable silhouette readable at small size
Output expectation: one propulsion upgrade module for shop cards and workshop UI
Constraints: no text, no watermark, no rocket-engine look, no flame effects, no environment
Negative prompt: photorealistic, spaceship engine, racing turbo part, clutter, copied sci-fi thruster
```
- 后处理：推进器形体要能和气瓶一眼区分。

#### 阶段3-03 货舱扩展模块
- 用途：对应背包或货舱容量升级。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_module_cargo`.
- 生图顺序：推进器之后。
- 统一风格检查点：要传达“装更多”，不是只是一个箱子。
- 提示词：
```text
Use case: stylized-concept
Asset type: upgrade module cutout asset for "Deep Tide Station"
Primary request: create a cargo expansion module for increasing collection capacity
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: modular cargo pod with latch systems, reinforced brackets, compartment structure, and clear attachment points for the player submersible
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft industrial light with readable form highlights
Palette: blue gray, dark steel, muted teal, cyan indicators, tiny orange warning paint
Composition: centered module, broad readable volume, visually communicates storage capacity
Output expectation: one cargo-upgrade asset suitable for icons, cards, and workshop displays
Constraints: no text, no watermark, no generic shipping crate, no environment, no clutter
Negative prompt: photorealistic, wooden crate, military ammo box, copied sci-fi cargo pod, muddy silhouette
```
- 后处理：缩小后仍需看出“多舱体结构”。

#### 阶段3-04 机械臂效率模块
- 用途：对应采集效率升级。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_module_arm`.
- 生图顺序：货舱模块之后。
- 统一风格检查点：机械臂模块应简洁，不要机甲化。
- 提示词：
```text
Use case: stylized-concept
Asset type: upgrade module cutout asset for "Deep Tide Station"
Primary request: create an efficiency-focused recovery arm upgrade module
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: industrial manipulator arm segment with reinforced joints, gripping head, and compact serviceable mechanics
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with small mechanical highlights
Palette: gray metal, steel blue, cyan readout accents, muted teal, tiny orange safety paint
Composition: centered arm module with clear functional silhouette
Output expectation: one arm-upgrade asset usable in workshop and UI contexts
Constraints: no text, no watermark, no giant robot arm, no weapon style, no environment
Negative prompt: photorealistic, factory robot realism, anime mech arm, tangled wires, copied industrial arm design
```
- 后处理：机械臂末端功能头要易读。

#### 阶段3-05 扫描阵列模块
- 用途：对应探测范围升级。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_module_scanner`.
- 生图顺序：机械臂模块之后。
- 统一风格检查点：是深海扫描设备，不是雷达锅。
- 提示词：
```text
Use case: stylized-concept
Asset type: upgrade module cutout asset for "Deep Tide Station"
Primary request: create a compact scanner array module for resource detection upgrades
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: an underwater scanning module with compact antenna geometry, sensor fins, and instrument housing suited to a small salvage vehicle
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with subtle instrument glow
Palette: steel blue, dark gray, cyan scan accents, pale teal indicators, tiny orange warning details
Composition: centered module with a unique but compact silhouette
Output expectation: one scanner-upgrade asset clearly readable in UI and upgrade scenes
Constraints: no text, no watermark, no giant dish, no satellite look, no environment
Negative prompt: photorealistic, radar tower, spaceship sensor spam, clutter, copied scanner design
```
- 后处理：扫描设备的“技术感”要高于“武器感”。

#### 阶段3-06 耐压外壳模块
- 用途：对应结构耐久或深度抗压升级。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_module_hull`.
- 生图顺序：扫描阵列之后。
- 统一风格检查点：必须显得厚实可靠，但不要笨重到像装甲车。
- 提示词：
```text
Use case: stylized-concept
Asset type: upgrade module cutout asset for "Deep Tide Station"
Primary request: create a pressure-resistant hull upgrade module for deeper operation
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: reinforced hull plate set with structural ribs, sealing details, and deep-sea pressure design language
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft industrial light with emphasized edge readability on armor plates
Palette: dark steel blue, gray, muted teal, cyan indicator lines, tiny orange hazard marks
Composition: centered module with stable heavy silhouette and clear layered construction
Output expectation: one hull-upgrade asset suited for workshop cards and diagrams
Constraints: no text, no watermark, no tank armor fantasy, no environment, no clutter
Negative prompt: photorealistic, military vehicle armor, giant mech plating, copied sci-fi armor kit, muddy silhouette
```
- 后处理：注意“厚重”和“可爱”之间的平衡。

#### 阶段3-07 备用氧包
- 用途：一次性补氧消耗品。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_tool_backup_oxygen`.
- 生图顺序：永久升级模块完成后。
- 统一风格检查点：应是可携带消耗品，而不是永久模块。
- 提示词：
```text
Use case: stylized-concept
Asset type: consumable tool cutout asset for "Deep Tide Station"
Primary request: create a backup oxygen pack used as a one-time emergency consumable
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: compact emergency oxygen pack with hose port, pressure meter, and field-use industrial casing
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with readable field-use wear and small indicator accents
Palette: blue gray, steel gray, cyan gauge light, muted teal, orange warning stripes
Composition: centered compact consumable object that feels portable and valuable
Output expectation: one emergency oxygen item for inventory and UI use
Constraints: no text, no watermark, no full scuba tank look, no environment, no clutter
Negative prompt: photorealistic, medical oxygen tank realism, generic camping canister, copied sci-fi medkit
```
- 后处理：尺寸感要明显比永久气瓶模块更小。

#### 阶段3-08 修复焊枪
- 用途：修复、工坊、临时交互物。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_tool_welder`.
- 生图顺序：备用氧包之后。
- 统一风格检查点：是深海维护工具，不是武器。
- 提示词：
```text
Use case: stylized-concept
Asset type: tool cutout asset for "Deep Tide Station"
Primary request: create a compact underwater repair welder used for maintenance and salvage tasks
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: practical underwater welding and repair tool with insulated grip, nozzle head, and industrial field-service design
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with controlled metallic highlights
Palette: steel gray, deep blue handle, cyan indicator light, muted teal details, tiny orange safety labels
Composition: centered tool with readable handle-head relationship and clean silhouette
Output expectation: one maintenance-tool asset for workshop and item usage
Constraints: no text, no watermark, no gun styling, no environment, no clutter
Negative prompt: photorealistic, firearm silhouette, heavy industrial realism, copied plasma cutter designs, anime weapon
```
- 后处理：如果远看像枪，说明失败。

#### 阶段3-09 声呐标记浮标
- 用途：探路或定位用功能道具。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_tool_sonar_buoy`.
- 生图顺序：修复焊枪之后。
- 统一风格检查点：必须像海洋设备，而不是漂流瓶。
- 提示词：
```text
Use case: stylized-concept
Asset type: utility item cutout asset for "Deep Tide Station"
Primary request: create a sonar marker buoy used for navigation and location tagging
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: compact marine buoy device with emitter core, tether point, protective frame, and underwater industrial design
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with a small sonar-emitter glow
Palette: teal, blue gray, steel gray, cyan light, orange safety accents
Composition: centered buoy item with clear top-bottom orientation and readable shape
Output expectation: one utility buoy asset suitable for inventory or world placement
Constraints: no text, no watermark, no civilian life-buoy look, no environment, no clutter
Negative prompt: photorealistic, beach buoy, bottle, copied marine drone, muddy silhouette
```
- 后处理：确保一眼能认出这是“设备”，不是“装饰品”。

#### 阶段3-10 返航信标
- 用途：返航辅助功能道具或地图交互物。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_tool_return_beacon`.
- 生图顺序：声呐浮标之后。
- 统一风格检查点：导航功能比造型酷炫更重要。
- 提示词：
```text
Use case: stylized-concept
Asset type: utility beacon cutout asset for "Deep Tide Station"
Primary request: create a return-to-base guidance beacon device
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a compact navigation beacon with clear signal-light logic, industrial mounting points, and safe-return identity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with readable navigation light accents
Palette: steel blue, gray, teal, cyan guidance light, small orange warning paint
Composition: centered beacon device with stable directional silhouette and clear signal core
Output expectation: one return-guidance utility asset for UI, workshop, or map support
Constraints: no text, no watermark, no magic totem look, no environment, no clutter
Negative prompt: photorealistic, fantasy beacon, religious totem, copied sci-fi navigation node, messy design
```
- 后处理：如果看起来像法杖或祭坛，要重来。

#### 阶段3-11 深度许可证芯片
- 用途：海域解锁与许可证系统图标主体。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_item_depth_license`.
- 生图顺序：返航信标之后。
- 统一风格检查点：应像严肃的工业许可件，不像银行卡。
- 提示词：
```text
Use case: stylized-concept
Asset type: progression item cutout asset for "Deep Tide Station"
Primary request: create a depth-license chip item representing permission to access deeper zones
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a rugged industrial authorization chip or seal with pressure-grade framing and access-device logic
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with controlled edge highlights and small secure-access glow
Palette: dark blue, steel gray, cyan interface lines, muted teal, tiny orange security markings
Composition: centered authorization item with compact premium silhouette
Output expectation: one progression-item asset for zone unlock UI and settlement scenes
Constraints: no text, no watermark, no credit-card look, no environment, no clutter
Negative prompt: photorealistic, modern bank card, fantasy key, copied access-card designs, muddy silhouette
```
- 后处理：可做成卡或芯片，但必须更“耐压工业”。

#### 阶段3-12 工坊零件包
- 用途：升级界面、制作材料包、演示辅助素材。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase3_item_workshop_kit`.
- 生图顺序：本阶段最后。
- 统一风格检查点：是“模块包”，不是乱七八糟一堆垃圾。
- 提示词：
```text
Use case: stylized-concept
Asset type: crafting bundle cutout asset for "Deep Tide Station"
Primary request: create a workshop parts kit used for upgrades and maintenance
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a bundled set of organized industrial parts, sealed components, connectors, and repair pieces in a readable package form
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with practical metal highlights
Palette: gray, steel blue, muted teal, cyan markers, tiny orange labels
Composition: centered parts kit with organized internal structure and tidy silhouette
Output expectation: one crafting-bundle asset for UI cards, loot, and workshop visuals
Constraints: no text, no watermark, no trash pile look, no environment, no clutter
Negative prompt: photorealistic, junk heap, random toolbox photo, copied sci-fi repair kit, messy silhouette
```
- 后处理：必须看出“被整理过”，不能像散装废料。

---

## 11. 阶段 4：海域背景

### 11.1 阶段目标

- 锁定海域推进的视觉层次。
- 每个海域都必须一眼不同。
- 但不同海域仍然属于同一个游戏世界。

### 11.2 阶段操作顺序

1. 先做海面与转场。
2. 再做第一海域两张主背景。
3. 再做第二海域两张主背景。
4. 再做第三海域两张主背景。
5. 最后补深渊遗迹与通用前后景层。

### 11.3 本阶段总建议

- 宽背景优先 `16:9`。
- 同海域至少做两张，防止重复感太强。
- 给玩法区域留空，别把图画满。

### 11.4 阶段条目

#### 阶段4-01 海面基地远景
- 用途：基地场景主背景远景层。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_surface_base_far`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：海面应服务“回收站经营”，不是浪漫海景。
- 提示词：
```text
Use case: stylized-concept
Asset type: wide scene background for "Deep Tide Station"
Primary request: create the sea-surface recovery station far background layer
Scene/backdrop: ocean surface platform, distant support structures, crane silhouettes, docking lanes, muted waves, and a practical salvage-station skyline
Subject: functional industrial sea-surface base environment for a 2D game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: overcast marine daylight with subtle industrial glow accents
Palette: steel blue, sea gray, muted teal, pale cyan display lights, restrained orange safety marks
Composition: wide horizontal background with clear horizon line and space for UI overlay
Output expectation: one stable far-background layer supporting the base scene
Constraints: no text, no watermark, no luxury sci-fi city, no dramatic storm, no clutter
Negative prompt: photorealistic, tropical resort, cyberpunk skyline, romantic sunset postcard, copied platform designs
```
- 后处理：保证海平线清楚，但不过分吸睛。

#### 阶段4-02 出航转场海面图
- 用途：开始下潜前的转场或演示镜头。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_surface_departure`.
- 生图顺序：海面远景之后。
- 统一风格检查点：强调“出航开始”，而不是基地定居状态。
- 提示词：
```text
Use case: stylized-concept
Asset type: wide transition background for "Deep Tide Station"
Primary request: create a departure scene from the surface base into a dive mission
Scene/backdrop: docking edge, recovery sub preparing to descend, guidance lights, crane silhouettes, ocean surface, and a clear mission-start mood
Subject: practical deep-sea mission departure scene for a 2D salvage game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: marine daylight with slightly stronger guidance lights around the launch area
Palette: gray blue, sea teal, steel gray, cyan signal lights, small safety orange
Composition: wide side-view scene with a clear launch focal zone and clean peripheral space
Output expectation: one mission-start background supporting transitions and cut-ins
Constraints: no text, no watermark, no cinematic camera angle, no heroic poster vibe
Negative prompt: photorealistic, storm action movie, resort dock, cyberpunk city port, copied launch bay
```
- 后处理：与基地远景相比，这张要更有“准备出发”的节奏。

#### 阶段4-03 浅海断层区主背景 A
- 用途：第一海域常规探索背景。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_zone1_main_a`.
- 生图顺序：出航图之后。
- 统一风格检查点：相对友好、读路清楚、地形块明显。
- 提示词：
```text
Use case: stylized-concept
Asset type: gameplay background for zone one in "Deep Tide Station"
Primary request: create the first main background for the shallow fault area
Scene/backdrop: broken ledges, layered rock walls, mild glowing resources in the distance, open swim lanes, sparse salvage debris, and calm first-zone atmosphere
Subject: readable early-game underwater exploration environment
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: clearer underwater diffuse light with light haze and modest glow
Palette: slate blue, teal, cyan glow, blue-gray rock, soft green-blue highlights
Composition: wide side-view environment with obvious navigable routes and uncluttered center space
Output expectation: one reusable early-zone gameplay background
Constraints: no text, no watermark, no dense clutter, no horror darkness, no poster composition
Negative prompt: photorealistic, reef realism, abyss horror, oversaturated fantasy, copied underwater concept art
```
- 后处理：优先保留有明显平台感和路线感的版本。

#### 阶段4-04 浅海断层区主背景 B
- 用途：第一海域变化背景。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_zone1_main_b`.
- 生图顺序：主背景 A 之后。
- 统一风格检查点：保持第一海域属性，但换掉地形关系。
- 提示词：
```text
Use case: stylized-concept
Asset type: alternate gameplay background for zone one in "Deep Tide Station"
Primary request: create a second background for the shallow fault area with different rock rhythm and exploration pockets
Scene/backdrop: broad fault shelves, rounded rock breaks, small salvage fragments, gentle light shafts, and wider gathering spaces
Subject: an alternate early-game underwater environment from the same zone family
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: readable underwater diffuse light with slightly more spacious atmosphere
Palette: deep blue, slate teal, cyan glows, blue-gray stone, small cool white highlights
Composition: wide side-view environment with a different route flow than background A
Output expectation: one alternate background that reduces visual repetition in zone one
Constraints: no text, no watermark, no dark oppressive mood, no cluttered reef, no copied level art
Negative prompt: photorealistic, documentary reef, fantasy cave overload, visual noise, copied trench backgrounds
```
- 后处理：A 和 B 的主轮廓分布必须明显不同。

#### 阶段4-05 热泉区主背景 A
- 用途：第二海域探索背景。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_zone2_main_a`.
- 生图顺序：第一海域两张完成后。
- 统一风格检查点：热泉感必须明显，但整体依然偏冷。
- 提示词：
```text
Use case: stylized-concept
Asset type: gameplay background for zone two in "Deep Tide Station"
Primary request: create the first main background for the thermal vent zone
Scene/backdrop: blackened rock pillars, mineral crust, vent openings, vertical bubble plumes, rare ore spots, and tighter routes
Subject: readable mid-game thermal vent exploration environment
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: cold underwater light mixed with subtle warm vent glow and clear edge readability
Palette: basalt gray, navy, cyan, teal, controlled orange-red vent accents
Composition: wide side-view with denser hazards but usable routes clearly preserved
Output expectation: one core thermal-vent gameplay background for zone two
Constraints: no text, no watermark, no lava-fantasy palette, no smoke overload, no unreadable heat haze
Negative prompt: photorealistic, volcano cave, full red lighting, fantasy magma world, copied vent concept art
```
- 后处理：热泉亮点只能在局部，否则资源发光会失效。

#### 阶段4-06 热泉区主背景 B
- 用途：第二海域变化背景。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_zone2_main_b`.
- 生图顺序：主背景 A 之后。
- 统一风格检查点：同海域，但危险路径关系不同。
- 提示词：
```text
Use case: stylized-concept
Asset type: alternate gameplay background for zone two in "Deep Tide Station"
Primary request: create a second thermal vent background with new path shapes, vent placement, and mineral clusters
Scene/backdrop: fractured hot vents, vent-crust terraces, hazard chimneys, salvage remnants, and compressed exploration corridors
Subject: an alternate thermal-vent environment for the same mid-game zone
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: cold underwater base light with localized warm vent signatures and controlled contrast
Palette: charcoal blue, stone gray, cyan, teal, minimal orange-red vent glow
Composition: wide side-view background with a distinct path rhythm from thermal vent background A
Output expectation: one alternate thermal-vent gameplay background to prevent repetition
Constraints: no text, no watermark, no red-dominant image, no cinematic smoke chaos, no copied scene layouts
Negative prompt: photorealistic, volcanic poster, fantasy magma, clutter, muddy silhouettes, copied industrial cavern art
```
- 后处理：A 偏竖向，B 可偏横向，以拉开关卡观感。

#### 阶段4-07 冷流峡谷区主背景 A
- 用途：第三海域常规背景。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_zone3_main_a`.
- 生图顺序：热泉区完成后。
- 统一风格检查点：更压迫，但仍要能看通路。
- 提示词：
```text
Use case: stylized-concept
Asset type: gameplay background for zone three in "Deep Tide Station"
Primary request: create the first main background for the cold-current canyon zone
Scene/backdrop: narrow canyon walls, streaking current lanes, suspended debris, sparse mineral light, and long pressured swim corridors
Subject: readable late-mid-game canyon exploration environment
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: colder underwater light with denser haze and stronger rim contrast than earlier zones
Palette: deep navy, cold cyan, blue-gray rock, pale teal, faint white highlights
Composition: wide side-view environment with directional current flow and controlled tightness
Output expectation: one cold-current canyon background for advanced exploration
Constraints: no text, no watermark, no unreadable darkness, no fog wall, no horror framing
Negative prompt: photorealistic, black abyss, thriller cave, visual mud, copied trench game art
```
- 后处理：远景降低细节，别让窄路变得更难看清。

#### 阶段4-08 冷流峡谷区主背景 B
- 用途：第三海域变化背景。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_zone3_main_b`.
- 生图顺序：主背景 A 之后。
- 统一风格检查点：在同一海域逻辑下调整断面和视线引导。
- 提示词：
```text
Use case: stylized-concept
Asset type: alternate gameplay background for zone three in "Deep Tide Station"
Primary request: create a second cold-current canyon background with altered choke points and current-driven landmarking
Scene/backdrop: layered canyon cracks, broken structural frames, drifting panels, cold light minerals, and sharper route compression
Subject: alternate advanced canyon environment for the same gameplay zone
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: cold diffuse underwater light with selective edge readability and restrained glow
Palette: deep blue, slate gray, pale cyan, cold teal, small white accents
Composition: wide side-view background with a route rhythm clearly different from canyon background A
Output expectation: one alternate canyon background that preserves style while varying level feeling
Constraints: no text, no watermark, no total darkness, no cluttered debris field, no copied canyon art
Negative prompt: photorealistic, horror trench, pitch black cave, noisy contrast, fantasy ice canyon, copied concepts
```
- 后处理：A 与 B 一起看时，必须能记住差异。

#### 阶段4-09 深渊遗迹区主背景 A
- 用途：更深层终局海域背景。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_zone4_main_a`.
- 生图顺序：第三海域之后。
- 统一风格检查点：要高级、神秘，但仍然属于工业海底世界。
- 提示词：
```text
Use case: stylized-concept
Asset type: late-game gameplay background for "Deep Tide Station"
Primary request: create the first main background for the abyssal ruins zone
Scene/backdrop: ancient collapsed deep-sea facility remains, pressure gates, broken observation structures, rare luminous relic elements, and severe depth atmosphere
Subject: high-end late-game deep abyss salvage environment
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: very deep underwater light with concentrated visibility pockets, controlled glow, and readable silhouettes
Palette: navy-black blue, steel gray, cyan relic glow, muted teal, tiny orange emergency remnants
Composition: wide side-view environment with large ruins as landmarks and playable clear spaces
Output expectation: one memorable late-game abyssal ruins background
Constraints: no text, no watermark, no ancient fantasy temple look, no horror monster scene, no clutter overload
Negative prompt: photorealistic, alien temple, gothic horror ruins, muddy blackness, copied deep ruin concepts
```
- 后处理：不要让遗迹看成古代神殿，必须偏近未来工业遗迹。

#### 阶段4-10 深渊遗迹区主背景 B
- 用途：终局海域变化背景。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_zone4_main_b`.
- 生图顺序：主背景 A 之后。
- 统一风格检查点：同样是遗迹区，但路线组织和地标不同。
- 提示词：
```text
Use case: stylized-concept
Asset type: alternate late-game gameplay background for "Deep Tide Station"
Primary request: create a second abyssal ruins background with different ruin geometry, pressure structures, and navigation rhythm
Scene/backdrop: fallen structural ribs, sealed doors, broken tunnels, cold-glow relic machinery, and deep pressure atmosphere
Subject: alternate late-game salvage ruins environment in the same visual family
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: deep underwater darkness controlled by focused readable highlights and restrained relic glow
Palette: dark navy, blue-gray steel, cyan, pale teal, small dead-orange emergency accents
Composition: wide side-view environment clearly distinct from abyssal background A while retaining the same zone identity
Output expectation: one alternate late-game ruins background for variety
Constraints: no text, no watermark, no fantasy dungeon tone, no unreadable darkness, no copied ruin art
Negative prompt: photorealistic, horror ruin, magical altar, muddy black image, copied deep-space ruin concepts
```
- 后处理：确保两张遗迹图不是只换了镜头角度。

#### 阶段4-11 海底远景装饰层
- 用途：通用 parallax 远景层。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_parallax_far`.
- 生图顺序：四海域主背景完成后。
- 统一风格检查点：远景要弱，不抢玩法主体。
- 提示词：
```text
Use case: stylized-concept
Asset type: parallax far-layer background for "Deep Tide Station"
Primary request: create a reusable far parallax underwater layer for side-view levels
Scene/backdrop: distant rock silhouettes, faint debris forms, soft water haze, sparse tiny glow points, and broad depth shapes
Subject: reusable deep-sea distance layer supporting many gameplay scenes
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft distant underwater haze with very low contrast and controlled color depth
Palette: deep blue, muted teal, desaturated cyan, blue-gray silhouettes
Composition: wide low-detail background layer designed to sit behind gameplay space
Output expectation: one reusable parallax far layer that never steals focus
Constraints: no text, no watermark, no sharp detail, no hero focal point, no clutter
Negative prompt: photorealistic, poster composition, strong contrast foreground look, copied ocean matte painting
```
- 后处理：如果这层缩小后还太抢眼，说明细节过多。

#### 阶段4-12 海底近景遮罩层
- 用途：通用前景层、空间包围感增强。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整宽幅。
- 命名建议：`phase4_parallax_front`.
- 生图顺序：本阶段最后。
- 统一风格检查点：近景只做遮罩感，不能挡玩法信息。
- 提示词：
```text
Use case: stylized-concept
Asset type: parallax foreground layer for "Deep Tide Station"
Primary request: create a reusable front parallax underwater layer that adds depth without blocking gameplay
Scene/backdrop: soft foreground rock edges, sparse cables or frame silhouettes, drifting particles, and readable side masks with open center space
Subject: reusable front-layer framing for underwater side-view levels
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: slightly darker foreground shapes with soft edge highlights and controlled translucency
Palette: dark blue-gray, muted teal, pale cyan edge accents
Composition: wide foreground mask layout with large open safe play zone in the center
Output expectation: one reusable front-layer visual for depth enhancement
Constraints: no text, no watermark, no solid center obstruction, no detailed hero objects, no clutter
Negative prompt: photorealistic, busy foreground branches, hard blocking silhouette, copied underwater matte foregrounds
```
- 后处理：保留中间大开口版本，方便 HUD 和玩家活动。

---

## 12. 阶段 5：地形与场景道具

### 12.1 阶段目标

- 让地图具备可玩性和结构感。
- 道具与地形要能反复拼接使用。
- 单体轮廓要适配 2D 关卡布局。

### 12.2 阶段操作顺序

1. 先做基础岩壁和平台。
2. 再做资源附着面与危险喷口。
3. 再做废弃设施和容器类。
4. 最后做识别性道具。

### 12.3 本阶段总建议

- 多数资产采用纯 `#00ff00` 背景。
- 结构道具不要做得太厚重，否则地图会压黑。
- 能拼就尽量拼，避免每一关都要新画。

### 12.4 阶段条目

#### 阶段5-01 岩壁块
- 用途：基础地图边界与碰撞块视觉。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_rock_wall`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：岩壁块要清楚，不要真实山石杂乱感。
- 提示词：
```text
Use case: stylized-concept
Asset type: terrain cutout asset for "Deep Tide Station"
Primary request: create a reusable underwater rock wall chunk for side-view level construction
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a readable modular underwater rock wall piece with simple stratified forms and game-friendly silhouette
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with restrained stone-edge highlights
Palette: blue-gray rock, slate blue shadow, muted teal undertone, faint cyan edge accents
Composition: centered modular terrain chunk with clean attachment edges for level assembly
Output expectation: one reusable rock-wall asset suitable for tiling and collision readability
Constraints: no text, no watermark, no photoreal stone detail, no moss overload, no environment scene
Negative prompt: photorealistic, noisy cliff texture, fantasy cave crystal wall, clutter, copied platformer rock tile
```
- 后处理：边缘尽量明确，方便程序里配碰撞框。

#### 阶段5-02 断裂平台
- 用途：平台边缘、地形层次、资源停靠点。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_broken_platform`.
- 生图顺序：岩壁块之后。
- 统一风格检查点：要有“停靠感”和“路线感”。
- 提示词：
```text
Use case: stylized-concept
Asset type: terrain-platform cutout asset for "Deep Tide Station"
Primary request: create a broken underwater platform ledge for side-view pathing and landmark use
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a broken stone-and-metal ledge with flat standing surface logic and readable fractured edges
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with restrained edge clarity
Palette: blue-gray rock, steel gray fragments, muted teal undertones, small cyan residue accents
Composition: centered terrain element with a clear top plane and attachable sides
Output expectation: one route-defining platform asset for level assembly
Constraints: no text, no watermark, no photoreal rubble mess, no environment background, no clutter
Negative prompt: photorealistic, broken city street, fantasy floating island, noisy debris field, copied platform tile
```
- 后处理：顶部平面要明确，方便玩家感知“这是路”。

#### 阶段5-03 壳晶附着岩面
- 用途：壳晶矿资源挂载底座。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_crystal_mount`.
- 生图顺序：平台之后。
- 统一风格检查点：既像地形，也像资源可附着点。
- 提示词：
```text
Use case: stylized-concept
Asset type: terrain-support cutout asset for "Deep Tide Station"
Primary request: create a rock surface specially suited for attached shell-crystal resource placement
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: an angled rock face with shell-like mineral crust and clear attachment surfaces for crystal ore spawning
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with readable crust and plane separation
Palette: blue-gray stone, pale shell gray, faint teal mineral tint, subtle cyan reflections
Composition: centered support terrain shape with obvious mounting geometry
Output expectation: one specialized terrain piece for crystal-resource presentation
Constraints: no text, no watermark, no full resource embedded, no environment, no clutter
Negative prompt: photorealistic, cave wall scan, fantasy ore wall, noisy coral reef, copied mineral prop
```
- 后处理：不要直接把壳晶矿画死在上面，方便后续分离使用。

#### 阶段5-04 热泉喷口
- 用途：危险地形主体。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_thermal_vent`.
- 生图顺序：资源挂载面之后。
- 统一风格检查点：喷口要一眼可识别，危险语义明确。
- 提示词：
```text
Use case: stylized-concept
Asset type: hazard terrain cutout asset for "Deep Tide Station"
Primary request: create a thermal vent opening used as a damaging underwater hazard
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a basalt vent fissure with mineral buildup, a clear outlet mouth, and controlled warm hazard cues
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: cold base light with very localized warm vent accents
Palette: dark basalt gray, navy, muted teal, tiny orange-red vent glow
Composition: centered hazard element with obvious dangerous opening and clean outer shape
Output expectation: one recognizable hazard terrain asset for thermal zones
Constraints: no text, no watermark, no full flame plume, no lava fantasy, no environment
Negative prompt: photorealistic, volcano crater, fire pit, fantasy magma vent, clutter, copied vent props
```
- 后处理：喷口本体和喷出的特效要分开。

#### 阶段5-05 冷流喷口
- 用途：推拉移动的环境危险。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_cold_current_vent`.
- 生图顺序：热泉喷口之后。
- 统一风格检查点：必须看出定向水流的源头。
- 提示词：
```text
Use case: stylized-concept
Asset type: hazard terrain cutout asset for "Deep Tide Station"
Primary request: create a cold-current outlet used to alter player movement
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a rock crack or industrial nozzle opening shaped to emit a strong directional cold-water current
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: cold diffuse light with subtle current-source highlight accents
Palette: blue-gray, cold cyan, pale teal, muted steel accents
Composition: centered hazard element with clear directional form and readable outlet structure
Output expectation: one current-source terrain asset for movement-control challenges
Constraints: no text, no watermark, no magic portal look, no environment, no clutter
Negative prompt: photorealistic, icy spell vortex, fantasy wind source, copied nozzle props, muddy shape
```
- 后处理：水流拖尾特效要放到特效阶段，不在这里画满。

#### 阶段5-06 深裂缝
- 用途：掉落危险、视觉压迫、路线限制。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_deep_crack`.
- 生图顺序：冷流喷口之后。
- 统一风格检查点：裂缝要深，但轮廓边界必须清楚。
- 提示词：
```text
Use case: stylized-concept
Asset type: hazard terrain cutout asset for "Deep Tide Station"
Primary request: create a deep underwater fissure used as a dangerous route separator or drop hazard
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a sharply readable rock fissure with depth darkness, broken edges, and subtle internal glow hints
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: dim cold light with careful edge readability and minimal interior glow
Palette: dark navy, blue-gray rock, muted teal, faint cyan edge accents
Composition: centered hazard opening with strong readable borders and depth implication
Output expectation: one fissure hazard asset for route shaping and danger cues
Constraints: no text, no watermark, no horror void monster look, no environment, no clutter
Negative prompt: photorealistic, horror chasm, lava crack, fantasy abyss portal, muddy black blob
```
- 后处理：裂缝中间可以暗，但边缘绝不能丢。

#### 阶段5-07 废弃金属梁
- 用途：工业遗迹感、地图装饰、可组合障碍。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_metal_beam`.
- 生图顺序：裂缝之后。
- 统一风格检查点：像海底设施残骸，不像普通工地钢梁。
- 提示词：
```text
Use case: stylized-concept
Asset type: structural prop cutout asset for "Deep Tide Station"
Primary request: create an abandoned structural beam from deep-sea infrastructure
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a readable industrial beam or frame section with marine wear, pressure-rated construction, and salvage-station world consistency
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with restrained metallic highlights
Palette: steel gray, dark blue metal, muted teal residue, tiny orange safety paint remnants
Composition: centered structural fragment with clean geometric silhouette for layering in scenes
Output expectation: one reusable industrial debris prop for many sea zones
Constraints: no text, no watermark, no construction-site realism, no environment, no clutter
Negative prompt: photorealistic, rusty junk photo, city construction beam, copied sci-fi corridor part, muddy silhouette
```
- 后处理：尽量做可横可竖都能用的结构。

#### 阶段5-08 回收容器箱
- 用途：可交互容器、地面目标物、基地物件。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_salvage_container`.
- 生图顺序：金属梁之后。
- 统一风格检查点：像深海回收容器，不是普通运输纸箱。
- 提示词：
```text
Use case: stylized-concept
Asset type: interactive prop cutout asset for "Deep Tide Station"
Primary request: create a salvage container crate used as a readable interactive object
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a reinforced underwater recovery container with latch system, pressure locks, and clear loot-container identity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft industrial light with controlled metal and edge readability
Palette: blue-gray, steel gray, cyan lock light, muted teal, orange warning paint
Composition: centered prop with obvious lid-body separation and clear interaction silhouette
Output expectation: one reusable interactive container for world use
Constraints: no text, no watermark, no wooden crate, no environment, no clutter
Negative prompt: photorealistic, cargo shipping crate photo, fantasy treasure chest, copied sci-fi loot box
```
- 后处理：看缩略图时也要能识别“可打开”。

#### 阶段5-09 浮标灯塔
- 用途：地图导航物、返航点、提示地标。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_signal_buoy`.
- 生图顺序：容器箱之后。
- 统一风格检查点：必须像导航设施，不能像装饰雕塑。
- 提示词：
```text
Use case: stylized-concept
Asset type: navigation prop cutout asset for "Deep Tide Station"
Primary request: create a beacon buoy or signal tower used as a navigation landmark
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: an industrial underwater signal buoy with readable light head, support frame, and route-guidance identity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with a focused readable beacon glow
Palette: steel blue, gray, teal, cyan signal light, orange hazard accents
Composition: centered landmark prop with a clear vertical silhouette and visible signal core
Output expectation: one navigation landmark asset for route guidance and return cues
Constraints: no text, no watermark, no fantasy lighthouse look, no environment, no clutter
Negative prompt: photorealistic, coast lighthouse, sculpture, copied sci-fi beacon, muddy details
```
- 后处理：灯塔型道具要尽量细长但别脆弱。

#### 阶段5-10 海底管道残骸
- 用途：工业氛围、路径遮挡、拼接道具。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_pipe_wreck`.
- 生图顺序：浮标灯塔之后。
- 统一风格检查点：圆管结构清楚，可横向拼接。
- 提示词：
```text
Use case: stylized-concept
Asset type: structural debris cutout asset for "Deep Tide Station"
Primary request: create a broken underwater pipeline section from abandoned infrastructure
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a readable pressure-rated pipe segment with fractured ends, service brackets, and marine wear
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft industrial light with restrained cylindrical highlights
Palette: blue-gray metal, dark steel, muted teal, faint cyan utility accents
Composition: centered structural debris prop with clean pipe identity and game-friendly silhouette
Output expectation: one reusable pipeline-wreck prop for multiple sea zones
Constraints: no text, no watermark, no full environment, no junk heap look, no clutter
Negative prompt: photorealistic, oil-rig realism, city sewer pipe, copied sci-fi corridor tube, muddy silhouette
```
- 后处理：破口形状可以有一两种变化，方便后续拓展。

#### 阶段5-11 黑暗区边缘标识
- 用途：视觉引导、风险提示、地图教学。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_darkzone_marker`.
- 生图顺序：管道之后。
- 统一风格检查点：像边界标识，不像广告牌。
- 提示词：
```text
Use case: stylized-concept
Asset type: guidance prop cutout asset for "Deep Tide Station"
Primary request: create a marker object used to signal the edge of dark or dangerous zones
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a rugged boundary marker with industrial warning-light logic and readable edge-zone identity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: subdued base light with a focused warning-light element
Palette: dark gray, steel blue, cyan, small orange warning accents, muted teal
Composition: centered marker prop with obvious top-light and base structure
Output expectation: one edge-marker prop useful for teaching dangerous area transitions
Constraints: no text, no watermark, no billboard look, no environment, no clutter
Negative prompt: photorealistic, road sign, neon ad board, fantasy totem, copied warning beacon
```
- 后处理：标识本身要简洁，警示语义主要靠灯色。

#### 阶段5-12 可交互遗迹容器
- 用途：特殊掉落、钥匙或工具解锁目标。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase5_relic_container`.
- 生图顺序：本阶段最后。
- 统一风格检查点：必须明显比普通容器更高级、更神秘。
- 提示词：
```text
Use case: stylized-concept
Asset type: special interactive prop cutout asset for "Deep Tide Station"
Primary request: create a rare relic-container object that requires special interaction or tools to open
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a sealed advanced storage pod from old deep-sea infrastructure, with higher-tier locks and premium visual identity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft neutral light with focused premium lock and seam highlights
Palette: dark steel blue, gray, cyan lock glow, muted teal, tiny warm accent lights
Composition: centered special container with a clear rare-object silhouette distinct from normal crates
Output expectation: one higher-value interactive pod for secrets and advanced rewards
Constraints: no text, no watermark, no fantasy treasure chest look, no environment, no clutter
Negative prompt: photorealistic, pirate chest, generic sci-fi loot box, copied relic container, muddy silhouette
```
- 后处理：要和普通容器箱拉开档次，但依然属于同一世界。

---

## 13. 阶段 6：危险生物与风险体

### 13.1 阶段目标

- 锁定主要敌对与风险对象。
- 危险体必须可读、可规避、可记忆。
- 每个生物要有状态变化，但仍保持家族统一。

### 13.2 阶段操作顺序

1. 先做电弧鳐三状态。
2. 再做裂壳螺三状态。
3. 再做脉冲水母群三状态。
4. 最后补额外风险体。

### 13.3 本阶段总建议

- 单体生物统一纯 `#00ff00` 背景。
- 同一生物的不同状态尽量连续生成。
- 危险语义优先于可爱程度。

### 13.4 阶段条目

#### 阶段6-01 电弧鳐巡游态
- 用途：基础巡逻敌人状态。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_arc_ray_patrol`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：像深海异常鳐类，不像普通海洋馆鳐鱼。
- 提示词：
```text
Use case: stylized-concept
Asset type: enemy cutout asset for "Deep Tide Station"
Primary request: create the patrol state of Arc Ray, an electric deep-sea hostile creature
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a flattened ray-shaped hostile creature with built-in electric organs, smooth menace, and readable side-view profile
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: dim underwater diffuse light with subtle bioelectric edge glow
Palette: navy, dark teal, cyan electric accents, pale cold-white edge sparks
Composition: centered single enemy with a broad readable silhouette and patrol-state calm tension
Output expectation: one stable patrol-state enemy asset for regular gameplay
Constraints: no text, no watermark, no gore, no horror face, no environment
Negative prompt: photorealistic, aquarium ray, alien horror monster, copied sci-fi fish, muddy silhouette, blood
```
- 后处理：巡游态不要放电太多，保留蓄力空间。

#### 阶段6-02 电弧鳐蓄电态
- 用途：攻击前摇状态。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_arc_ray_charge`.
- 生图顺序：巡游态之后。
- 统一风格检查点：主体结构一致，只增强危险张力。
- 提示词：
```text
Use case: stylized-concept
Asset type: enemy-state cutout asset for "Deep Tide Station"
Primary request: create the charge-up state of Arc Ray with visible electrical buildup
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: the same Arc Ray creature with electric organs brightening and a more tense body posture before discharge
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: dim base light with stronger localized electric build-up highlights
Palette: dark navy, teal body, bright cyan charge lines, cold white spark accents
Composition: centered enemy state with preserved silhouette family and clearer attack intent
Output expectation: one charge-state variant that signals danger before attack
Constraints: no text, no watermark, no redesign, no huge energy explosion, no environment
Negative prompt: photorealistic, superhero lightning creature, copied electric fish, over-bloom, muddy pose
```
- 后处理：蓄电态和放电态必须明显分开。

#### 阶段6-03 电弧鳐放电态
- 用途：攻击判定状态。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_arc_ray_attack`.
- 生图顺序：蓄电态之后。
- 统一风格检查点：放电效果集中，不用把特效画满整张。
- 提示词：
```text
Use case: stylized-concept
Asset type: enemy-state cutout asset for "Deep Tide Station"
Primary request: create the discharge attack state of Arc Ray with controlled electric release
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: the same Arc Ray creature releasing visible electric arcs from edge organs, with a readable attack-state posture
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: strong localized electric highlights over a dark restrained base
Palette: dark teal body, bright cyan electric arcs, cold white spark tips, minimal warm accents
Composition: centered attack-state enemy with the body still clearly visible despite the electrical effect
Output expectation: one attack-state variant for clear threat feedback
Constraints: no text, no watermark, no giant explosion cloud, no environment, no silhouette loss
Negative prompt: photorealistic, comic-book lightning blast, copied electric boss monster, over-bloom, clutter
```
- 后处理：如果只剩电没有鳐，说明过了。

#### 阶段6-04 裂壳螺闭壳态
- 用途：潜伏敌人静止状态。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_crack_snail_closed`.
- 生图顺序：电弧鳐系列之后。
- 统一风格检查点：要像会爆发的硬壳危险体。
- 提示词：
```text
Use case: stylized-concept
Asset type: enemy cutout asset for "Deep Tide Station"
Primary request: create the closed-shell idle state of Crack Shell Snail, an ambush-type hostile creature
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a dense heavy spiral shell creature with visible fracture lines, compact dangerous mass, and ambush readiness
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: dim underwater diffuse light with restrained shell-edge highlights
Palette: shell gray, blue-gray, dark teal shadow, faint cyan seam glow
Composition: centered enemy with a dense low-profile silhouette that implies hidden danger
Output expectation: one closed-shell ambush-state enemy asset
Constraints: no text, no watermark, no cute snail face, no environment, no clutter
Negative prompt: photorealistic, garden snail, cartoon mascot, horror parasite shell, copied shell monster design
```
- 后处理：闭壳态必须和地图岩块能区分，但不能太显眼。

#### 阶段6-05 裂壳螺攻击态
- 用途：突刺或张壳攻击状态。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_crack_snail_attack`.
- 生图顺序：闭壳态之后。
- 统一风格检查点：张开后危险明显，但仍属于同一壳体。
- 提示词：
```text
Use case: stylized-concept
Asset type: enemy-state cutout asset for "Deep Tide Station"
Primary request: create the attack-open state of Crack Shell Snail with dangerous interior structures revealed
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: the same heavy shell creature opening part of its cracked shell to reveal attack anatomy or striking mechanism
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: dim base light with focused highlights on the opened shell and striking structure
Palette: gray shell, dark teal body, cyan seam accents, pale white sharp highlights
Composition: centered attack-state silhouette with clear relation to the closed-shell version
Output expectation: one attack-state ambush enemy variant with obvious threat escalation
Constraints: no text, no watermark, no gore, no giant mouth horror, no environment
Negative prompt: photorealistic, body horror mollusk, copied monster shell, blood, clutter, unreadable anatomy
```
- 后处理：攻击态应一眼看出“现在危险”。

#### 阶段6-06 裂壳螺破碎态
- 用途：被击退、失活或可采集残壳状态。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_crack_snail_broken`.
- 生图顺序：攻击态之后。
- 统一风格检查点：仍保留主体可识别性，不是满地碎块。
- 提示词：
```text
Use case: stylized-concept
Asset type: enemy-state cutout asset for "Deep Tide Station"
Primary request: create the broken or disabled state of Crack Shell Snail for defeat feedback
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: the same shell creature with shell damage, collapsed posture, and reduced threat without turning into random debris
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft dim light with restrained fracture highlights
Palette: shell gray, blue-gray, muted teal, faint cyan residue
Composition: centered disabled-state enemy with enough continuity from the active states
Output expectation: one broken-state variant for defeat or hazard-resolution feedback
Constraints: no text, no watermark, no gore, no debris explosion, no environment
Negative prompt: photorealistic, smashed corpse, blood, copied monster carcass, muddy rubble
```
- 后处理：破碎态不要太花，避免玩家误认成资源。

#### 阶段6-07 脉冲水母群静态
- 用途：群体危险的默认状态。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_pulse_jelly_idle`.
- 生图顺序：裂壳螺系列之后。
- 统一风格检查点：强调“群体”，不是单只大型水母。
- 提示词：
```text
Use case: stylized-concept
Asset type: enemy-group cutout asset for "Deep Tide Station"
Primary request: create the idle drifting state of Pulse Jelly Group, a clustered hostile organism
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a small cluster of translucent pulse jelly organisms moving together as one readable hostile group
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater light with faint internal pulse glow
Palette: pale cyan, translucent blue, muted purple-blue accents, cold white tips
Composition: centered grouped silhouette with several small bodies forming one recognizable enemy unit
Output expectation: one idle-state grouped enemy asset for swarm-like hazards
Constraints: no text, no watermark, no giant singular jellyfish, no horror tendril overload, no environment
Negative prompt: photorealistic, aquarium jellyfish photo, alien horror tentacles, copied jelly monster designs, clutter
```
- 后处理：缩小后必须仍然看出“群体结构”。

#### 阶段6-08 脉冲水母群脉冲态
- 用途：危险即将触发的预警状态。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_pulse_jelly_pulse`.
- 生图顺序：静态之后。
- 统一风格检查点：亮度增强，但不能盖过主体轮廓。
- 提示词：
```text
Use case: stylized-concept
Asset type: enemy-group state cutout asset for "Deep Tide Station"
Primary request: create the pulsing-alert state of Pulse Jelly Group with synchronized light buildup
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: the same jelly cluster with stronger internal pulse light, synchronized rhythm, and clearer threat-readiness
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft base light with stronger internal pulsing glow and edge readability
Palette: cyan, pale blue, faint violet-blue, cold white pulse highlights
Composition: centered grouped enemy maintaining the same cluster family silhouette
Output expectation: one warning-state grouped enemy variant
Constraints: no text, no watermark, no full-screen bloom, no environment, no silhouette loss
Negative prompt: photorealistic, neon wallpaper, copied bioluminescent jelly art, muddy transparency, clutter
```
- 后处理：脉冲态要能做“攻击前摇”的视觉提示。

#### 阶段6-09 脉冲水母群追随态
- 用途：主动接近玩家时的状态。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_pulse_jelly_chase`.
- 生图顺序：脉冲态之后。
- 统一风格检查点：姿态更集中、更前压。
- 提示词：
```text
Use case: stylized-concept
Asset type: enemy-group state cutout asset for "Deep Tide Station"
Primary request: create the follow or chase state of Pulse Jelly Group with tighter forward movement energy
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: the same jelly cluster compressing forward as a coordinated hostile group, implying pursuit
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater base light with controlled bioluminescent edges
Palette: pale cyan, blue, muted violet-blue, white tips
Composition: centered grouped enemy with a more directional and compressed silhouette than the idle version
Output expectation: one chase-state swarm enemy asset for more active threat moments
Constraints: no text, no watermark, no giant blur trails, no environment, no monster-horror exaggeration
Negative prompt: photorealistic, alien swarm horror, copied jelly swarm design, over-bloom, clutter
```
- 后处理：不要靠拖影表达追击，靠群体姿态表达。

#### 阶段6-10 危险浮游刺群
- 用途：附加小型风险体。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_spike_plankton`.
- 生图顺序：三大主敌之后。
- 统一风格检查点：看起来是危险浮游体，不是灰尘。
- 提示词：
```text
Use case: stylized-concept
Asset type: minor hazard group cutout asset for "Deep Tide Station"
Primary request: create a drifting spike-plankton hazard cluster used as a minor environmental threat
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a compact cluster of tiny sharp drifting organisms with faint glow and a readable collective hazard silhouette
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft diffuse light with tiny hostile-glow accents
Palette: pale teal, cyan, muted blue, faint white points
Composition: centered clustered minor hazard with enough density to read clearly
Output expectation: one small-scale hazard asset for environmental variety
Constraints: no text, no watermark, no dust cloud look, no full-screen particle swarm, no environment
Negative prompt: photorealistic, pollen cloud, glitter dust, horror parasite cloud, copied swarm designs
```
- 后处理：它应该是“可见的危险团”，不是背景粒子。

#### 阶段6-11 异常机械寄生体
- 用途：工业遗迹区附加敌对单位。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_mech_parasite`.
- 生图顺序：浮游刺群之后。
- 统一风格检查点：是生物与旧设施的混合异常，不是机器人。
- 提示词：
```text
Use case: stylized-concept
Asset type: hybrid hazard cutout asset for "Deep Tide Station"
Primary request: create an abnormal mech-parasite life form that inhabits old deep-sea infrastructure
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a small hostile organism partially fused with old mechanical housing, original, readable, and suited to ruined facilities
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: dim cold light with tiny interface-like glow points and organic edge highlights
Palette: dark blue metal, gray shell, cyan lights, muted teal tissue-like accents
Composition: centered hybrid hazard with a distinct silhouette not overlapping the main enemy trio
Output expectation: one extra-risk enemy for deeper facility zones
Constraints: no text, no watermark, no body horror, no humanoid robot, no environment
Negative prompt: photorealistic, cybernetic gore, full robot drone, copied parasite machine design, clutter
```
- 后处理：混合感要 subtle，不要恶心化。

#### 阶段6-12 深渊观测眼
- 用途：终局风险体或特殊地形生物。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase6_abyss_observer`.
- 生图顺序：本阶段最后。
- 统一风格检查点：要神秘、有压迫，但不做克苏鲁 horror。
- 提示词：
```text
Use case: stylized-concept
Asset type: special hazard cutout asset for "Deep Tide Station"
Primary request: create an abyss observer hazard, a rare deep-zone organism or mechanism that watches and threatens intruders
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a mysterious singular deep-zone watcher with a focused luminous core and compact ominous silhouette, blending organic and industrial cues
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: deep cold base light with a central threatening glow and controlled edge readability
Palette: dark navy, cyan core light, muted teal, pale white highlights, almost no warm tones
Composition: centered special hazard with strong iconic silhouette and late-game tension
Output expectation: one memorable final-zone risk entity for advanced encounters
Constraints: no text, no watermark, no eldritch horror overload, no gore, no environment
Negative prompt: photorealistic, giant eyeball horror, tentacle nightmare, copied abyss monster design, visual mud
```
- 后处理：如果太恐怖，会破坏整个项目的课程展示气质。

---

## 目录

1. 文档使用方式
2. 全项目统一风格规范
3. 全项目统一负面词规范
4. 全项目统一输出规范
5. 全项目统一生图顺序
6. 阶段总览
7. 阶段 0：风格锁定图
8. 阶段 1：主角与潜水器
9. 阶段 2：资源体系
10. 阶段 3：升级模块与工具
11. 阶段 4：海域背景
12. 阶段 5：地形与场景道具
13. 阶段 6：危险生物与风险体
14. 阶段 7：基地与功能界面场景
15. 阶段 8：HUD 与 UI 控件
16. 阶段 9：特效与动画参考
17. 阶段 10：图鉴与宣传图
18. 最终统一质检标准
19. 常见返工原因
20. 资产命名建议

---

## 1. 文档使用方式

### 1.1 你必须按阶段做

- 不要先做 UI，再回头补场景。
- 不要先做宣传图，再回头补资源。
- 不要一开始就把所有资源做满级精修。
- 先锁风格，再锁主角，再锁资源，再锁场景，再锁 UI，再锁特效。

### 1.2 每一张图都要经过同一套判断

每一张图生成后都要检查：

1. 轮廓是否清楚。
2. 颜色是否仍然在统一色系里。
3. 发光是否克制。
4. 是否像同一个游戏里的素材。
5. 是否适合 2D 侧视玩法。
6. 是否能直接切出来使用。
7. 是否会和 HUD、资源、地形打架。

### 1.3 生图模型使用建议

- 如果你要快速定风格，先低成本出草图。
- 如果你要正式资产，再出精修版。
- 如果你要透明背景资产，优先生成纯色抠图底。
- 如果你要背景图，不要透明底，直接生成完整构图。

### 1.4 你生成时要固定不变的内容

以下内容必须在所有提示词里保持稳定：

- 世界观：深海回收站
- 类型：2D 横版侧视深海采集经营游戏
- 美术方向：原创，不靠近现成 IP
- 光照：柔和水下漫射光
- 主色：深蓝、冷青、青绿
- 点缀：荧光青、少量安全橙
- 质感：半风格化，干净，可读性高
- 结构：适合做游戏资产，不是海报拼贴

---

## 2. 全项目统一风格规范

### 2.1 风格一句话定义

`原创深海回收站题材的 2D 横版侧视游戏美术，半风格化工业科幻，清晰轮廓，冷青蓝主色，荧光青绿发光点缀，少量安全橙提示色，纹理克制，可读性优先。`

### 2.2 视觉关键词

- 深海
- 回收
- 废弃设施
- 工业科幻
- 断层岩壁
- 热泉矿化
- 冷流峡谷
- 荧光资源
- 小型潜水器
- 水下风险
- 可读性优先
- 原创游戏资产

### 2.3 颜色规则

- 大面积主色：深海蓝、灰蓝、炭灰蓝
- 中间层颜色：冷青、墨青、青灰
- 发光层颜色：荧光青、青绿、冷白蓝
- 危险提示色：少量橙红
- 稀有提示色：青绿、暖金、亮红只能小面积使用

### 2.4 形体规则

- 外轮廓必须大、稳、清楚。
- 不追求碎细节。
- 优先大块面 + 明确的功能结构。
- 角色、资源、敌人都要一眼能区分。
- 侧视 2D 可读性大于三维炫技。

### 2.5 光照规则

- 所有资产都默认在水下环境。
- 光来自柔和的漫射环境光。
- 高亮边缘只用于帮助读形。
- 发光结构集中在资源、仪器、警示灯、危险体上。
- 不要大面积镜面反射。

### 2.6 纹理规则

- 纹理要有，但不能脏。
- 不要照片贴图感。
- 不要高噪点。
- 岩石要简洁。
- 金属要有轻度磨损，但不要写实锈蚀海报感。

### 2.7 UI 规则

- UI 不是现代手机 APP 风。
- UI 要像深海回收站设备面板。
- 线条简洁。
- 信息模块清楚。
- 图标统一圆角、科技框、少量发光边缘。

### 2.8 透明背景资产统一规则

所有需要后续抠图的单体资产，提示词里统一加入：

- 使用纯 `#00ff00` 单色背景用于后期抠图。
- 背景不能有阴影。
- 背景不能有渐变。
- 主体不能出现大面积 `#00ff00`。
- 主体要居中并留安全边距。

### 2.9 背景图统一规则

所有海域背景图都必须：

- 预留角色活动区域。
- 不能满屏都是细节。
- 前中后景分层明显。
- 视线中心让给玩法区域。
- 颜色对比不要压过资源与玩家。

### 2.10 敌人与危险体统一规则

- 不做恐怖写实怪。
- 不做血腥。
- 不做高密度触手堆叠。
- 要有危险感，但仍属于可爱的工业科幻深海世界。
- 轮廓必须能在水下背景里读清。

---

## 3. 全项目统一负面词规范

所有提示词都默认追加以下负面方向：

- 不要文字
- 不要水印
- 不要 logo
- 不要现成游戏既视感
- 不要像任何知名 IP 主角
- 不要写实照片感
- 不要像电影海报
- 不要像像素风
- 不要日漫大眼人物
- 不要泥状模糊轮廓
- 不要过度复杂背景
- 不要难以切图的散乱元素
- 不要 UI 文字直接印在素材上
- 不要强透视导致 2D 难用

---

## 4. 全项目统一输出规范

### 4.1 单体资产

- 推荐画幅：`1:1`
- 背景：纯 `#00ff00`
- 主体：居中
- 边缘：留安全边距
- 用途：后续抠图、裁切、导出 PNG

### 4.2 宽幅背景

- 推荐画幅：`16:9`
- 背景：完整场景
- 主体：不要只有中心构图
- 用途：基地界面、海域场景、结算界面、升级界面

### 4.3 UI 套件

- 推荐画幅：`1:1` 或 `4:3`
- 透明背景优先
- 组件之间要有统一边框与颜色逻辑

### 4.4 图鉴与宣传图

- 图鉴卡推荐：`3:4`
- 横版封面推荐：`16:9`
- 竖版封面推荐：`4:5`

---

## 5. 全项目统一生图顺序

### 5.1 第一轮

- 风格母图
- 色板图
- UI 母图
- 海域母图

### 5.2 第二轮

- 主角潜水器
- 核心资源四种
- 第一海域背景

### 5.3 第三轮

- 敌人
- 危险地形
- 基地与结算

### 5.4 第四轮

- HUD
- 按钮
- 交互提示
- 升级模块

### 5.5 第五轮

- 特效
- 动画参考
- 图鉴卡
- 宣传图

---

## 6. 阶段总览

| 阶段 | 名称 | 目标 | 推荐先做 | 预计条目数 |
|---|---|---|---|---|
| 0 | 风格锁定图 | 统一风格 | 风格母图、色板、UI 母图 | 12 |
| 1 | 主角与潜水器 | 锁主角视觉 | 待机、推进、受击 | 12 |
| 2 | 资源体系 | 锁核心采集物 | 四大资源三档稀有度 | 12 |
| 3 | 升级模块与工具 | 锁成长反馈视觉 | 气瓶、推进器、货舱、机械臂 | 12 |
| 4 | 海域背景 | 锁地图视觉层次 | 断层区、热泉区、冷流峡谷区 | 12 |
| 5 | 地形与场景道具 | 锁地图可玩元素 | 岩壁、平台、喷口、容器 | 12 |
| 6 | 危险生物与风险体 | 锁敌对逻辑视觉 | 电弧鳐、裂壳螺、水母群 | 12 |
| 7 | 基地与功能界面场景 | 锁菜单与功能页 | 基地、结算、升级、图鉴室 | 12 |
| 8 | HUD 与 UI 控件 | 锁交互层 | 氧气条、按钮、图标、卡片 | 12 |
| 9 | 特效与动画参考 | 锁反馈层 | 采集、警报、推进、放电 | 12 |
| 10 | 图鉴与宣传图 | 锁展示层 | 图鉴卡、封面、海报 | 12 |

---

## 7. 阶段 0：风格锁定图

### 7.1 阶段目标

- 先统一风格，不先抠具体资产。
- 先确认世界观气质，再做功能素材。
- 这一阶段做错，后面所有资产都会返工。

### 7.2 阶段操作顺序

1. 先出风格母图 A。
2. 再出风格母图 B。
3. 在两者之间选方向。
4. 再补色板与材质图。
5. 再做 UI 母图。
6. 最后做海域气质图。

### 7.3 本阶段总建议

- 每个条目先出 `4` 张初稿。
- 从中选 `1` 张保留。
- 保留图再做 `1` 张精修。
- 本阶段不追求抠图透明背景。

### 7.4 阶段条目

#### 阶段0-01 风格母图 A
- 用途：锁定整体世界观、材质、色彩和主视觉语气。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整场景。
- 命名建议：`phase0_style_master_a`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：必须同时出现深海、回收站、潜水器、废弃设施、荧光资源。
- 提示词：
```text
Use case: stylized-concept
Asset type: key art style master for the game "Deep Tide Station"
Primary request: create a master style frame that defines the whole game visual direction
Scene/backdrop: a wide underwater deep-sea salvage scene with a small recovery submersible, broken marine facility parts, glowing resources, layered rock walls, and readable play space
Subject: original 2D side-view deep-sea salvage world mood shot
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with readable rim highlights and controlled glow
Palette: navy, slate blue, teal, cyan glow, rust gray, small orange accents
Composition: wide composition, clear foreground midground background separation, gameplay readability preserved
Output expectation: one polished master mood frame that can guide every later asset
Constraints: no text, no watermark, no logo, no copied franchise design, no photorealism
Negative prompt: photorealistic, pixel art, anime face, muddy silhouette, noisy texture, over-detailed clutter, copied game art
```
- 后处理：从 4 张里只保留最像“同一游戏世界”的 1 张，不选最华丽的，选最可落地的。

#### 阶段0-02 风格母图 B
- 用途：作为风格母图 A 的对照方案，避免一开始锁错方向。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：16:9。
- 背景：完整场景。
- 命名建议：`phase0_style_master_b`.
- 生图顺序：本阶段第 2 张。
- 统一风格检查点：同样必须原创，但相比 A 更偏工业设施与冷静 UI 感。
- 提示词：
```text
Use case: stylized-concept
Asset type: alternate key art style master for the game "Deep Tide Station"
Primary request: create a second master style frame with stronger industrial salvage atmosphere but the same gameplay-friendly readability
Scene/backdrop: deep underwater salvage corridor with damaged sea structures, a compact player submersible, sparse glowing resources, pressure lights, and layered blue water haze
Subject: original 2D side-view industrial deep-sea exploration mood shot
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with colder highlights and limited glow
Palette: deep navy, steel blue, cyan, muted teal, desaturated gray, small safety orange
Composition: wide side-view composition with a clear playable corridor and uncluttered focal area
Output expectation: one polished alternate mood frame for comparing visual direction
Constraints: no text, no watermark, no logo, no horror realism, no copied franchise design
Negative prompt: photorealistic, pixel art, anime, muddy contrast, visual noise, dense clutter, existing IP shapes
```
- 后处理：A 与 B 二选一为主方向，另一张只保留作备用参考。

#### 阶段0-03 统一色板图
- 用途：锁定整个项目的综合色域。
- 建议生成数量：初稿 3 张，保留 1 张。
- 建议画幅：4:3。
- 背景：简洁展示板。
- 命名建议：`phase0_color_script`.
- 生图顺序：在母图二选一之后。
- 统一风格检查点：必须包含主色、发光色、危险提示色、UI 色、背景色。
- 提示词：
```text
Use case: productivity-visual
Asset type: color script and palette board for the game "Deep Tide Station"
Primary request: create a clean palette board that defines environment colors, glow colors, hazard colors, UI colors, and material accent colors
Scene/backdrop: minimal design presentation board with labeled color blocks visually implied but without actual text
Subject: deep-sea salvage palette system in a cohesive game-ready style
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: neutral presentation lighting
Palette: navy, slate blue, blue gray, teal, fluorescent cyan, cold white, safety orange, warning red used sparingly
Composition: clean board layout, grouped by environment, resource, hazard, UI, and highlight colors
Output expectation: a single palette board that locks color discipline for the full game
Constraints: no text, no watermark, no brand marks, no random rainbow palette
Negative prompt: photorealistic, noisy gradients, unrelated warm palette dominance, oversaturated fantasy rainbow, clutter
```
- 后处理：提取 8 到 12 个核心色，后续所有提示词都只允许在这个范围里波动。

#### 阶段0-04 材质语言图
- 用途：锁定岩石、金属、凝胶、晶体、发光结构的材质处理方式。
- 建议生成数量：初稿 3 张，保留 1 张。
- 建议画幅：4:3。
- 背景：展示板。
- 命名建议：`phase0_material_board`.
- 生图顺序：色板图之后。
- 统一风格检查点：材质要简洁、统一、不要写实照片贴图感。
- 提示词：
```text
Use case: productivity-visual
Asset type: material language board for the game "Deep Tide Station"
Primary request: create a material board showing unified treatment for rock, worn metal, glowing gel, crystal, painted hull surfaces, and warning lights
Scene/backdrop: clean presentation board with isolated material swatches and sample object fragments, no text
Subject: cohesive semi-stylized underwater industrial material language
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: neutral studio-like board lighting while preserving underwater-inspired color logic
Palette: navy, steel blue, gray, teal, cyan glow, subtle rust gray, tiny orange accents
Composition: clean arrangement of material examples with ample spacing and easy visual comparison
Output expectation: one clear material guide board usable as a production reference
Constraints: no text, no watermark, no photoreal material scans, no chaotic samples
Negative prompt: photorealistic, PBR showroom, dirty grunge overload, random fantasy gems, noisy textures
```
- 后处理：确认“金属磨损程度”和“晶体发光程度”，后续不要漂移。

#### 阶段0-05 轮廓语言图
- 用途：锁定主角、资源、敌人、UI 的轮廓复杂度。
- 建议生成数量：初稿 3 张，保留 1 张。
- 建议画幅：4:3。
- 背景：展示板。
- 命名建议：`phase0_shape_language`.
- 生图顺序：材质图之后。
- 统一风格检查点：轮廓必须简洁，大中小关系明确。
- 提示词：
```text
Use case: productivity-visual
Asset type: shape language board for the game "Deep Tide Station"
Primary request: create a silhouette and shape language board showing how the player vehicle, resources, enemies, props, and UI frames should differ while still feeling unified
Scene/backdrop: minimal design board with isolated silhouette groups and clean spacing, no text
Subject: readable game shape language for a side-view deep-sea salvage game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: simple presentation lighting prioritizing silhouette readability
Palette: mostly silhouette tones with accent cyan and orange highlights
Composition: grouped silhouettes with clear categories and strong contrast
Output expectation: one board that helps keep future assets consistent in complexity and outline style
Constraints: no text, no watermark, no over-rendering, no dense line art
Negative prompt: photorealistic, noisy shapes, tangled details, hard-to-read silhouettes, full illustration clutter
```
- 后处理：后续任何资产如果缩小后读不清，都回看这张图重做。

#### 阶段0-06 水下光照与体积感图
- 用途：锁定整个项目的水下体积感，不让后期每张图光照乱掉。
- 建议生成数量：初稿 3 张，保留 1 张。
- 建议画幅：16:9。
- 背景：完整场景。
- 命名建议：`phase0_underwater_lighting`.
- 生图顺序：轮廓图之后。
- 统一风格检查点：水体存在感明显，但不妨碍游戏可读性。
- 提示词：
```text
Use case: stylized-concept
Asset type: underwater lighting reference frame for the game "Deep Tide Station"
Primary request: create a style frame focused on underwater volume, suspended particles, soft haze, rim highlights, and readable glow behavior
Scene/backdrop: side-view underwater corridor with rocks, a small submersible, glowing resource points, and distant facility remains
Subject: readable underwater lighting and atmosphere for a 2D gameplay scene
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light, layered haze, subtle god-rays only where helpful, controlled glow
Palette: deep blue, cyan haze, muted teal, cold white highlights, minimal orange
Composition: wide side-view with clear midground play space and atmosphere stacked in depth
Output expectation: one underwater lighting reference shot for all later scene prompts
Constraints: no text, no watermark, no extreme darkness, no cinematic overbloom
Negative prompt: photorealistic, horror darkness, blown-out neon, muddy fog, movie-poster lighting, copied concept art
```
- 后处理：确认远景降饱和、近景更清晰，中景最适合玩法。

#### 阶段0-07 基地气质参考图
- 用途：锁定海面回收站的视觉语气。
- 建议生成数量：初稿 4 张，保留 1 张。
- 建议画幅：16:9。
- 背景：完整场景。
- 命名建议：`phase0_base_mood`.
- 生图顺序：在水下光照图之后。
- 统一风格检查点：基地必须像“功能性回收站”，不是豪华科幻城市。
- 提示词：
```text
Use case: stylized-concept
Asset type: base mood frame for the game "Deep Tide Station"
Primary request: create a sea-surface recovery station mood image that feels practical, compact, industrial, and clearly linked to deep-sea salvage work
Scene/backdrop: ocean surface platform, docking bay, crane, storage containers, repair lights, upgrade workshop entrance, and the player sub parked nearby
Subject: original recovery station base for a deep-sea salvage game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: overcast marine light with subtle industrial highlights and restrained glow
Palette: blue gray, steel gray, teal accents, cyan display light, orange hazard paint
Composition: side-view base layout with clear functional zones and uncluttered interface-friendly areas
Output expectation: one base mood frame that guides all later base scene images
Constraints: no text, no watermark, no luxury architecture, no crowded city skyline
Negative prompt: photorealistic, glossy sci-fi city, cyberpunk overload, anime style, dense clutter, copied platform design
```
- 后处理：确定基地是“工作站”而不是“景观图”。

#### 阶段0-08 浅海断层区气质参考图
- 用途：锁定第一海域的整体感。
- 建议生成数量：初稿 3 张，保留 1 张。
- 建议画幅：16:9。
- 背景：完整场景。
- 命名建议：`phase0_zone1_mood`.
- 生图顺序：基地气质图之后。
- 统一风格检查点：要相对明快，适合新手期。
- 提示词：
```text
Use case: stylized-concept
Asset type: zone mood frame for shallow fault area in "Deep Tide Station"
Primary request: create the first sea zone mood image, relatively friendly, readable, and rich with exploration cues
Scene/backdrop: shallow deep-sea fault zone with broken ledges, open movement lanes, mild glowing resources, sparse sea plants, and distant salvage debris
Subject: original first gameplay zone mood for a 2D salvage game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: clearer underwater diffuse light with modest haze and gentle glow
Palette: blue gray, teal, cyan glow, soft green highlights, tiny orange warning accents
Composition: wide side-view scene with safe lanes, readable landmarks, and clear collectible pockets
Output expectation: one mood frame establishing the first zone as playable and welcoming
Constraints: no text, no watermark, no oppressive darkness, no overgrown clutter
Negative prompt: photorealistic, horror abyss, heavy black shadows, visual noise, oversaturated neon, copied reef designs
```
- 后处理：这张图决定第一海域是否适合教学与演示。

#### 阶段0-09 热泉区气质参考图
- 用途：锁定第二海域的差异化。
- 建议生成数量：初稿 3 张，保留 1 张。
- 建议画幅：16:9。
- 背景：完整场景。
- 命名建议：`phase0_zone2_mood`.
- 生图顺序：第一海域气质图之后。
- 统一风格检查点：危险感更强，但仍保留读形和移动空间。
- 提示词：
```text
Use case: stylized-concept
Asset type: zone mood frame for thermal vent area in "Deep Tide Station"
Primary request: create the second sea zone mood image with stronger danger, hot vent signatures, mineral build-up, and denser risk cues
Scene/backdrop: thermal vent field with dark rock columns, vent plumes, mineral crusts, glowing ore deposits, hazard lights, and tighter movement paths
Subject: original thermal vent gameplay zone for a 2D salvage game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light mixed with subtle warm vent glow and sharp readable accents
Palette: deep navy, basalt gray, cyan, teal, cold white, limited orange-red vent glow
Composition: layered side-view with denser hazards yet clear playable channels
Output expectation: one mood frame that clearly separates zone two from zone one
Constraints: no text, no watermark, no lava fantasy look, no chaotic clutter
Negative prompt: photorealistic, volcanic fantasy, full red palette, unreadable smoke, muddy contrast, copied vent scenes
```
- 后处理：热泉光要少而准，不能把全图染成熔岩世界。

#### 阶段0-10 冷流峡谷区气质参考图
- 用途：锁定第三海域的压迫感。
- 建议生成数量：初稿 3 张，保留 1 张。
- 建议画幅：16:9。
- 背景：完整场景。
- 命名建议：`phase0_zone3_mood`.
- 生图顺序：热泉区气质图之后。
- 统一风格检查点：低能见度、强流向、狭窄感，但仍可玩。
- 提示词：
```text
Use case: stylized-concept
Asset type: zone mood frame for cold-current canyon in "Deep Tide Station"
Primary request: create the third sea zone mood image with stronger pressure, cold current lanes, narrow passages, and lower visibility
Scene/backdrop: deep canyon walls, current streaks, hanging debris, sparse cold-glow minerals, abandoned structural fragments, and constricted routes
Subject: original cold-current canyon gameplay zone for a 2D salvage game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: colder diffuse underwater light, stronger haze, sharper rim edges, minimal warm accents
Palette: deep blue, cold cyan, blue gray, pale teal, muted steel, almost no warm color
Composition: side-view canyon with strong directionality and controlled visual compression
Output expectation: one mood frame that communicates mid-to-late game challenge escalation
Constraints: no text, no watermark, no total darkness, no unreadable fog wall
Negative prompt: photorealistic, horror abyss, monochrome blackness, visual mud, random fantasy ruins, copied trench concepts
```
- 后处理：确保玩家仍能看懂通路，不要只剩“酷”。

#### 阶段0-11 风险生物群气质参考图
- 用途：锁定危险生物的共同视觉世界。
- 建议生成数量：初稿 3 张，保留 1 张。
- 建议画幅：16:9。
- 背景：完整场景。
- 命名建议：`phase0_enemy_mood`.
- 生图顺序：海域气质图之后。
- 统一风格检查点：危险体必须统一成“深海工业世界下的异常生物”。
- 提示词：
```text
Use case: stylized-concept
Asset type: enemy ecosystem mood frame for the game "Deep Tide Station"
Primary request: create a mood frame showing how hostile deep-sea creatures in this game should feel: dangerous, readable, and original rather than horror grotesque
Scene/backdrop: underwater risk zone with an electric ray, shell-like ambusher, pulse jelly group, faint resource glow, and clear side-view spacing
Subject: cohesive hostile life forms for a deep-sea salvage game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: dimmer underwater diffuse light with selective edge highlights and localized threat glow
Palette: navy, cyan, teal, pale bioluminescent blue, muted purple accents, tiny warning orange
Composition: side-view group composition that keeps each creature silhouette distinct
Output expectation: one mood frame guiding all later enemy and hazard designs
Constraints: no text, no watermark, no gore, no body horror, no copied creature designs
Negative prompt: photorealistic, grotesque horror, alien movie creature, blood, tentacle overload, muddy silhouettes
```
- 后处理：把“怪物感”压住，把“玩法识别性”提上来。

#### 阶段0-12 UI 风格母图
- 用途：锁定整个项目 UI 的边框、灯光、模块感。
- 建议生成数量：初稿 4 张，保留 1 张。
- 建议画幅：16:9。
- 背景：展示板。
- 命名建议：`phase0_ui_master`.
- 生图顺序：本阶段最后做。
- 统一风格检查点：UI 必须像同一套回收站设备界面，不像手机应用。
- 提示词：
```text
Use case: ui-mockup
Asset type: UI style master board for the game "Deep Tide Station"
Primary request: create a visual direction board for the game's HUD, buttons, panels, cards, meters, and dialog frames in one consistent style
Scene/backdrop: a clean design sheet showing multiple interface fragments such as oxygen bars, panel frames, buttons, grid slots, and warning modules without text
Subject: original deep-sea industrial game interface language
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: subtle interface glow, screen light accents, controlled luminous edges
Palette: steel blue, navy, teal, cyan glow, muted gray, small orange warning accents
Composition: modular design board with spacing and consistent corner radii and frame logic
Output expectation: one style board that locks the UI language for every later control and panel
Constraints: no text, no watermark, no mobile app aesthetic, no fantasy UI ornament overload
Negative prompt: photorealistic, glossy smartphone UI, cyberpunk overload, random neon, medieval fantasy panels, clutter
```
- 后处理：后续所有 UI 组件都必须回看这张母图。

---

## 8. 阶段 1：主角与潜水器

### 8.1 阶段目标

- 锁定玩家视觉中心。
- 玩家潜水器必须一眼就能认出来。
- 同时兼顾待机、移动、受击、返航、升级后的可扩展性。

### 8.2 阶段操作顺序

1. 先做基础待机。
2. 再做灯亮状态。
3. 再做推进状态。
4. 再做受击与警报状态。
5. 最后做功能展开状态。

### 8.3 本阶段总建议

- 单体资产优先纯 `#00ff00` 背景。
- 每个条目先出 `4` 张。
- 只保留最稳定、最能做系列扩展的一张。
- 不要一开始追求超级复杂结构。

### 8.4 阶段条目

#### 阶段1-01 主角潜水器基础待机图
- 用途：玩家在大多数时间看到的主角资产。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_player_sub_idle`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：机身必须小巧、可靠、功能明确，不像军用潜艇。
- 提示词：
```text
Use case: stylized-concept
Asset type: game-ready 2D side-view cutout asset for the player submersible in "Deep Tide Station"
Primary request: create the main player submersible in its default idle state
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no floor, no gradients
Subject: compact single-pilot deep-sea recovery submersible with front lamp, oxygen tank housing, small manipulator arm, cargo unit, and rear thruster
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater-inspired diffuse light with crisp readable rim highlights
Palette: navy, slate blue, steel gray, cyan glow, teal details, tiny safety-orange accents
Composition: centered subject, side view, generous padding, clean silhouette for game usage
Output expectation: one stable hero vehicle design for repeated gameplay use
Constraints: no text, no watermark, no human face, no realistic military submarine look, no heavy clutter
Negative prompt: photorealistic, pixel art, anime mech, muddy silhouette, over-detailed pipes everywhere, copied franchise vehicle
```
- 后处理：这张决定一切，后续所有状态都要沿用同一机体比例。

#### 阶段1-02 主角潜水器前灯开启图
- 用途：照明与探索状态表现。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_player_sub_light_on`.
- 生图顺序：待机图确认后立即生成。
- 统一风格检查点：只能改变照明与少量细节，不改变主体形体。
- 提示词：
```text
Use case: stylized-concept
Asset type: variant cutout asset for the player submersible in "Deep Tide Station"
Primary request: create the player submersible with the front exploration light turned on while preserving the exact same base design
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: the same compact recovery submersible, same proportions, with an active front lamp and subtle illuminated equipment accents
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft diffuse light plus a readable controlled lamp glow cone implied on the vehicle itself only
Palette: navy, steel blue, cyan glow, pale lamp white, muted teal, tiny orange accents
Composition: centered side-view subject with identical silhouette to the idle variant
Output expectation: one lighting-on gameplay variant that matches the idle vehicle
Constraints: no text, no watermark, no environment, no redesign of the hull, no oversized light beam scene
Negative prompt: photorealistic, over-bloom, redesign, clutter, copied sci-fi vehicle, anime mech
```
- 后处理：检查和待机图叠放时，主体轮廓是否完全一致。

#### 阶段1-03 主角潜水器推进状态图
- 用途：移动帧主状态参考。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_player_sub_move`.
- 生图顺序：灯亮图之后。
- 统一风格检查点：推进感明确，但不能复杂到难切图。
- 提示词：
```text
Use case: stylized-concept
Asset type: movement cutout asset for the player submersible in "Deep Tide Station"
Primary request: create the player submersible in a forward movement state with active rear propulsion
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: the same compact recovery submersible with rear thruster glow and a slight forward-drive pose, preserving the same hull and silhouette language
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with stronger propulsion glow accents
Palette: navy, slate blue, steel gray, cyan propulsion glow, teal details, minimal orange accents
Composition: centered subject, side-view, movement energy implied without motion blur overload
Output expectation: one movement-state reference matching the base hero vehicle
Constraints: no text, no watermark, no full environment, no redesign of proportions, no messy exhaust clouds
Negative prompt: photorealistic, racing vehicle style, muddy silhouette, dramatic perspective, copied franchise vehicle
```
- 后处理：推进尾流如果太抢眼，会压掉资源与敌人。

#### 阶段1-04 主角潜水器受击状态图
- 用途：受伤反馈和危险提示。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_player_sub_hit`.
- 生图顺序：推进状态之后。
- 统一风格检查点：有反馈，但不能变成爆炸废铁。
- 提示词：
```text
Use case: stylized-concept
Asset type: hit-state cutout asset for the player submersible in "Deep Tide Station"
Primary request: create the player submersible in a light hit reaction state with small sparks and warning signals
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: the same compact recovery submersible, slightly tilted from impact, with localized electric sparks and a subtle red-orange warning indicator
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft diffuse underwater light with tiny impact spark highlights
Palette: navy, steel blue, cyan accents, cold white sparks, tiny warning orange-red
Composition: centered side-view subject with intact readability and unchanged core hull proportions
Output expectation: one hit-state variant for clear gameplay feedback
Constraints: no text, no watermark, no explosion cloud, no destroyed hull, no gore
Negative prompt: photorealistic, battle damage realism, flames everywhere, clutter, copied combat sub design
```
- 后处理：控制火花范围，不然会和特效层冲突。

#### 阶段1-05 主角潜水器低氧警报状态图
- 用途：低氧时的主角状态视觉增强。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_player_sub_low_oxygen`.
- 生图顺序：受击图之后。
- 统一风格检查点：主体不变，只强化警报灯与紧张感。
- 提示词：
```text
Use case: stylized-concept
Asset type: alert-state cutout asset for the player submersible in "Deep Tide Station"
Primary request: create the player submersible in a low-oxygen alert state with restrained alarm lighting
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: the same compact recovery submersible with small emergency beacon lights and tension-focused illuminated warning accents
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft base light plus sparse pulsing warning accents
Palette: navy, steel blue, cyan glow, pale white, tiny orange-red warning indicators
Composition: centered side-view subject, same silhouette, no extra environmental storytelling
Output expectation: one low-oxygen variant that reads instantly in gameplay
Constraints: no text, no watermark, no redesign, no cinematic smoke, no big environment
Negative prompt: photorealistic, over-bloom alarm lights, clutter, copied sci-fi cockpit design, anime mech
```
- 后处理：不要让低氧状态看起来像受击状态，二者必须能区分。

#### 阶段1-06 主角潜水器满载货舱状态图
- 用途：返航压力、收益反馈表现。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_player_sub_loaded`.
- 生图顺序：警报图之后。
- 统一风格检查点：货舱扩展要明确，但不能破坏基础轮廓。
- 提示词：
```text
Use case: stylized-concept
Asset type: cargo-loaded cutout asset for the player submersible in "Deep Tide Station"
Primary request: create the player submersible in a visibly cargo-loaded state while preserving its core silhouette
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no floor, no shadows, no gradients
Subject: the same compact recovery submersible carrying visible collection pods, secured crates, or attached cargo modules
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with light metallic highlights on cargo modules
Palette: navy, steel blue, gray cargo metal, cyan accents, tiny orange markings
Composition: centered side-view subject with added cargo weight but preserved gameplay readability
Output expectation: one loaded-state variant communicating return pressure and reward
Constraints: no text, no watermark, no huge pile of junk obscuring the vehicle, no redesign of base hull
Negative prompt: photorealistic, scrap heap overload, muddy silhouette, dramatic perspective, copied industrial craft
```
- 后处理：看缩略图时，必须一眼能看出“装满了”。

#### 阶段1-07 机械臂展开状态图
- 用途：采集与升级视觉反馈。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_player_sub_arm_open`.
- 生图顺序：满载图之后。
- 统一风格检查点：展开结构应易读，不能像复杂机甲。
- 提示词：
```text
Use case: stylized-concept
Asset type: interaction-state cutout asset for the player submersible in "Deep Tide Station"
Primary request: create the player submersible with its recovery arm deployed for collection interaction
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: the same compact recovery submersible with a readable deployed manipulator arm ready to collect resources
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with tiny mechanical highlight accents
Palette: navy, steel blue, gray arm joints, cyan display lights, small orange safety marks
Composition: centered side-view subject, arm clearly visible, still compact and game-readable
Output expectation: one interaction variant for collection and upgrade visuals
Constraints: no text, no watermark, no overcomplicated robotics, no extra clutter, no redesign of the hull
Negative prompt: photorealistic, mech anime arm, tangled cables, muddy structure, copied robotic arm design
```
- 后处理：机械臂长度不能超过画面太多，否则后续碰撞区难对应。

#### 阶段1-08 扫描器展开状态图
- 用途：扫描范围升级、探测资源表现。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_player_sub_scanner`.
- 生图顺序：机械臂图之后。
- 统一风格检查点：扫描器是功能差异，不是第二台潜艇。
- 提示词：
```text
Use case: stylized-concept
Asset type: scanner-state cutout asset for the player submersible in "Deep Tide Station"
Primary request: create the player submersible with a visible scan module or antenna array deployed
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: the same compact recovery submersible with a readable resource-scanning module extended from the hull
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with scan-device highlight accents
Palette: navy, blue gray, cyan lights, teal device accents, tiny orange warning marks
Composition: centered side-view subject, scanning device obvious but not silhouette-breaking
Output expectation: one scanner-upgrade variant matching the main hero vehicle
Constraints: no text, no watermark, no redesign, no large radar dish, no environment
Negative prompt: photorealistic, satellite dish comedy, clutter, copied sci-fi scanner craft, anime mech
```
- 后处理：这张图只需要“看得见扫描器”，不要加入扫描波特效。

#### 阶段1-09 返航状态图
- 用途：返航、完成采集后的方向性反馈。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_player_sub_return`.
- 生图顺序：扫描器图之后。
- 统一风格检查点：返航状态依然要看起来稳定，不是逃命翻滚。
- 提示词：
```text
Use case: stylized-concept
Asset type: return-state cutout asset for the player submersible in "Deep Tide Station"
Primary request: create the player submersible in a return-to-base state with subtle navigation cue lighting
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: the same compact recovery submersible with homebound navigation lights and a more directed movement posture
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with faint route-guidance light accents
Palette: navy, steel blue, teal, cyan navigation light, minimal orange safety markers
Composition: centered side-view subject, clean readable directional intent
Output expectation: one return-state variant that supports safe-return gameplay feedback
Constraints: no text, no watermark, no exaggerated motion blur, no redesign, no environment
Negative prompt: photorealistic, action movie chase lighting, clutter, copied franchise craft, anime vehicle
```
- 后处理：返航状态和推进状态差异应主要在灯光语义而不是乱加零件。

#### 阶段1-10 海面停靠状态图
- 用途：基地停靠插画与菜单辅助素材。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_player_sub_docked`.
- 生图顺序：返航状态之后。
- 统一风格检查点：必须像“作业完成后停靠”，不是展示型摆拍。
- 提示词：
```text
Use case: stylized-concept
Asset type: docked cutout asset for the player submersible in "Deep Tide Station"
Primary request: create the player submersible in a calm docked state suitable for base and menu use
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: the same compact recovery submersible powered down slightly, tidy, practical, and ready for maintenance
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: calm neutral lighting with minimal glow and readable edges
Palette: navy, steel blue, gray, muted teal, tiny orange maintenance markings
Composition: centered side-view subject designed for insertion into base-related layouts
Output expectation: one docked variant for menus and base screens
Constraints: no text, no watermark, no dramatic action pose, no environment, no redesign
Negative prompt: photorealistic, hero showroom rendering, clutter, copied vehicle design, anime mech
```
- 后处理：保留较静态的状态，方便叠加到基地背景。

#### 阶段1-11 潜航员剪影备用图
- 用途：图鉴、教程、UI 辅助形象，不作为主玩法角色。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase1_diver_silhouette`.
- 生图顺序：潜水器系列后再生成。
- 统一风格检查点：是世界观人物，不喧宾夺主，不要脸部写实。
- 提示词：
```text
Use case: stylized-concept
Asset type: support character cutout asset for "Deep Tide Station"
Primary request: create an original recovery-station diver silhouette character for support UI and lore use, not as the primary gameplay sprite
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: compact deep-sea salvage diver in a practical suit with helmet, utility harness, and industrial equipment shapes
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft diffuse light with readable helmet rim and suit highlights
Palette: navy suit, gray metal parts, teal glow accents, tiny safety-orange details
Composition: centered side-view or slight three-quarter silhouette optimized for support art and tutorial use
Output expectation: one support-character design consistent with the world but secondary to the vehicle
Constraints: no text, no watermark, no expressive anime face, no heroic poster pose, no weapon emphasis
Negative prompt: photorealistic, anime protagonist, military marine, copied diver suit, noisy details, full illustration background
```
- 后处理：这个角色只用于辅助说明，不要让它比潜水器更显眼。

#### 阶段1-12 潜水器概念页
- 用途：统一主角的升级扩展与报告展示。
- 建议生成数量：初稿 3 张，保留 1 张。
- 建议画幅：4:3。
- 背景：展示板。
- 命名建议：`phase1_player_sub_sheet`.
- 生图顺序：本阶段最后。
- 统一风格检查点：必须把同一潜水器的功能结构讲清楚。
- 提示词：
```text
Use case: productivity-visual
Asset type: concept sheet board for the player submersible in "Deep Tide Station"
Primary request: create a clean concept board of the main player submersible showing the same design in several functional states and close-up module callouts without text
Scene/backdrop: presentation board with the main vehicle, secondary small variants, and modular detail insets
Subject: cohesive design sheet for the recovery submersible used throughout the game
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: neutral presentation lighting with soft underwater-inspired highlights
Palette: navy, steel blue, teal, cyan glow, muted gray, small orange accents
Composition: clean concept-board layout with ample spacing and consistent vehicle proportions
Output expectation: one production-friendly concept sheet for reference and presentation
Constraints: no text, no watermark, no random redesign variants, no huge perspective distortion
Negative prompt: photorealistic, blueprint overload, anime mech sheet, clutter, copied sci-fi concept board
```
- 后处理：后续升级模组、图鉴和报告截图都可以引用这张概念页。

---

## 9. 阶段 2：资源体系

### 9.1 阶段目标

- 锁定四大核心采集物。
- 同时完成普通、稀有、珍贵三档的视觉差异。
- 差异主要来自发光、结构完整度、稀有装饰，而不是完全换物种。

### 9.2 阶段操作顺序

1. 先做每种资源普通版。
2. 再做稀有版。
3. 再做珍贵版。
4. 同类资源始终保持基本轮廓一致。

### 9.3 本阶段总建议

- 单体资源统一纯 `#00ff00` 背景。
- 同类资源三档最好连着出，避免风格漂移。
- 生成时优先“地图可读性”，不要先追求图鉴精修。

### 9.4 阶段条目

#### 阶段2-01 荧团浮体普通版
- 用途：第一海域基础售卖资源。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_glow_cluster_common`.
- 生图顺序：本阶段第 1 张。
- 统一风格检查点：看起来像深海漂浮资源，不像普通水母。
- 提示词：
```text
Use case: stylized-concept
Asset type: game-ready 2D cutout resource asset for "Deep Tide Station"
Primary request: create the common version of Glow Cluster, a floating sellable deep-sea resource
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a semi-transparent glowing floating cluster, gel-like and softly bioluminescent, original resource object rather than a jellyfish
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with mild inner glow and crisp outer readability
Palette: pale cyan, teal glow, cool blue edges, very subtle white highlights
Composition: centered single resource object with clean silhouette and safe cutout padding
Output expectation: one common-tier collectible resource suitable for frequent map placement
Constraints: no text, no watermark, no jellyfish anatomy, no tentacle clutter, no environment
Negative prompt: photorealistic, organism realism, anime cute mascot, muddy translucent blob, copied sea-creature design
```
- 后处理：普通版发光要弱，才能让稀有与珍贵版拉开层级。

#### 阶段2-02 荧团浮体稀有版
- 用途：中价值售卖或保留资源。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_glow_cluster_rare`.
- 生图顺序：普通版通过后。
- 统一风格检查点：同轮廓，增强内核发光与结构层次。
- 提示词：
```text
Use case: stylized-concept
Asset type: rare-tier 2D cutout resource asset for "Deep Tide Station"
Primary request: create the rare version of Glow Cluster while preserving the same base species and silhouette logic
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a more luminous semi-transparent floating cluster with a stronger inner core, richer layered gel forms, and clearer rare-tier identity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft diffuse underwater light with stronger internal glow than the common tier
Palette: cyan, teal, pale green-cyan glow, cool white internal highlights
Composition: centered single resource object matching the common version silhouette family
Output expectation: one rare-tier variant visibly more valuable but still map-readable
Constraints: no text, no watermark, no total redesign, no tentacle creature look, no environment
Negative prompt: photorealistic, fantasy slime monster, muddy blob, copied bioluminescent animal, oversaturated neon
```
- 后处理：稀有版增强的是“价值感”，不是“体积翻倍”。

#### 阶段2-03 荧团浮体珍贵版
- 用途：高价值、强视觉反馈资源。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_glow_cluster_epic`.
- 生图顺序：稀有版之后。
- 统一风格检查点：仍是同一种资源，但核心更稳定、更亮、更贵。
- 提示词：
```text
Use case: stylized-concept
Asset type: valuable-tier 2D cutout resource asset for "Deep Tide Station"
Primary request: create the precious version of Glow Cluster with the same family silhouette but a premium visual presence
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a high-value floating gel cluster with a strong luminous core, refined layered outer membrane, and a premium collectible feel
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with concentrated internal glow and crisp edge readability
Palette: teal, bright cyan, cold white, slight warm-gold highlight kept minimal and controlled
Composition: centered single object with readable premium silhouette and safe padding
Output expectation: one precious-tier variant that feels rare and rewarding on pickup
Constraints: no text, no watermark, no fantasy magic orb look, no huge particles, no environment
Negative prompt: photorealistic, treasure gem cliché, muddy transparency, monster anatomy, oversaturated rainbow neon
```
- 后处理：珍贵版可以有极小暖色，但绝不能脱离全项目冷色基调。

#### 阶段2-04 壳晶矿普通版
- 用途：基础升级材料。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_shell_crystal_common`.
- 生图顺序：荧团浮体系完成后。
- 统一风格检查点：必须看起来像附着型壳晶矿，而不是普通水晶。
- 提示词：
```text
Use case: stylized-concept
Asset type: game-ready 2D cutout resource asset for "Deep Tide Station"
Primary request: create the common version of Shell Crystal Ore, an attached deep-sea upgrade material
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a shell-like crust holding embedded crystal growth, attached-resource look, mineral and organism hybrid feel, original deep-sea ore object
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with restrained crystal highlights
Palette: gray shell, blue-gray crust, cyan crystal glow, cool white highlights
Composition: centered single resource object with attachment-friendly silhouette and clean readability
Output expectation: one common-tier ore asset suitable for wall placement and upgrade loops
Constraints: no text, no watermark, no generic fantasy gem cluster, no environment, no muddy details
Negative prompt: photorealistic, fantasy crystal cave, jewel-store shine, copied ore design, clutter, monster shell face
```
- 后处理：壳体和晶体必须两种材质明显区分。

#### 阶段2-05 壳晶矿稀有版
- 用途：中级升级材料与收益选择资源。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_shell_crystal_rare`.
- 生图顺序：普通版之后。
- 统一风格检查点：在原结构上强化结晶密度和内部光。
- 提示词：
```text
Use case: stylized-concept
Asset type: rare-tier 2D cutout resource asset for "Deep Tide Station"
Primary request: create the rare version of Shell Crystal Ore while keeping the same shell-crystal family shape language
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a richer shell-crystal ore formation with brighter internal crystal growth, clearer layers, and stronger value identity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater light with stronger crystal edge highlights than the common version
Palette: gray shell, teal-cyan crystal glow, blue-gray mineral base, pale white sparkle accents
Composition: centered resource object, same family silhouette, readable rare-tier upgrade
Output expectation: one rare-tier ore variant for mid-value progression
Constraints: no text, no watermark, no total redesign, no fantasy gemstone pile, no environment
Negative prompt: photorealistic, luxury jewel, muddy texture, copied mineral design, noisy clutter
```
- 后处理：稀有版主要靠“内部结构更完整”，不要只是变亮。

#### 阶段2-06 壳晶矿珍贵版
- 用途：深海高价值升级材料。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_shell_crystal_epic`.
- 生图顺序：稀有版之后。
- 统一风格检查点：贵重感来自结构完整与核心发光，不是加满粒子。
- 提示词：
```text
Use case: stylized-concept
Asset type: precious-tier 2D cutout resource asset for "Deep Tide Station"
Primary request: create the precious version of Shell Crystal Ore with a premium upgrade-material presence
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: an advanced shell-crystal formation with a strong protected luminous core, refined shell structure, and high-value collectible identity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with concentrated crystal-core highlights
Palette: blue-gray shell, bright cyan, teal, cold white, micro warm-gold accents used sparingly
Composition: centered single resource object with crisp premium silhouette and collectible readability
Output expectation: one precious-tier ore variant suitable for late-game payoff
Constraints: no text, no watermark, no fantasy crown jewel look, no environment, no overdone particle effects
Negative prompt: photorealistic, treasure chest gem, rainbow saturation, muddy silhouette, copied crystal IP design
```
- 后处理：珍贵版不要看起来像另一个资源类。

#### 阶段2-07 冷凝胶普通版
- 用途：中层升级材料。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_condense_gel_common`.
- 生图顺序：壳晶矿系完成后。
- 统一风格检查点：应是冷流形成的高密度胶体，不是果冻玩具。
- 提示词：
```text
Use case: stylized-concept
Asset type: game-ready 2D cutout resource asset for "Deep Tide Station"
Primary request: create the common version of Condense Gel, a cold-current formed upgrade material
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a dense cold semi-liquid gel mass with subtle translucency, internal flow hints, and an original deep-sea material feel
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with restrained subsurface glow
Palette: ice blue, pale cyan, cool teal, muted white highlights
Composition: centered single gel object with clean, readable outer silhouette
Output expectation: one common-tier cold gel asset suitable for mid-layer resource loops
Constraints: no text, no watermark, no toy jelly look, no slime monster cues, no environment
Negative prompt: photorealistic, dessert jelly, anime slime, muddy blob, copied biogel design, clutter
```
- 后处理：普通版边缘要简洁，不能太破碎。

#### 阶段2-08 冷凝胶稀有版
- 用途：进阶升级材料。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_condense_gel_rare`.
- 生图顺序：普通版之后。
- 统一风格检查点：内部流动感增强，但外轮廓仍清楚。
- 提示词：
```text
Use case: stylized-concept
Asset type: rare-tier 2D cutout resource asset for "Deep Tide Station"
Primary request: create the rare version of Condense Gel with stronger internal structure and value cues
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a denser cold gel mass with clearer inner luminous veins, refined surface folds, and increased collectible value feel
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with brighter inner flow accents than the common version
Palette: ice blue, cyan, teal, cool white, faint green-cyan glow
Composition: centered single gel object from the same family with readable rare-tier distinction
Output expectation: one rare-tier gel variant that still reads cleanly in-game
Constraints: no text, no watermark, no total redesign, no slime creature cues, no environment
Negative prompt: photorealistic, dessert gel, monster slime, muddy translucency, copied biotech goo design
```
- 后处理：稀有版应更“凝”，不要更“散”。

#### 阶段2-09 冷凝胶珍贵版
- 用途：高阶升级与深层回报。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_condense_gel_epic`.
- 生图顺序：稀有版之后。
- 统一风格检查点：看起来更纯净、更高能，而不是更大一坨。
- 提示词：
```text
Use case: stylized-concept
Asset type: precious-tier 2D cutout resource asset for "Deep Tide Station"
Primary request: create the precious version of Condense Gel with premium purity and stronger energy concentration
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a high-value condensed cold gel mass with luminous internal energy, refined translucency, and premium collectible identity
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with concentrated internal glow and elegant edge readability
Palette: bright cyan, ice blue, teal, cold white, very subtle warm highlight only if needed
Composition: centered single high-value gel object with a strong premium silhouette
Output expectation: one precious-tier gel variant for late-game material payoff
Constraints: no text, no watermark, no fantasy magic orb look, no monster cues, no environment
Negative prompt: photorealistic, rainbow gel, slime creature, muddy edges, copied fantasy resource design
```
- 后处理：如果生成结果像发光宝珠，要打回。

#### 阶段2-10 旧时代零件普通版
- 用途：深海废弃设施低阶回收物。
- 建议生成数量：初稿 4 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_old_parts_common`.
- 生图顺序：冷凝胶系之后。
- 统一风格检查点：必须看出“来自旧设施”，但不能脏到看不清。
- 提示词：
```text
Use case: stylized-concept
Asset type: game-ready 2D cutout resource asset for "Deep Tide Station"
Primary request: create the common version of Old-Era Parts, salvageable metal remnants from abandoned deep-sea facilities
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: a readable cluster of old mechanical components, plates, connectors, or frame pieces with clear industrial origin
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with controlled metallic edge highlights
Palette: steel gray, blue gray, aged metal, muted teal residue, tiny orange markings
Composition: centered single salvage item with clean readable silhouette, not a junk pile mess
Output expectation: one common-tier salvage part asset usable in deeper resource loops
Constraints: no text, no watermark, no full rust heap, no giant machine chunk, no environment
Negative prompt: photorealistic, scrap pile realism, clutter, copied sci-fi engine parts, muddy silhouette, grunge overload
```
- 后处理：一定要限制“破旧程度”，不然会变成脏垃圾堆。

#### 阶段2-11 旧时代零件稀有版
- 用途：可卖可留的中高阶零件。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_old_parts_rare`.
- 生图顺序：普通版之后。
- 统一风格检查点：结构更完整、功能感更强。
- 提示词：
```text
Use case: stylized-concept
Asset type: rare-tier 2D cutout resource asset for "Deep Tide Station"
Primary request: create the rare version of Old-Era Parts with a stronger sense of usable preserved structure
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no gradients, no shadows
Subject: a salvage component cluster with more intact connectors, energy ports, mechanical framing, and visible value beyond scrap metal
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater light with controlled reflective edges and small functional glow accents
Palette: gray metal, blue steel, muted teal, cyan port glow, tiny orange labels
Composition: centered single salvage object matching the common-tier family but clearly rarer
Output expectation: one rare-tier old-part asset that feels useful and collectible
Constraints: no text, no watermark, no giant machinery mass, no environment, no redesign into a weapon
Negative prompt: photorealistic, junkyard realism, clutter, copied engine core designs, muddy edges, grunge overload
```
- 后处理：稀有版应更“可用”，而不是更“破”。

#### 阶段2-12 旧时代零件珍贵版
- 用途：高级模块制造材料。
- 建议生成数量：初稿 3 张，精修 1 张。
- 建议画幅：1:1。
- 背景：纯 `#00ff00`。
- 命名建议：`phase2_old_parts_epic`.
- 生图顺序：本阶段最后。
- 统一风格检查点：稀有核心模块感强，但不变成传奇武器。
- 提示词：
```text
Use case: stylized-concept
Asset type: precious-tier 2D cutout resource asset for "Deep Tide Station"
Primary request: create the precious version of Old-Era Parts as a high-value preserved core module from abandoned deep-sea infrastructure
Scene/backdrop: perfectly flat solid #00ff00 chroma-key background for clean cutout, no shadows, no gradients
Subject: an intact advanced salvage module with clear industrial form, premium connectors, contained light sources, and strong late-game crafting value
Style anchor: original 2D side-view deep-sea salvage game, semi-stylized industrial sci-fi, clean silhouette, readable shapes, restrained hand-painted texture, cool cyan-blue palette, fluorescent teal accents, small safety-orange accents, no existing IP resemblance
Lighting: soft underwater diffuse light with premium core highlights and controlled small glow sources
Palette: steel gray, dark blue metal, cyan energy ports, pale white highlights, minimal warm accents
Composition: centered single valuable salvage module with crisp premium silhouette
Output expectation: one precious-tier part asset that feels rare, advanced, and game-usable
Constraints: no text, no watermark, no weapon look, no huge machine block, no environment
Negative prompt: photorealistic, treasure chest loot, fantasy artifact, clutter, copied sci-fi reactor core, grunge overload
```
- 后处理：珍贵版要有“高级模块”感，但不能像大型地图道具。

---
