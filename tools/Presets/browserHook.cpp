#include "../../BetterEdit.hpp"
#include "PresetLayer.hpp"
#include <InputPrompt.hpp>

using namespace gdmake;

class EditLevelLayer_CB : public gd::EditLevelLayer {
    public:
        void onCreatePreset(cocos2d::CCObject* pSender) {
            auto lvl = extra::as<gd::GJGameLevel*>(
                extra::as<cocos2d::CCNode*>(pSender)->getUserObject()
            );

            InputPrompt::create("Save Preset", "Preset Name", [&lvl](const char* name) -> void {
                std::cout << name << "\n";
                std::cout << gd::LevelString(lvl->levelString).pData << "\n";

                BetterEdit::sharedState()->addPreset({
                    name, lvl->levelString
                });
            }, "Save")->show();
        }
};

void setupCreatePresetButton(gd::EditLevelLayer* self, gd::GJGameLevel* level) {
    auto btn = gd::CCMenuItemSpriteExtra::create(
        CCNodeConstructor()
            .fromFrameName("GJ_plusBtn_001.png")
            .scale(.6f)
            .done(),
        self,
        (cocos2d::SEL_MenuHandler)&EditLevelLayer_CB::onCreatePreset
    );
    btn->setUserObject(level);

    auto menu = extra::getChild<cocos2d::CCMenu*>(self, 13);
    auto folderBtn = extra::getChild<gd::CCMenuItemSpriteExtra*>(menu, -1);

    btn->setPosition(
        folderBtn->getPositionX(),
        folderBtn->getPositionY() + 40.0f
    );

    menu->addChild(btn);
}

GDMAKE_HOOK(0x15cbf0)
void __fastcall LevelBrowserLayer_onNew(gd::LevelBrowserLayer* self, edx_t edx, cocos2d::CCObject* pSender) {
    PresetLayer::create()->show();
}
