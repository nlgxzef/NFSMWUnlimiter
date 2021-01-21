# NFSMW Unlimiter
NFSMW Unlimiter is a script mod which fixes some issues and makes some improvements for added cars.

Features:
+ Fixes visibility, damage and crash issues for added cars.
+ Lets modders use custom "manufacturer" on frontend VLT node, for their car mods with new manufacturers. (Fully configurable via ini file.)
+ Fixes disappearing wheels issue.
+ Fixes secondary logo issue for cars without manufacturer logo.
+ Allows modders to add more than 10 cars in traffic patterns.
+ Expands memory pools.
+ Fixes flickering cars in crowded areas with rain
+ Fixes character names for non-career events.
+ Fixes missing objects for options and stuff in FNGs by cloning them.
+ Adds new customization items to the menu. (Fully configurable via car-specific or general ini files.) (Parts should get added by modders.)
+ Lets modders add custom rim brands. (Fully configurable via ini file.)
+ Lets modders define custom destroyed bounty award messages for any cop car. (Fully configurable via ini file.)
+ Lets modders add up to 1000 names for random AI Opponents. (RACERNAME_000-999)
+ Lets modders define engine type for any car. (Piston, Castrol (use "castrol" cheat code) and Rotary.)
+ Lets modders force LOD A for any car. (Useful if the modded car doesn't have LOD parts.)
+ Lets users enable some BETA features to use with elaymm4's BETA Content Mod.
+ Enables Backroom in My Cars menu. (Known issue: When you use Esc key to back out from Backroom, you won't be able to move between the options. Press Enter or Esc to get back and enter the menu again.)
+ Allows rims to have "LANGUAGEHASH" attribute.

Also check out:
- [2005 Ford Mustang GT (S-197) "Extra Customization Showcase"](https://nfsmods.xyz/mod/2225)
- [NFSMW Leftover Brakes Fix](https://nfsmods.xyz/mod/2226)
- [NFS Better License Plates](https://nfsmods.xyz/mod/2010)

# Technical Information
If you want everything to work properly:

1) You will need to add these textures in your FrontEnd\\FrontB.lzc, FrontEndTextures.tpk:
```
5524B4D1 - VISUAL_PART_ATTACHMENT
54125A8D - VISUAL_PART_BRAKE
DB0C8F94 - VISUAL_PART_DRIVER
F69AC384 - VISUAL_PART_HEAD_LIGHTS
524B1D74 - VISUAL_PART_INTERIOR
D68F9860 - VISUAL_PART_LICENSE_PLATE
0294EC5E - VISUAL_PART_ROOF
0DD35467 - VISUAL_PART_SIDE_MIRROR
2CBB2D1C - VISUAL_PART_TAIL_LIGHTS
```

2) You will need to add these strings into your LANGUAGES\\(LanguageName).bin:
```
964861FC - CO_DRIVER
BFC2E2AC - CO_ATTACHMENTS
B81F39E9 - CO_ATTACHMENT_1
B81F39EA - CO_ATTACHMENT_2
B81F39EB - CO_ATTACHMENT_3
B81F39EC - CO_ATTACHMENT_4
B81F39ED - CO_ATTACHMENT_5
B81F39EE - CO_ATTACHMENT_6
B81F39EF - CO_ATTACHMENT_7
B81F39F0 - CO_ATTACHMENT_8
B81F39F1 - CO_ATTACHMENT_9
BC067739 - CO_ATTACHMENT_10
CBC529DC - CO_INTERIOR
D16C070D - CO_HEADLIGHTS
F86904C6 - CO_ROOF
F9D99DA5 - CO_TAILLIGHTS
D3DAE7CF - CO_SIDE_MIRROR
```

3) You will need to add the new camera angles for the new customization options via NFS-VltEd.
```
frontend, screens, customize_master, customize_customizeparts:
customize_customizeparts_777
customize_customizeparts_266
customize_customizeparts_265
customize_customizeparts_262
customize_customizeparts_263
customize_customizeparts_264
customize_customizeparts_267
customize_customizeparts_268
customize_customizeparts_269
customize_customizeparts_270
customize_customizeparts_271
customize_customizeparts_272
customize_customizeparts_273
customize_customizeparts_274
customize_customizeparts_275
customize_customizeparts_276
customize_customizeparts_277
customize_customizeparts_278
customize_customizeparts_776
```

Note: Binary and NFS-VltEd scripts which will do these automatically for you are available in the release pack.

# Download
You can [download Unlimiter](https://github.com/nlgzrgn/NFSMWUnlimiter/releases) from Releases page, or from [NFSMods.xyz](https://www.nfsmods.xyz).
If you want to compile it yourself, you can download the source code from the green Code button up there.
